#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int* qr_point ;
typedef  int /*<<< orphan*/  qr_line ;

/* Variables and functions */
 int INT_MAX ; 
 int INT_MIN ; 
 int QR_INT_BITS ; 
 int QR_MAXI (int,int) ; 
 int QR_MINI (int,int) ; 
 int qr_ilog (int) ; 
 int /*<<< orphan*/  qr_line_fit (int /*<<< orphan*/ ,int,int,int,int,int,int) ; 

__attribute__((used)) static void qr_line_fit_points(qr_line _l,qr_point *_p,int _np,int _res){
  int sx;
  int sy;
  int xmin;
  int xmax;
  int ymin;
  int ymax;
  int xbar;
  int ybar;
  int dx;
  int dy;
  int sxx;
  int sxy;
  int syy;
  int sshift;
  int sround;
  int i;
  sx=sy=0;
  ymax=xmax=INT_MIN;
  ymin=xmin=INT_MAX;
  for(i=0;i<_np;i++){
    sx+=_p[i][0];
    xmin=QR_MINI(xmin,_p[i][0]);
    xmax=QR_MAXI(xmax,_p[i][0]);
    sy+=_p[i][1];
    ymin=QR_MINI(ymin,_p[i][1]);
    ymax=QR_MAXI(ymax,_p[i][1]);
  }
  xbar=(sx+(_np>>1))/_np;
  ybar=(sy+(_np>>1))/_np;
  sshift=QR_MAXI(0,qr_ilog(_np*QR_MAXI(QR_MAXI(xmax-xbar,xbar-xmin),
   QR_MAXI(ymax-ybar,ybar-ymin)))-(QR_INT_BITS-1>>1));
  sround=(1<<sshift)>>1;
  sxx=sxy=syy=0;
  for(i=0;i<_np;i++){
    dx=_p[i][0]-xbar+sround>>sshift;
    dy=_p[i][1]-ybar+sround>>sshift;
    sxx+=dx*dx;
    sxy+=dx*dy;
    syy+=dy*dy;
  }
  qr_line_fit(_l,xbar,ybar,sxx,sxy,syy,_res);
}