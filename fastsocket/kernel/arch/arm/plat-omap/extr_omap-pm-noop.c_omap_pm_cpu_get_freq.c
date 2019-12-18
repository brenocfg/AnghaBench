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
 int /*<<< orphan*/  pr_debug (char*) ; 

unsigned long omap_pm_cpu_get_freq(void)
{
	pr_debug("OMAP PM: CPUFreq requests current CPU frequency\n");

	/*
	 * Call clk_get_rate() on the mpu_ck.
	 */

	return 0;
}