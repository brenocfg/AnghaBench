#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qr_point ;
struct TYPE_4__ {int u0; int v0; int** fwd; } ;
typedef  TYPE_1__ qr_hom_cell ;

/* Variables and functions */
 int /*<<< orphan*/  qr_hom_cell_fproject (int /*<<< orphan*/ ,TYPE_1__ const*,int,int,int) ; 

__attribute__((used)) static void qr_hom_cell_project(qr_point _p,const qr_hom_cell *_cell,
 int _u,int _v,int _res){
  _u-=_cell->u0<<_res;
  _v-=_cell->v0<<_res;
  qr_hom_cell_fproject(_p,_cell,
   _cell->fwd[0][0]*_u+_cell->fwd[0][1]*_v+(_cell->fwd[0][2]<<_res),
   _cell->fwd[1][0]*_u+_cell->fwd[1][1]*_v+(_cell->fwd[1][2]<<_res),
   _cell->fwd[2][0]*_u+_cell->fwd[2][1]*_v+(_cell->fwd[2][2]<<_res));
}