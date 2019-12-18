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
union float64_components {int* i; int /*<<< orphan*/  f64; } ;
struct roundingData {int dummy; } ;
typedef  int /*<<< orphan*/  float64 ;

/* Variables and functions */

__attribute__((used)) static float64 float64_abs(struct roundingData *roundData,float64 rFm)
{
	union float64_components u;

	u.f64 = rFm;
#ifdef __ARMEB__
	u.i[0] &= 0x7fffffff;
#else
	u.i[1] &= 0x7fffffff;
#endif

	return u.f64;
}