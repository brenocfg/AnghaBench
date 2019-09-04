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
struct TYPE_3__ {int** fwd; int res; scalar_t__ y0; scalar_t__ x0; } ;
typedef  TYPE_1__ qr_aff ;

/* Variables and functions */

__attribute__((used)) static void qr_aff_project(qr_point _p,const qr_aff *_aff,
 int _u,int _v){
  _p[0]=(_aff->fwd[0][0]*_u+_aff->fwd[0][1]*_v+(1<<_aff->res-1)>>_aff->res)
   +_aff->x0;
  _p[1]=(_aff->fwd[1][0]*_u+_aff->fwd[1][1]*_v+(1<<_aff->res-1)>>_aff->res)
   +_aff->y0;
}