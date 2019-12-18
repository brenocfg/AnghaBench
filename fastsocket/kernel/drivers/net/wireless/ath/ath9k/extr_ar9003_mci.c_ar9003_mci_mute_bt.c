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
struct ath_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_MCI_MSG_ATTRIBUTES_TABLE ; 
 int /*<<< orphan*/  AR_MCI_TX_CTRL ; 
 int /*<<< orphan*/  AR_MCI_TX_CTRL_DISABLE_LNA_UPDATE ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar9003_mci_send_lna_take (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ar9003_mci_send_sys_sleeping (struct ath_hw*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ar9003_mci_mute_bt(struct ath_hw *ah)
{
	/* disable all MCI messages */
	REG_WRITE(ah, AR_MCI_MSG_ATTRIBUTES_TABLE, 0xffff0000);
	REG_SET_BIT(ah, AR_MCI_TX_CTRL, AR_MCI_TX_CTRL_DISABLE_LNA_UPDATE);

	/* wait pending HW messages to flush out */
	udelay(10);

	/*
	 * Send LNA_TAKE and SYS_SLEEPING when
	 * 1. reset not after resuming from full sleep
	 * 2. before reset MCI RX, to quiet BT and avoid MCI RX misalignment
	 */
	ar9003_mci_send_lna_take(ah, true);

	udelay(5);

	ar9003_mci_send_sys_sleeping(ah, true);
}