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
typedef  int uint32_t ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*) ; 
 int INT_MASK ; 
 int ONE ; 
 int ONE_HALF ; 
 int abs (int) ; 
 int /*<<< orphan*/  do_div (int,int) ; 

__attribute__((used)) static int scale_params(uint32_t dim_in, uint32_t dim_out, uint32_t origin,
			uint32_t *phase_init, uint32_t *phase_step)
{
	/* to improve precicsion calculations are done in U31.33 and converted
	 * to U3.29 at the end */
	int64_t k1, k2, k3, k4, tmp;
	uint64_t n, d, os, os_p, od, od_p, oreq;
	unsigned rpa = 0;
	int64_t ip64, delta;

	if (dim_out % 3 == 0)
		rpa = !(dim_in % (dim_out / 3));

	n = ((uint64_t)dim_out) << 34;
	d = dim_in;
	if (!d)
		return -1;
	do_div(n, d);
	k3 = (n + 1) >> 1;
	if ((k3 >> 4) < (1LL << 27) || (k3 >> 4) > (1LL << 31)) {
		DLOG("crap bad scale\n");
		return -1;
	}
	n = ((uint64_t)dim_in) << 34;
	d = (uint64_t)dim_out;
	if (!d)
		return -1;
	do_div(n, d);
	k1 = (n + 1) >> 1;
	k2 = (k1 - ONE) >> 1;

	*phase_init = (int)(k2 >> 4);
	k4 = (k3 - ONE) >> 1;

	if (rpa) {
		os = ((uint64_t)origin << 33) - ONE_HALF;
		tmp = (dim_out * os) + ONE_HALF;
		if (!dim_in)
			return -1;
		do_div(tmp, dim_in);
		od = tmp - ONE_HALF;
	} else {
		os = ((uint64_t)origin << 1) - 1;
		od = (((k3 * os) >> 1) + k4);
	}

	od_p = od & INT_MASK;
	if (od_p != od)
		od_p += ONE;

	if (rpa) {
		tmp = (dim_in * od_p) + ONE_HALF;
		if (!dim_in)
			return -1;
		do_div(tmp, dim_in);
		os_p = tmp - ONE_HALF;
	} else {
		os_p = ((k1 * (od_p >> 33)) + k2);
	}

	oreq = (os_p & INT_MASK) - ONE;

	ip64 = os_p - oreq;
	delta = ((int64_t)(origin) << 33) - oreq;
	ip64 -= delta;
	/* limit to valid range before the left shift */
	delta = (ip64 & (1LL << 63)) ? 4 : -4;
	delta <<= 33;
	while (abs((int)(ip64 >> 33)) > 4)
		ip64 += delta;
	*phase_init = (int)(ip64 >> 4);
	*phase_step = (uint32_t)(k1 >> 4);
	return 0;
}