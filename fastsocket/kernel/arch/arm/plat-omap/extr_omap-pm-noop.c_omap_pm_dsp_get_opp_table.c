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
struct omap_opp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*) ; 

const struct omap_opp *omap_pm_dsp_get_opp_table(void)
{
	pr_debug("OMAP PM: DSP request for OPP table\n");

	/*
	 * Return DSP frequency table here:  The final item in the
	 * array should have .rate = .opp_id = 0.
	 */

	return NULL;
}