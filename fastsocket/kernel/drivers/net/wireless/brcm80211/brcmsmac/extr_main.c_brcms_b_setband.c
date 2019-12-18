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
typedef  int /*<<< orphan*/  uint ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct brcms_hardware {int /*<<< orphan*/  d11core; int /*<<< orphan*/  up; struct brcms_c_info* wlc; } ;
struct brcms_c_info {int /*<<< orphan*/  wl; scalar_t__ macintstatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 int MCTL_EN_MAC ; 
 scalar_t__ MI_DMAINT ; 
 int /*<<< orphan*/  ON ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bcma_core_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_core_is_enabled (int /*<<< orphan*/ ) ; 
 int bcma_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_b_bsinit (struct brcms_c_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_b_core_phy_clk (struct brcms_hardware*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_c_mctrl_reset (struct brcms_hardware*) ; 
 int /*<<< orphan*/  brcms_c_setband_inact (struct brcms_c_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_intrsrestore (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maccontrol ; 

__attribute__((used)) static void brcms_b_setband(struct brcms_hardware *wlc_hw, uint bandunit,
			    u16 chanspec) {
	struct brcms_c_info *wlc = wlc_hw->wlc;
	u32 macintmask;

	/* Enable the d11 core before accessing it */
	if (!bcma_core_is_enabled(wlc_hw->d11core)) {
		bcma_core_enable(wlc_hw->d11core, 0);
		brcms_c_mctrl_reset(wlc_hw);
	}

	macintmask = brcms_c_setband_inact(wlc, bandunit);

	if (!wlc_hw->up)
		return;

	brcms_b_core_phy_clk(wlc_hw, ON);

	/* band-specific initializations */
	brcms_b_bsinit(wlc, chanspec);

	/*
	 * If there are any pending software interrupt bits,
	 * then replace these with a harmless nonzero value
	 * so brcms_c_dpc() will re-enable interrupts when done.
	 */
	if (wlc->macintstatus)
		wlc->macintstatus = MI_DMAINT;

	/* restore macintmask */
	brcms_intrsrestore(wlc->wl, macintmask);

	/* ucode should still be suspended.. */
	WARN_ON((bcma_read32(wlc_hw->d11core, D11REGOFFS(maccontrol)) &
		 MCTL_EN_MAC) != 0);
}