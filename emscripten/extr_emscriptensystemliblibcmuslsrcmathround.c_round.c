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
typedef  int uint64_t ;
typedef  double double_t ;

/* Variables and functions */
 int /*<<< orphan*/  FORCE_EVAL (double) ; 
 double toint ; 

double round(double x)
{
	union {double f; uint64_t i;} u = {x};
	int e = u.i >> 52 & 0x7ff;
	double_t y;

	if (e >= 0x3ff+52)
		return x;
	if (u.i >> 63)
		x = -x;
	if (e < 0x3ff-1) {
		/* raise inexact if x!=0 */
		FORCE_EVAL(x + toint);
		return 0*u.f;
	}
	y = x + toint - toint - x;
	if (y > 0.5)
		y = y + x - 1;
	else if (y <= -0.5)
		y = y + x + 1;
	else
		y = y + x;
	if (u.i >> 63)
		y = -y;
	return y;
}