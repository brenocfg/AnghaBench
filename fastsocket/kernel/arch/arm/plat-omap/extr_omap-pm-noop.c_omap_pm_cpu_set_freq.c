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
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long) ; 

void omap_pm_cpu_set_freq(unsigned long f)
{
	if (f == 0) {
		WARN_ON(1);
		return;
	}

	pr_debug("OMAP PM: CPUFreq requests CPU frequency to be set to %lu\n",
		 f);

	/*
	 * For l-o dev tree, determine whether MPU freq or DSP OPP id
	 * freq is higher.  Find the OPP ID corresponding to the
	 * higher frequency.  Call clk_round_rate() and clk_set_rate()
	 * on the OPP custom clock.
	 *
	 * CDP should just be able to set the VDD1 OPP clock rate here.
	 */
}