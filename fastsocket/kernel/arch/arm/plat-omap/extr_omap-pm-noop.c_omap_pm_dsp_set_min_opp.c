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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__) ; 

void omap_pm_dsp_set_min_opp(u8 opp_id)
{
	if (opp_id == 0) {
		WARN_ON(1);
		return;
	}

	pr_debug("OMAP PM: DSP requests minimum VDD1 OPP to be %d\n", opp_id);

	/*
	 *
	 * For l-o dev tree, our VDD1 clk is keyed on OPP ID, so we
	 * can just test to see which is higher, the CPU's desired OPP
	 * ID or the DSP's desired OPP ID, and use whichever is
	 * highest.
	 *
	 * In CDP12.14+, the VDD1 OPP custom clock that controls the DSP
	 * rate is keyed on MPU speed, not the OPP ID.  So we need to
	 * map the OPP ID to the MPU speed for use with clk_set_rate()
	 * if it is higher than the current OPP clock rate.
	 *
	 */
}