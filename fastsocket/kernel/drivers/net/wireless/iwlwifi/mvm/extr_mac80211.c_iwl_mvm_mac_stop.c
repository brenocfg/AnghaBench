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
struct iwl_mvm {int /*<<< orphan*/  async_handlers_wk; int /*<<< orphan*/  mutex; int /*<<< orphan*/  aux_sta; int /*<<< orphan*/  trans; int /*<<< orphan*/  roc_done_wk; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_mvm_async_handlers_purge (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_dealloc_int_sta (struct iwl_mvm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_trans_stop_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_trans_stop_hw (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_mac_stop(struct ieee80211_hw *hw)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);

	flush_work(&mvm->async_handlers_wk);

	mutex_lock(&mvm->mutex);
	/* async_handlers_wk is now blocked */

	/*
	 * The work item could be running or queued if the
	 * ROC time event stops just as we get here.
	 */
	cancel_work_sync(&mvm->roc_done_wk);

	iwl_trans_stop_device(mvm->trans);
	iwl_trans_stop_hw(mvm->trans, false);

	iwl_mvm_async_handlers_purge(mvm);
	/* async_handlers_list is empty and will stay empty: HW is stopped */

	/* the fw is stopped, the aux sta is dead: clean up driver state */
	iwl_mvm_dealloc_int_sta(mvm, &mvm->aux_sta);

	mutex_unlock(&mvm->mutex);

	/*
	 * The worker might have been waiting for the mutex, let it run and
	 * discover that its list is now empty.
	 */
	cancel_work_sync(&mvm->async_handlers_wk);
}