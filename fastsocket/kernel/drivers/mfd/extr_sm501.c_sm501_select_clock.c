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
struct sm501_clock {unsigned long mclk; unsigned long divider; unsigned long shift; } ;

/* Variables and functions */
 int /*<<< orphan*/  sm501_calc_clock (unsigned long,struct sm501_clock*,int,unsigned long,long*) ; 

__attribute__((used)) static unsigned long sm501_select_clock(unsigned long freq,
					struct sm501_clock *clock,
					int max_div)
{
	unsigned long mclk;
	long best_diff = 999999999;

	/* Try 288MHz and 336MHz clocks. */
	for (mclk = 288000000; mclk <= 336000000; mclk += 48000000) {
		sm501_calc_clock(freq, clock, max_div, mclk, &best_diff);
	}

	/* Return best clock. */
	return clock->mclk / (clock->divider << clock->shift);
}