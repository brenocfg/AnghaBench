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

/* Variables and functions */
 int /*<<< orphan*/  FORCE_EVAL (double) ; 
 scalar_t__ isnan (long double) ; 
 scalar_t__ signbit (double) ; 

double nexttoward(double x, long double y)
{
	union {double f; uint64_t i;} ux = {x};
	int e;

	if (isnan(x) || isnan(y))
		return x + y;
	if (x == y)
		return y;
	if (x == 0) {
		ux.i = 1;
		if (signbit(y))
			ux.i |= 1ULL<<63;
	} else if (x < y) {
		if (signbit(x))
			ux.i--;
		else
			ux.i++;
	} else {
		if (signbit(x))
			ux.i++;
		else
			ux.i--;
	}
	e = ux.i>>52 & 0x7ff;
	/* raise overflow if ux.f is infinite and x is finite */
	if (e == 0x7ff)
		FORCE_EVAL(x+x);
	/* raise underflow if ux.f is subnormal or zero */
	if (e == 0)
		FORCE_EVAL(x*x + ux.f*ux.f);
	return ux.f;
}