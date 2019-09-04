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

/* Variables and functions */

__attribute__((used)) static int qr_point_ccw(const qr_point _p0,
 const qr_point _p1,const qr_point _p2){
  return (_p1[0]-_p0[0])*(_p2[1]-_p0[1])-(_p1[1]-_p0[1])*(_p2[0]-_p0[0]);
}