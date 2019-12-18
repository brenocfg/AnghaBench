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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct brcms_hardware {int forcefastclk; int mac_suspend_depth; int /*<<< orphan*/  wake_override; TYPE_1__* band; struct brcms_c_info* wlc; } ;
struct brcms_c_info {int /*<<< orphan*/  wl; } ;
struct TYPE_2__ {int /*<<< orphan*/  pi; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CLKMODE_DYNAMIC ; 
 int /*<<< orphan*/  BCMA_CLKMODE_FAST ; 
 int /*<<< orphan*/  BRCMS_WAKE_OVERRIDE_MACSUSPEND ; 
 int /*<<< orphan*/  brcms_b_bsinit (struct brcms_c_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_b_clkctl_clk (struct brcms_hardware*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_b_coreinit (struct brcms_c_info*) ; 
 int /*<<< orphan*/  brcms_c_setxband (struct brcms_hardware*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_intrsoff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_intrsrestore (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chspec_bandunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mboolset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_cal_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_chanspec_radio_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) void
static brcms_b_init(struct brcms_hardware *wlc_hw, u16 chanspec) {
	u32 macintmask;
	bool fastclk;
	struct brcms_c_info *wlc = wlc_hw->wlc;

	/* request FAST clock if not on */
	fastclk = wlc_hw->forcefastclk;
	if (!fastclk)
		brcms_b_clkctl_clk(wlc_hw, BCMA_CLKMODE_FAST);

	/* disable interrupts */
	macintmask = brcms_intrsoff(wlc->wl);

	/* set up the specified band and chanspec */
	brcms_c_setxband(wlc_hw, chspec_bandunit(chanspec));
	wlc_phy_chanspec_radio_set(wlc_hw->band->pi, chanspec);

	/* do one-time phy inits and calibration */
	wlc_phy_cal_init(wlc_hw->band->pi);

	/* core-specific initialization */
	brcms_b_coreinit(wlc);

	/* band-specific inits */
	brcms_b_bsinit(wlc, chanspec);

	/* restore macintmask */
	brcms_intrsrestore(wlc->wl, macintmask);

	/* seed wake_override with BRCMS_WAKE_OVERRIDE_MACSUSPEND since the mac
	 * is suspended and brcms_c_enable_mac() will clear this override bit.
	 */
	mboolset(wlc_hw->wake_override, BRCMS_WAKE_OVERRIDE_MACSUSPEND);

	/*
	 * initialize mac_suspend_depth to 1 to match ucode
	 * initial suspended state
	 */
	wlc_hw->mac_suspend_depth = 1;

	/* restore the clk */
	if (!fastclk)
		brcms_b_clkctl_clk(wlc_hw, BCMA_CLKMODE_DYNAMIC);
}