#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
struct brcms_hardware {TYPE_1__* band; TYPE_2__* wlc; int /*<<< orphan*/  up; } ;
struct TYPE_4__ {int /*<<< orphan*/  wl; scalar_t__ macintmask; } ;
struct TYPE_3__ {int /*<<< orphan*/  pi; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CLKMODE_FAST ; 
 int /*<<< orphan*/  brcms_b_clkctl_clk (struct brcms_hardware*,int /*<<< orphan*/ ) ; 
 int brcms_deviceremoved (TYPE_2__*) ; 
 int /*<<< orphan*/  brcms_intrsoff (int /*<<< orphan*/ ) ; 
 scalar_t__ wlc_phy_down (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int brcms_b_bmac_down_prep(struct brcms_hardware *wlc_hw)
{
	bool dev_gone;
	uint callbacks = 0;

	if (!wlc_hw->up)
		return callbacks;

	dev_gone = brcms_deviceremoved(wlc_hw->wlc);

	/* disable interrupts */
	if (dev_gone)
		wlc_hw->wlc->macintmask = 0;
	else {
		/* now disable interrupts */
		brcms_intrsoff(wlc_hw->wlc->wl);

		/* ensure we're running on the pll clock again */
		brcms_b_clkctl_clk(wlc_hw, BCMA_CLKMODE_FAST);
	}
	/* down phy at the last of this stage */
	callbacks += wlc_phy_down(wlc_hw->band->pi);

	return callbacks;
}