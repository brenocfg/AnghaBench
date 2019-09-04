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
typedef  int* qr_point ;
struct TYPE_3__ {int** inv; int x0; int y0; int ires; } ;
typedef  TYPE_1__ qr_aff ;

/* Variables and functions */

__attribute__((used)) static void qr_aff_unproject(qr_point _q,const qr_aff *_aff,
 int _x,int _y){
  _q[0]=_aff->inv[0][0]*(_x-_aff->x0)+_aff->inv[0][1]*(_y-_aff->y0)
   +(1<<_aff->ires>>1)>>_aff->ires;
  _q[1]=_aff->inv[1][0]*(_x-_aff->x0)+_aff->inv[1][1]*(_y-_aff->y0)
   +(1<<_aff->ires>>1)>>_aff->ires;
}