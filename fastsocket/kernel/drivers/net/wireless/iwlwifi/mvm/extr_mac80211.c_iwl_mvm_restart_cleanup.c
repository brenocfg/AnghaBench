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
struct iwl_mvm {scalar_t__ vif_count; int /*<<< orphan*/  hw; int /*<<< orphan*/  sta_drained; int /*<<< orphan*/  fw_key_table; int /*<<< orphan*/  scan_status; int /*<<< orphan*/  trans; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_RESUME_ALL ; 
 int /*<<< orphan*/  IWL_MVM_SCAN_NONE ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iwl_mvm*) ; 
 int /*<<< orphan*/  ieee80211_remain_on_channel_expired (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_wake_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_cleanup_iterator ; 
 int /*<<< orphan*/  iwl_trans_stop_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_trans_stop_hw (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void iwl_mvm_restart_cleanup(struct iwl_mvm *mvm)
{
	iwl_trans_stop_device(mvm->trans);
	iwl_trans_stop_hw(mvm->trans, false);

	mvm->scan_status = IWL_MVM_SCAN_NONE;

	/* just in case one was running */
	ieee80211_remain_on_channel_expired(mvm->hw);

	ieee80211_iterate_active_interfaces_atomic(
		mvm->hw, IEEE80211_IFACE_ITER_RESUME_ALL,
		iwl_mvm_cleanup_iterator, mvm);

	memset(mvm->fw_key_table, 0, sizeof(mvm->fw_key_table));
	memset(mvm->sta_drained, 0, sizeof(mvm->sta_drained));

	ieee80211_wake_queues(mvm->hw);

	mvm->vif_count = 0;
}