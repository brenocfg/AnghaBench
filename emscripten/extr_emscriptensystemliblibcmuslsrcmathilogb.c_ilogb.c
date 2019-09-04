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
 int /*<<< orphan*/  FORCE_EVAL (float) ; 
 int FP_ILOGB0 ; 
 int FP_ILOGBNAN ; 
 int INT_MAX ; 

int ilogb(double x)
{
	#pragma STDC FENV_ACCESS ON
	union {double f; uint64_t i;} u = {x};
	uint64_t i = u.i;
	int e = i>>52 & 0x7ff;

	if (!e) {
		i <<= 12;
		if (i == 0) {
			FORCE_EVAL(0/0.0f);
			return FP_ILOGB0;
		}
		/* subnormal x */
		for (e = -0x3ff; i>>63 == 0; e--, i<<=1);
		return e;
	}
	if (e == 0x7ff) {
		FORCE_EVAL(0/0.0f);
		return i<<12 ? FP_ILOGBNAN : INT_MAX;
	}
	return e - 0x3ff;
}