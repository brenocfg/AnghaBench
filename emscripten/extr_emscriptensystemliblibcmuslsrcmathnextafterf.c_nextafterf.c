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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  FORCE_EVAL (float) ; 
 scalar_t__ isnan (float) ; 

float nextafterf(float x, float y)
{
	union {float f; uint32_t i;} ux={x}, uy={y};
	uint32_t ax, ay, e;

	if (isnan(x) || isnan(y))
		return x + y;
	if (ux.i == uy.i)
		return y;
	ax = ux.i & 0x7fffffff;
	ay = uy.i & 0x7fffffff;
	if (ax == 0) {
		if (ay == 0)
			return y;
		ux.i = (uy.i & 0x80000000) | 1;
	} else if (ax > ay || ((ux.i ^ uy.i) & 0x80000000))
		ux.i--;
	else
		ux.i++;
	e = ux.i & 0x7f800000;
	/* raise overflow if ux.f is infinite and x is finite */
	if (e == 0x7f800000)
		FORCE_EVAL(x+x);
	/* raise underflow if ux.f is subnormal or zero */
	if (e == 0)
		FORCE_EVAL(x*x + ux.f*ux.f);
	return ux.f;
}