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
struct brcms_hardware {int boardflags; TYPE_1__* band; } ;
struct brcms_c_info {struct brcms_hardware* hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  phyrev; } ;

/* Variables and functions */
 int BFL_NOPLLDOWN ; 
 scalar_t__ BRCMS_ISNPHY (TYPE_1__*) ; 
 size_t MHF1 ; 
 int /*<<< orphan*/  MHF1_FORCEFASTCLK ; 
 int /*<<< orphan*/  MHF1_IQSWAP_WAR ; 
 size_t MHF2 ; 
 int /*<<< orphan*/  MHF2_NPHY40MHZ_WAR ; 
 int MHFMAX ; 
 scalar_t__ NREV_LT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
brcms_c_mhfdef(struct brcms_c_info *wlc, u16 *mhfs, u16 mhf2_init)
{
	struct brcms_hardware *wlc_hw = wlc->hw;

	memset(mhfs, 0, MHFMAX * sizeof(u16));

	mhfs[MHF2] |= mhf2_init;

	/* prohibit use of slowclock on multifunction boards */
	if (wlc_hw->boardflags & BFL_NOPLLDOWN)
		mhfs[MHF1] |= MHF1_FORCEFASTCLK;

	if (BRCMS_ISNPHY(wlc_hw->band) && NREV_LT(wlc_hw->band->phyrev, 2)) {
		mhfs[MHF2] |= MHF2_NPHY40MHZ_WAR;
		mhfs[MHF1] |= MHF1_IQSWAP_WAR;
	}
}