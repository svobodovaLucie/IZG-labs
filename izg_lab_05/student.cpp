/******************************************************************************
 * Laborator 04 Krivky - Zaklady pocitacove grafiky - IZG
 * ihulik@fit.vutbr.cz
 *
 * 
 * Popis: Hlavicky funkci pro funkce studentu
 *
 * Opravy a modifikace:
 * - isvoboda@fit.vutbr.cz
 *
 */

#include "student.h"
#include "globals.h"
#include "main.h"

#include <time.h>
#include <math.h>

//Viz hlavicka vector.h
USE_VECTOR_OF(Point2d, point2d_vec)
#define point2d_vecGet(pVec, i) (*point2d_vecGetPtr((pVec), (i)))

/* Secte dva body Point2d a vysledek vrati v result (musi byt inicializovan a alokovan)*/
void	addPoint2d(const Point2d *a, const Point2d *b, Point2d *result)
{
	IZG_ASSERT(result);
	result->x = a->x+b->x;
	result->y = a->y+b->y;
}

/* Vynasobi bod Point2d skalarni hodnotou typu double a vysledek vrati v result (musi byt inicializovan a alokovan)*/
void	mullPoint2d(double val, const Point2d *p, Point2d *result)
{
	IZG_ASSERT(result);
	result->x = p->x*val;
	result->y = p->y*val;
}

/**
 * Inicializace ridicich bodu horni trajektorie ve vykreslovacim okne.
 * Pocatek souradnicove soustavy je v levem hornim rohu okna. Xova souradnice
 * roste smerem doprava, Y smerem dolu.
 * @param points vystup, kam se pridavaji ridici body
 * @param offset_x posun vsech ridicich bodu v horizontalnim smeru (aby se mohli souradnice zadavat s pocatkem [0,0])
 * @param offset_y posun vsech ridicich bodu ve vertikalnim smeru
 */
void initControlPointsUp(S_Vector **points, int offset_x, int offset_y) {
  *points = vecCreateEmpty(sizeof(Point2d));
  Point2d p;
  p.x = 0;   p.y = 0;    point2d_vecPushBack(*points, p);

  p.x = 40;  p.y = -250; point2d_vecPushBack(*points, p);
  p.x = 160; p.y = -250; point2d_vecPushBack(*points, p);
  
  p.x = 200; p.y = 0;    point2d_vecPushBack(*points, p);

  p.x = 210; p.y = -180; point2d_vecPushBack(*points, p);
  p.x = 350; p.y = -180; point2d_vecPushBack(*points, p);
  
  p.x = 360; p.y = 0;    point2d_vecPushBack(*points, p);

  p.x = 390; p.y = -120;  point2d_vecPushBack(*points, p);
  p.x = 430; p.y = -120;  point2d_vecPushBack(*points, p);
  
  p.x = 460; p.y = 0;    point2d_vecPushBack(*points, p);

  p.x = 470; p.y = -70;  point2d_vecPushBack(*points, p);
  p.x = 525; p.y = -70;  point2d_vecPushBack(*points, p);
  
  p.x = 535; p.y = 0;    point2d_vecPushBack(*points, p);

  p.x = 545; p.y = -40;  point2d_vecPushBack(*points, p);
  p.x = 575; p.y = -40;  point2d_vecPushBack(*points, p);
  
  p.x = 585; p.y = 0;    point2d_vecPushBack(*points, p);

  Point2d offset = {offset_x, offset_y, 1.0};
  for(int i = 0; i < (*points)->size; i++) {
    addPoint2d(point2d_vecGetPtr(*points, i), &offset, point2d_vecGetPtr(*points, i));
  }
}

