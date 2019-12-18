#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct brcms_hardware {int sbclk; int clk; TYPE_1__* band; scalar_t__ pllreq; int /*<<< orphan*/  unit; int /*<<< orphan*/  d11core; } ;
struct TYPE_2__ {scalar_t__ pi; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcms_dbg_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wlc_phy_hw_clk_state_upd (scalar_t__,int) ; 

__attribute__((used)) static void brcms_b_xtal(struct brcms_hardware *wlc_hw, bool want)
{
	brcms_dbg_info(wlc_hw->d11core, "wl%d: want %d\n", wlc_hw->unit, want);

	/*
	 * dont power down if plldown is false or
	 * we must poll hw radio disable
	 */
	if (!want && wlc_hw->pllreq)
		return;

	wlc_hw->sbclk = want;
	if (!wlc_hw->sbclk) {
		wlc_hw->clk = false;
		if (wlc_hw->band && wlc_hw->band->pi)
			wlc_phy_hw_clk_state_upd(wlc_hw->band->pi, false);
	}
}