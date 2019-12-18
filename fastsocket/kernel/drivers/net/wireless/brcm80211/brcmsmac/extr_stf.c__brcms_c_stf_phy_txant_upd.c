#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct brcms_c_info {TYPE_1__* stf; int /*<<< orphan*/  hw; TYPE_2__* band; } ;
typedef  scalar_t__ s8 ;
struct TYPE_7__ {int /*<<< orphan*/  phyrev; } ;
struct TYPE_6__ {int phytxant; int txchain; scalar_t__ txant; } ;

/* Variables and functions */
 scalar_t__ ANT_TX_FORCE_0 ; 
 scalar_t__ ANT_TX_FORCE_1 ; 
 scalar_t__ BRCMS_ISLCNPHY (TYPE_2__*) ; 
 scalar_t__ BRCMS_ISNPHY (TYPE_2__*) ; 
 scalar_t__ BRCMS_ISSSLPNPHY (TYPE_2__*) ; 
 scalar_t__ BRCMS_PHY_11N_CAP (TYPE_2__*) ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NREV_LT (int /*<<< orphan*/ ,int) ; 
 int PHY_TXC_ANT_0 ; 
 int PHY_TXC_ANT_1 ; 
 int PHY_TXC_ANT_2 ; 
 int PHY_TXC_ANT_SHIFT ; 
 int PHY_TXC_LCNPHY_ANT_LAST ; 
 int PHY_TXC_OLD_ANT_0 ; 
 int PHY_TXC_OLD_ANT_1 ; 
 int PHY_TXC_OLD_ANT_LAST ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  brcms_b_txant_set (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _brcms_c_stf_phy_txant_upd(struct brcms_c_info *wlc)
{
	s8 txant;

	txant = (s8) wlc->stf->txant;
	if (BRCMS_PHY_11N_CAP(wlc->band)) {
		if (txant == ANT_TX_FORCE_0) {
			wlc->stf->phytxant = PHY_TXC_ANT_0;
		} else if (txant == ANT_TX_FORCE_1) {
			wlc->stf->phytxant = PHY_TXC_ANT_1;

			if (BRCMS_ISNPHY(wlc->band) &&
			    NREV_GE(wlc->band->phyrev, 3)
			    && NREV_LT(wlc->band->phyrev, 7))
				wlc->stf->phytxant = PHY_TXC_ANT_2;
		} else {
			if (BRCMS_ISLCNPHY(wlc->band) ||
			    BRCMS_ISSSLPNPHY(wlc->band))
				wlc->stf->phytxant = PHY_TXC_LCNPHY_ANT_LAST;
			else {
				/* catch out of sync wlc->stf->txcore */
				WARN_ON(wlc->stf->txchain <= 0);
				wlc->stf->phytxant =
				    wlc->stf->txchain << PHY_TXC_ANT_SHIFT;
			}
		}
	} else {
		if (txant == ANT_TX_FORCE_0)
			wlc->stf->phytxant = PHY_TXC_OLD_ANT_0;
		else if (txant == ANT_TX_FORCE_1)
			wlc->stf->phytxant = PHY_TXC_OLD_ANT_1;
		else
			wlc->stf->phytxant = PHY_TXC_OLD_ANT_LAST;
	}

	brcms_b_txant_set(wlc->hw, wlc->stf->phytxant);
}