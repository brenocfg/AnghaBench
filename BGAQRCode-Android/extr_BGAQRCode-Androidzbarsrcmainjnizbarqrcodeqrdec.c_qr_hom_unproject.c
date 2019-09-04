#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * qr_point ;
struct TYPE_3__ {int** inv; int inv22; int res; scalar_t__ y0; scalar_t__ x0; } ;
typedef  TYPE_1__ qr_hom ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  INT_MIN ; 
 int /*<<< orphan*/  QR_DIVROUND (int,int) ; 

__attribute__((used)) static int qr_hom_unproject(qr_point _q,const qr_hom *_hom,int _x,int _y){
  int x;
  int y;
  int w;
  _x-=_hom->x0;
  _y-=_hom->y0;
  x=_hom->inv[0][0]*_x+_hom->inv[0][1]*_y;
  y=_hom->inv[1][0]*_x+_hom->inv[1][1]*_y;
  w=_hom->inv[2][0]*_x+_hom->inv[2][1]*_y
   +_hom->inv22+(1<<_hom->res-1)>>_hom->res;
  if(w==0){
    _q[0]=x<0?INT_MIN:INT_MAX;
    _q[1]=y<0?INT_MIN:INT_MAX;
    return -1;
  }
  else{
    if(w<0){
      x=-x;
      y=-y;
      w=-w;
    }
    _q[0]=QR_DIVROUND(x,w);
    _q[1]=QR_DIVROUND(y,w);
  }
  return 0;
}