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
typedef  int /*<<< orphan*/  u16 ;
struct brcms_hardware {int forcefastclk; TYPE_1__* band; } ;
struct TYPE_2__ {int /*<<< orphan*/  pi; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CLKMODE_DYNAMIC ; 
 int /*<<< orphan*/  BCMA_CLKMODE_FAST ; 
 int /*<<< orphan*/  brcms_b_clkctl_clk (struct brcms_hardware*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_b_phy_reset (struct brcms_hardware*) ; 
 int /*<<< orphan*/  wlc_phy_bw_state_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_chanspec_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void brcms_b_bw_set(struct brcms_hardware *wlc_hw, u16 bw)
{
	bool fastclk;

	/* request FAST clock if not on */
	fastclk = wlc_hw->forcefastclk;
	if (!fastclk)
		brcms_b_clkctl_clk(wlc_hw, BCMA_CLKMODE_FAST);

	wlc_phy_bw_state_set(wlc_hw->band->pi, bw);

	brcms_b_phy_reset(wlc_hw);
	wlc_phy_init(wlc_hw->band->pi, wlc_phy_chanspec_get(wlc_hw->band->pi));

	/* restore the clk */
	if (!fastclk)
		brcms_b_clkctl_clk(wlc_hw, BCMA_CLKMODE_DYNAMIC);
}