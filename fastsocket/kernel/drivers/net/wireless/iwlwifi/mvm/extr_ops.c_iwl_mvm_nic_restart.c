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
struct iwl_mvm {scalar_t__ cur_ucode; int scan_status; int /*<<< orphan*/  hw; int /*<<< orphan*/  status; int /*<<< orphan*/  notif_wait; } ;
struct TYPE_2__ {scalar_t__ restart_fw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
#define  IWL_MVM_SCAN_NONE 129 
#define  IWL_MVM_SCAN_OS 128 
 int /*<<< orphan*/  IWL_MVM_STATUS_IN_HW_RESTART ; 
 scalar_t__ IWL_UCODE_REGULAR ; 
 int /*<<< orphan*/  ieee80211_restart_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_scan_completed (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwl_abort_notification_waits (int /*<<< orphan*/ *) ; 
 TYPE_1__ iwlwifi_mod_params ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_nic_restart(struct iwl_mvm *mvm)
{
	iwl_abort_notification_waits(&mvm->notif_wait);

	/*
	 * If we're restarting already, don't cycle restarts.
	 * If INIT fw asserted, it will likely fail again.
	 * If WoWLAN fw asserted, don't restart either, mac80211
	 * can't recover this since we're already half suspended.
	 */
	if (test_and_set_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status)) {
		IWL_ERR(mvm, "Firmware error during reconfiguration! Abort.\n");
	} else if (mvm->cur_ucode == IWL_UCODE_REGULAR &&
		   iwlwifi_mod_params.restart_fw) {
		/*
		 * This is a bit racy, but worst case we tell mac80211 about
		 * a stopped/aborted (sched) scan when that was already done
		 * which is not a problem. It is necessary to abort any scan
		 * here because mac80211 requires having the scan cleared
		 * before restarting.
		 * We'll reset the scan_status to NONE in restart cleanup in
		 * the next start() call from mac80211.
		 */
		switch (mvm->scan_status) {
		case IWL_MVM_SCAN_NONE:
			break;
		case IWL_MVM_SCAN_OS:
			ieee80211_scan_completed(mvm->hw, true);
			break;
		}

		ieee80211_restart_hw(mvm->hw);
	}
}