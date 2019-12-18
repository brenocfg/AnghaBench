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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*) ; 

u8 omap_pm_dsp_get_opp(void)
{
	pr_debug("OMAP PM: DSP requests current DSP OPP ID\n");

	/*
	 * For l-o dev tree, call clk_get_rate() on VDD1 OPP clock
	 *
	 * CDP12.14+:
	 * Call clk_get_rate() on the OPP custom clock, map that to an
	 * OPP ID using the tables defined in board-*.c/chip-*.c files.
	 */

	return 0;
}