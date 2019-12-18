#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
struct brcms_hardware {int up; int sbclk; int clk; int /*<<< orphan*/  sih; int /*<<< orphan*/  noreset; TYPE_2__* wlc; int /*<<< orphan*/  d11core; TYPE_1__* band; } ;
struct TYPE_6__ {int /*<<< orphan*/  wl; } ;
struct TYPE_5__ {int /*<<< orphan*/  pi; } ;

/* Variables and functions */
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 int MCTL_EN_MAC ; 
 int /*<<< orphan*/  OFF ; 
 int /*<<< orphan*/  ai_pci_down (int /*<<< orphan*/ ) ; 
 scalar_t__ bcma_core_is_enabled (int /*<<< orphan*/ ) ; 
 int bcma_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_b_xtal (struct brcms_hardware*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_c_coredisable (struct brcms_hardware*) ; 
 int /*<<< orphan*/  brcms_c_flushqueues (TYPE_2__*) ; 
 int /*<<< orphan*/  brcms_c_suspend_mac_and_wait (TYPE_2__*) ; 
 int brcms_deviceremoved (TYPE_2__*) ; 
 scalar_t__ brcms_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maccontrol ; 
 int /*<<< orphan*/  wlc_phy_hw_clk_state_upd (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wlc_phy_hw_state_upd (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int brcms_b_down_finish(struct brcms_hardware *wlc_hw)
{
	uint callbacks = 0;
	bool dev_gone;

	if (!wlc_hw->up)
		return callbacks;

	wlc_hw->up = false;
	wlc_phy_hw_state_upd(wlc_hw->band->pi, false);

	dev_gone = brcms_deviceremoved(wlc_hw->wlc);

	if (dev_gone) {
		wlc_hw->sbclk = false;
		wlc_hw->clk = false;
		wlc_phy_hw_clk_state_upd(wlc_hw->band->pi, false);

		/* reclaim any posted packets */
		brcms_c_flushqueues(wlc_hw->wlc);
	} else {

		/* Reset and disable the core */
		if (bcma_core_is_enabled(wlc_hw->d11core)) {
			if (bcma_read32(wlc_hw->d11core,
					D11REGOFFS(maccontrol)) & MCTL_EN_MAC)
				brcms_c_suspend_mac_and_wait(wlc_hw->wlc);
			callbacks += brcms_reset(wlc_hw->wlc->wl);
			brcms_c_coredisable(wlc_hw);
		}

		/* turn off primary xtal and pll */
		if (!wlc_hw->noreset) {
			ai_pci_down(wlc_hw->sih);
			brcms_b_xtal(wlc_hw, OFF);
		}
	}

	return callbacks;
}