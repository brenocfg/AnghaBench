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
typedef  scalar_t__* qr_point ;
struct TYPE_3__ {scalar_t__ y0; scalar_t__ x0; } ;
typedef  TYPE_1__ qr_hom_cell ;

/* Variables and functions */
 scalar_t__ INT_MAX ; 
 scalar_t__ INT_MIN ; 
 scalar_t__ QR_DIVROUND (int,int) ; 

__attribute__((used)) static void qr_hom_cell_fproject(qr_point _p,const qr_hom_cell *_cell,
 int _x,int _y,int _w){
  if(_w==0){
    _p[0]=_x<0?INT_MIN:INT_MAX;
    _p[1]=_y<0?INT_MIN:INT_MAX;
  }
  else{
    if(_w<0){
      _x=-_x;
      _y=-_y;
      _w=-_w;
    }
    _p[0]=QR_DIVROUND(_x,_w)+_cell->x0;
    _p[1]=QR_DIVROUND(_y,_w)+_cell->y0;
  }
}