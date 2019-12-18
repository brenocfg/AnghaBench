#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int twofitweight; } ;
typedef  TYPE_1__ vorbis_info_floor1 ;
struct TYPE_6__ {int x0; int x1; int bn; int an; double xa; double ya; double x2a; double y2a; double xya; scalar_t__ xyb; scalar_t__ y2b; scalar_t__ x2b; scalar_t__ yb; scalar_t__ xb; } ;
typedef  TYPE_2__ lsfit_acc ;

/* Variables and functions */
 int rint (double) ; 

__attribute__((used)) static int fit_line(lsfit_acc *a,int fits,int *y0,int *y1,
                    vorbis_info_floor1 *info){
  double xb=0,yb=0,x2b=0,y2b=0,xyb=0,bn=0;
  int i;
  int x0=a[0].x0;
  int x1=a[fits-1].x1;

  for(i=0;i<fits;i++){
    double weight = (a[i].bn+a[i].an)*info->twofitweight/(a[i].an+1)+1.;

    xb+=a[i].xb + a[i].xa * weight;
    yb+=a[i].yb + a[i].ya * weight;
    x2b+=a[i].x2b + a[i].x2a * weight;
    y2b+=a[i].y2b + a[i].y2a * weight;
    xyb+=a[i].xyb + a[i].xya * weight;
    bn+=a[i].bn + a[i].an * weight;
  }

  if(*y0>=0){
    xb+=   x0;
    yb+=  *y0;
    x2b+=  x0 *  x0;
    y2b+= *y0 * *y0;
    xyb+= *y0 *  x0;
    bn++;
  }

  if(*y1>=0){
    xb+=   x1;
    yb+=  *y1;
    x2b+=  x1 *  x1;
    y2b+= *y1 * *y1;
    xyb+= *y1 *  x1;
    bn++;
  }

  {
    double denom=(bn*x2b-xb*xb);

    if(denom>0.){
      double a=(yb*x2b-xyb*xb)/denom;
      double b=(bn*xyb-xb*yb)/denom;
      *y0=rint(a+b*x0);
      *y1=rint(a+b*x1);

      /* limit to our range! */
      if(*y0>1023)*y0=1023;
      if(*y1>1023)*y1=1023;
      if(*y0<0)*y0=0;
      if(*y1<0)*y1=0;

      return 0;
    }else{
      *y0=0;
      *y1=0;
      return 1;
    }
  }
}