void initControlPointsDown(S_Vector **points, int offset_x, int offset_y) {
  /* == TODO ==
   * Uloha c.2
   * Nasledujuci volani funkce initControlPointsUp(.) zmazte a nahradte vlastnim kodem,
   * ktery inicializuje ridici body tak, aby byla trajektorie spojita (C1). Muzete skopirovat
   * kod funkce initControlPointsUp(.) a upravit primo souradnice bodu v kodu.
   */
  /*
    výpočet bodů pomocí doplnění třetího bodu na přímku (y vždy pouze změní znaménko, musíme tedy dopočítat x)
    analytická rovnice přímky: y = ax + b
    -> tedy b = y - ax, poté dopočítáme a. K výpočtu využíváme dvou předchozích nebo dvou dalších bodů (podle umístění hledaného body)
    ukázka výpočtu pro bod č. 5
      -250 = 160*a + b
        0  = 200*a + b
        --------------
        b = -200*a -> -250 = 160*a + (-200*a)
                      -250 = -40*a
                        a  = 25/4
                      -----------------------
                      b = -200*(25/4) = -1250
      rovnice přímky: y = 25/4*x - 1250
      souřadnice y bude mít pouze opačné znaménko: y = 180
      x dopočítáme pomocí vypočtené přímky:       180 = 25/4 * x - 1250   -> x = 228.8 
  */
  *points = vecCreateEmpty(sizeof(Point2d));
  Point2d p;
  // prvni krivka
  p.x = 0;   p.y = 0;    point2d_vecPushBack(*points, p);

  p.x = 40;  p.y = -250; point2d_vecPushBack(*points, p);
  p.x = 160; p.y = -250; point2d_vecPushBack(*points, p);
  
  // druha krivka
  p.x = 200; p.y = 0;    point2d_vecPushBack(*points, p);

  //p.x = 230; p.y = 180; point2d_vecPushBack(*points, p);
  //p.x = 320; p.y = 180; point2d_vecPushBack(*points, p);
  p.x = 229; p.y = 180; point2d_vecPushBack(*points, p);
  p.x = 315; p.y = 180; point2d_vecPushBack(*points, p);
  
  // treti krivka
  p.x = 360; p.y = 0;    point2d_vecPushBack(*points, p);

  p.x = 390; p.y = -120;  point2d_vecPushBack(*points, p);
  p.x = 430; p.y = -120;  point2d_vecPushBack(*points, p);
  
  // ctvrta krivka
  p.x = 460; p.y = 0;    point2d_vecPushBack(*points, p);

  p.x = 478; p.y = 70;  point2d_vecPushBack(*points, p);
  p.x = 518; p.y = 70;  point2d_vecPushBack(*points, p);
  
  // pata krivka
  p.x = 535; p.y = 0;    point2d_vecPushBack(*points, p);

  p.x = 545; p.y = -40;  point2d_vecPushBack(*points, p);
  p.x = 575; p.y = -40;  point2d_vecPushBack(*points, p);
  
  p.x = 585; p.y = 0;    point2d_vecPushBack(*points, p);

  Point2d offset = {offset_x, offset_y, 1.0};
  for(int i = 0; i < (*points)->size; i++) {
    addPoint2d(point2d_vecGetPtr(*points, i), &offset, point2d_vecGetPtr(*points, i));
  }
}

/**
 * Implementace vypoctu Bezierove kubiky.
 * @param P0,P1,P2,P3 ridici body kubiky
 * @param quality pocet bodu na krivke, ktere chceme vypocitat
 * @param trajectory_points vystupni vektor bodu kubiky (nemazat, jen pridavat body)
 */
void bezierCubic(const Point2d *P0, const Point2d *P1, const Point2d *P2, const Point2d *P3, 
  const int quality, S_Vector *trajectory_points) {
  
  /* == TODO ==
   * Soucast Ulohy c.1:
   * Sem pridejte kod vypoctu Bezierove kubiky. Body krivky pridavejte do trajectory_points.
   */
  double step = 1.0/quality;
  
  for(double t = 0.0; t <= 1.0; t+=step) {  
    double b0 = (1 - t)*(1 - t)*(1 - t);
    double b1 = 3*t*(1  - t)*(1 - t);
    double b2 = 3*t*t*(1 - t);
    double b3 = t*t*t;

    Point2d point;
    point.x = b0*P0->x + b1*P1->x + b2*P2->x + b3*P3->x;
    point.y = b0*P0->y + b1*P1->y + b2*P2->y + b3*P3->y;
    
    vecPushBack(trajectory_points, &point);
  }
}

/* 
 * Implementace vypoctu trajektorie, ktera se sklada z Bezierovych kubik.
 * @param quality pocet bodu krivky, ktere mame urcit
 * @param control_points ridici body krivky 
 * @param trajectory_points vystupni body zakrivene trajektorie 
 */
void	bezierCubicsTrajectory(int quality, const S_Vector *control_points, S_Vector *trajectory_points) {
  // Toto musi byt na zacatku funkce, nemazat.
  point2d_vecClean(trajectory_points);

  /* == TODO ==
   * Uloha c.1
   * Ziskejte postupne 4 ridici body a pro kazdou ctverici vypocitejte body Bezierovy kubiky.
   * 
   * Kostra:
   *  for(...; ...; ...) {
   *    Point2d *P0 = ...
   *    Point2d *P1 = ...
   *    Point2d *P2 = ...
   *    Point2d *P3 = ...
   *    bezierCubic(P0, P1, P2, P3, quality, trajectory_points);
   *  }
   * Nasledujici volani funkce getLinePoints(.) zmazte - je to jen ilustrace hranate trajektorie.
   */
   // jeden bod je vždy u dvou po sobě jdoucích křivek stejný, proto v cyklu je i = i + 3
    for(int i = 0; i < point2d_vecSize(control_points)-3; i = i + 3) {
      Point2d *P0 = (Point2d*)vecGetPtr(control_points, i);
      Point2d *P1 = (Point2d*)vecGetPtr(control_points, i + 1);
      Point2d *P2 = (Point2d*)vecGetPtr(control_points, i + 2);
      Point2d *P3 = (Point2d*)vecGetPtr(control_points, i + 3);
      bezierCubic(P0, P1, P2, P3, quality, trajectory_points);
    }
  //getLinePoints(control_points, trajectory_points);
}
