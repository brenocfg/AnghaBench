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
struct ath9k_hw_mci {scalar_t__ bt_state; int /*<<< orphan*/  wlan_channels_update; int /*<<< orphan*/ * wlan_channels; } ;
struct TYPE_2__ {struct ath9k_hw_mci mci; } ;
struct ath_hw {TYPE_1__ btcoex_hw; } ;

/* Variables and functions */
 scalar_t__ MCI_BT_SLEEP ; 
 int /*<<< orphan*/  MCI_GPM ; 
 int MCI_GPM_COEX_AGENT ; 
 int MCI_GPM_COEX_WLAN_CHANNELS ; 
 int /*<<< orphan*/  MCI_GPM_SET_TYPE_OPCODE (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ar9003_mci_send_message (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static void ar9003_mci_send_coex_wlan_channels(struct ath_hw *ah,
					       bool wait_done)
{
	struct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 *payload = &mci->wlan_channels[0];

	if (!mci->wlan_channels_update ||
	    (mci->bt_state == MCI_BT_SLEEP))
		return;

	MCI_GPM_SET_TYPE_OPCODE(payload, MCI_GPM_COEX_AGENT,
				MCI_GPM_COEX_WLAN_CHANNELS);
	ar9003_mci_send_message(ah, MCI_GPM, 0, payload, 16, wait_done, true);
	MCI_GPM_SET_TYPE_OPCODE(payload, 0xff, 0xff);
}