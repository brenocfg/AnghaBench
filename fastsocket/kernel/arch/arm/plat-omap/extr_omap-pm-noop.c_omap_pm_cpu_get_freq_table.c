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
struct cpufreq_frequency_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*) ; 

struct cpufreq_frequency_table **omap_pm_cpu_get_freq_table(void)
{
	pr_debug("OMAP PM: CPUFreq request for frequency table\n");

	/*
	 * Return CPUFreq frequency table here: loop over
	 * all VDD1 clkrates, pull out the mpu_ck frequencies, build
	 * table
	 */

	return NULL;
}