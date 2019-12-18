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
struct brcms_hardware {int clk; TYPE_1__* band; int /*<<< orphan*/  d11core; scalar_t__ noreset; int /*<<< orphan*/  wlc; int /*<<< orphan*/  unit; } ;
struct TYPE_2__ {int /*<<< orphan*/  pi; } ;

/* Variables and functions */
 int /*<<< orphan*/  OFF ; 
 int /*<<< orphan*/  bcma_core_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_b_core_phypll_ctl (struct brcms_hardware*,int) ; 
 int /*<<< orphan*/  brcms_dbg_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int brcms_deviceremoved (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_anacore (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_hw_clk_state_upd (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wlc_phy_switch_radio (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcms_c_coredisable(struct brcms_hardware *wlc_hw)
{
	bool dev_gone;

	brcms_dbg_info(wlc_hw->d11core, "wl%d: disable core\n", wlc_hw->unit);

	dev_gone = brcms_deviceremoved(wlc_hw->wlc);

	if (dev_gone)
		return;

	if (wlc_hw->noreset)
		return;

	/* radio off */
	wlc_phy_switch_radio(wlc_hw->band->pi, OFF);

	/* turn off analog core */
	wlc_phy_anacore(wlc_hw->band->pi, OFF);

	/* turn off PHYPLL to save power */
	brcms_b_core_phypll_ctl(wlc_hw, false);

	wlc_hw->clk = false;
	bcma_core_disable(wlc_hw->d11core, 0);
	wlc_phy_hw_clk_state_upd(wlc_hw->band->pi, false);
}