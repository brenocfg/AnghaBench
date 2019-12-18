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

/* Variables and functions */

__attribute__((used)) static unsigned long calc_mck_cycles(unsigned long ns, unsigned long mck_hz)
{
	unsigned long mul;

	/*
	* cycles = x [nsec] * f [Hz] / 10^9 [ns in sec] =
	*     x * (f / 1_000_000_000) =
	*     x * ((f * 65536) / 1_000_000_000) / 65536 =
	*     x * (((f / 10_000) * 65536) / 100_000) / 65536 =
	*/

	mul = (mck_hz / 10000) << 16;
	mul /= 100000;

	return (ns * mul + 65536) >> 16;    /* rounding */
}