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
struct ath9k_hw_mci {int ready; int /*<<< orphan*/  bt_state; } ;
struct TYPE_2__ {struct ath9k_hw_mci mci; } ;
struct ath_hw {TYPE_1__ btcoex_hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_BTCOEX_CTRL ; 
 int /*<<< orphan*/  MCI_BT_SLEEP ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9003_mci_disable_interrupt (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_mci_mute_bt (struct ath_hw*) ; 
 int /*<<< orphan*/  udelay (int) ; 

void ar9003_mci_stop_bt(struct ath_hw *ah, bool save_fullsleep)
{
	struct ath9k_hw_mci *mci_hw = &ah->btcoex_hw.mci;

	ar9003_mci_disable_interrupt(ah);

	if (mci_hw->ready && !save_fullsleep) {
		ar9003_mci_mute_bt(ah);
		udelay(20);
		REG_WRITE(ah, AR_BTCOEX_CTRL, 0);
	}

	mci_hw->bt_state = MCI_BT_SLEEP;
	mci_hw->ready = false;
}