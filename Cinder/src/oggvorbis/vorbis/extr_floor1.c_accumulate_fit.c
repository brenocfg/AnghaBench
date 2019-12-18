#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {float const twofitatten; } ;
typedef  TYPE_1__ vorbis_info_floor1 ;
struct TYPE_7__ {int x0; int x1; int xa; int ya; int x2a; int y2a; int xya; int an; int xb; int yb; int x2b; int y2b; int xyb; int bn; } ;
typedef  TYPE_2__ lsfit_acc ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int vorbis_dBquant (float const*) ; 

__attribute__((used)) static int accumulate_fit(const float *flr,const float *mdct,
                          int x0, int x1,lsfit_acc *a,
                          int n,vorbis_info_floor1 *info){
  long i;

  int xa=0,ya=0,x2a=0,y2a=0,xya=0,na=0, xb=0,yb=0,x2b=0,y2b=0,xyb=0,nb=0;

  memset(a,0,sizeof(*a));
  a->x0=x0;
  a->x1=x1;
  if(x1>=n)x1=n-1;

  for(i=x0;i<=x1;i++){
    int quantized=vorbis_dBquant(flr+i);
    if(quantized){
      if(mdct[i]+info->twofitatten>=flr[i]){
        xa  += i;
        ya  += quantized;
        x2a += i*i;
        y2a += quantized*quantized;
        xya += i*quantized;
        na++;
      }else{
        xb  += i;
        yb  += quantized;
        x2b += i*i;
        y2b += quantized*quantized;
        xyb += i*quantized;
        nb++;
      }
    }
  }

  a->xa=xa;
  a->ya=ya;
  a->x2a=x2a;
  a->y2a=y2a;
  a->xya=xya;
  a->an=na;

  a->xb=xb;
  a->yb=yb;
  a->x2b=x2b;
  a->y2b=y2b;
  a->xyb=xyb;
  a->bn=nb;

  return(na);
}