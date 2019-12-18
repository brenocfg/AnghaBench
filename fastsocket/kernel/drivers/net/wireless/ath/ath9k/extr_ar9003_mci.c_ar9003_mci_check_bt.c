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
struct ath9k_hw_mci {scalar_t__ bt_state; int query_bt; int need_flush_btinfo; int /*<<< orphan*/  ready; } ;
struct TYPE_2__ {struct ath9k_hw_mci mci; } ;
struct ath_hw {TYPE_1__ btcoex_hw; } ;

/* Variables and functions */
 scalar_t__ MCI_BT_AWAKE ; 
 int /*<<< orphan*/  ar9003_mci_2g5g_switch (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ar9003_mci_sync_bt_state (struct ath_hw*) ; 

void ar9003_mci_check_bt(struct ath_hw *ah)
{
	struct ath9k_hw_mci *mci_hw = &ah->btcoex_hw.mci;

	if (!mci_hw->ready)
		return;

	/*
	 * check BT state again to make
	 * sure it's not changed.
	 */
	ar9003_mci_sync_bt_state(ah);
	ar9003_mci_2g5g_switch(ah, true);

	if ((mci_hw->bt_state == MCI_BT_AWAKE) &&
	    (mci_hw->query_bt == true)) {
		mci_hw->need_flush_btinfo = true;
	}
}