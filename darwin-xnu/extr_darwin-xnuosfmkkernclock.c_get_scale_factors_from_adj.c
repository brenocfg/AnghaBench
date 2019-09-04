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
 scalar_t__ NSEC_PER_SEC ; 
 int ticks_per_sec ; 

__attribute__((used)) static void
get_scale_factors_from_adj(int64_t adjustment, uint64_t* tick_scale_x, uint64_t* s_scale_ns, int64_t* s_adj_nsx)
{
	uint64_t scale;
	int64_t nano, frac;

	/*-
	 * Calculating the scaling factor.  We want the number of 1/2^64
	 * fractions of a second per period of the hardware counter, taking
	 * into account the th_adjustment factor which the NTP PLL/adjtime(2)
	 * processing provides us with.
	 *
	 * The th_adjustment is nanoseconds per second with 32 bit binary
	 * fraction and we want 64 bit binary fraction of second:
	 *
	 *	 x = a * 2^32 / 10^9 = a * 4.294967296
	 *
	 * The range of th_adjustment is +/- 5000PPM so inside a 64bit int
	 * we can only multiply by about 850 without overflowing, that
	 * leaves no suitably precise fractions for multiply before divide.
	 *
	 * Divide before multiply with a fraction of 2199/512 results in a
	 * systematic undercompensation of 10PPM of th_adjustment.  On a
	 * 5000PPM adjustment this is a 0.05PPM error.  This is acceptable.
	 *
	 * We happily sacrifice the lowest of the 64 bits of our result
	 * to the goddess of code clarity.
	 *
	 */
	scale = (uint64_t)1 << 63;
	scale += (adjustment / 1024) * 2199;
	scale /= ticks_per_sec;
	*tick_scale_x = scale * 2;

	/*
	 * hi part of adj
	 * it contains ns (without fraction) to add to the next sec.
	 * Get ns scale factor for the next sec.
	 */
	nano = (adjustment > 0)? adjustment >> 32 : -((-adjustment) >> 32);
	scale = (uint64_t) NSEC_PER_SEC;
	scale += nano;
	*s_scale_ns = scale;

	/*
	 * lo part of adj
	 * it contains 32 bit frac of ns to add to the next sec.
	 * Keep it as additional adjustment for the next sec.
	 */
	frac = (adjustment > 0)? ((uint32_t) adjustment) : -((uint32_t) (-adjustment));
	*s_adj_nsx = (frac>0)? frac << 32 : -( (-frac) << 32);

	return;
}