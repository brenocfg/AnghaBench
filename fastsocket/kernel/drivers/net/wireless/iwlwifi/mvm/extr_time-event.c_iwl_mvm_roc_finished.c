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
struct iwl_mvm {int /*<<< orphan*/  roc_done_wk; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_MVM_STATUS_ROC_RUNNING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_roc_finished(struct iwl_mvm *mvm)
{
	/*
	 * First, clear the ROC_RUNNING status bit. This will cause the TX
	 * path to drop offchannel transmissions. That would also be done
	 * by mac80211, but it is racy, in particular in the case that the
	 * time event actually completed in the firmware (which is handled
	 * in iwl_mvm_te_handle_notif).
	 */
	clear_bit(IWL_MVM_STATUS_ROC_RUNNING, &mvm->status);

	/*
	 * Of course, our status bit is just as racy as mac80211, so in
	 * addition, fire off the work struct which will drop all frames
	 * from the hardware queues that made it through the race. First
	 * it will of course synchronize the TX path to make sure that
	 * any *new* TX will be rejected.
	 */
	schedule_work(&mvm->roc_done_wk);
}