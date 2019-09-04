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
struct dd {double lo; double hi; } ;

/* Variables and functions */
 struct dd dd_add (double,double) ; 

__attribute__((used)) static inline double add_adjusted(double a, double b)
{
	struct dd sum;
	union {double f; uint64_t i;} uhi, ulo;

	sum = dd_add(a, b);
	if (sum.lo != 0) {
		uhi.f = sum.hi;
		if ((uhi.i & 1) == 0) {
			/* hibits += (int)copysign(1.0, sum.hi * sum.lo) */
			ulo.f = sum.lo;
			uhi.i += 1 - ((uhi.i ^ ulo.i) >> 62);
			sum.hi = uhi.f;
		}
	}
	return (sum.hi);
}