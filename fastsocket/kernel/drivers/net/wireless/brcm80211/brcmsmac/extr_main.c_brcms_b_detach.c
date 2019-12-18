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
typedef  scalar_t__ uint ;
struct brcms_hw_band {int /*<<< orphan*/ * pi; } ;
struct brcms_hardware {scalar_t__ _nbands; int /*<<< orphan*/ * sih; int /*<<< orphan*/  physhim; int /*<<< orphan*/  phy_sh; struct brcms_hw_band** bandstate; struct brcms_hw_band* band; } ;
struct brcms_c_info {struct brcms_hardware* hw; } ;

/* Variables and functions */
 size_t OTHERBANDUNIT (struct brcms_c_info*) ; 
 int /*<<< orphan*/  ai_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brcms_b_detach_dmapio (struct brcms_hardware*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wlc_phy_shim_detach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int brcms_b_detach(struct brcms_c_info *wlc)
{
	uint i;
	struct brcms_hw_band *band;
	struct brcms_hardware *wlc_hw = wlc->hw;
	int callbacks;

	callbacks = 0;

	brcms_b_detach_dmapio(wlc_hw);

	band = wlc_hw->band;
	for (i = 0; i < wlc_hw->_nbands; i++) {
		if (band->pi) {
			/* Detach this band's phy */
			wlc_phy_detach(band->pi);
			band->pi = NULL;
		}
		band = wlc_hw->bandstate[OTHERBANDUNIT(wlc)];
	}

	/* Free shared phy state */
	kfree(wlc_hw->phy_sh);

	wlc_phy_shim_detach(wlc_hw->physhim);

	if (wlc_hw->sih) {
		ai_detach(wlc_hw->sih);
		wlc_hw->sih = NULL;
	}

	return callbacks;

}