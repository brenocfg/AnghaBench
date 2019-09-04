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
typedef  int double_t ;

/* Variables and functions */
 int /*<<< orphan*/  FORCE_EVAL (float) ; 
 double log1p (int) ; 

double atanh(double x)
{
	union {double f; uint64_t i;} u = {.f = x};
	unsigned e = u.i >> 52 & 0x7ff;
	unsigned s = u.i >> 63;
	double_t y;

	/* |x| */
	u.i &= (uint64_t)-1/2;
	y = u.f;

	if (e < 0x3ff - 1) {
		if (e < 0x3ff - 32) {
			/* handle underflow */
			if (e == 0)
				FORCE_EVAL((float)y);
		} else {
			/* |x| < 0.5, up to 1.7ulp error */
			y = 0.5*log1p(2*y + 2*y*y/(1-y));
		}
	} else {
		/* avoid overflow */
		y = 0.5*log1p(2*(y/(1-y)));
	}
	return s ? -y : y;
}