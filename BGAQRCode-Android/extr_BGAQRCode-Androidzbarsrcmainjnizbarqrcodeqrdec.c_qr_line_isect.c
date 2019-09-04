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
typedef  int /*<<< orphan*/ * qr_point ;
typedef  int* qr_line ;

/* Variables and functions */
 int /*<<< orphan*/  QR_DIVROUND (int,int) ; 

__attribute__((used)) static int qr_line_isect(qr_point _p,const qr_line _l0,const qr_line _l1){
  int d;
  int x;
  int y;
  d=_l0[0]*_l1[1]-_l0[1]*_l1[0];
  if(d==0)return -1;
  x=_l0[1]*_l1[2]-_l1[1]*_l0[2];
  y=_l1[0]*_l0[2]-_l0[0]*_l1[2];
  if(d<0){
    x=-x;
    y=-y;
    d=-d;
  }
  _p[0]=QR_DIVROUND(x,d);
  _p[1]=QR_DIVROUND(y,d);
  return 0;
}