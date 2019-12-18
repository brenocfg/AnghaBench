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
struct iwl_mvm {int /*<<< orphan*/  status; int /*<<< orphan*/  mutex; int /*<<< orphan*/  trans; int /*<<< orphan*/  hw; } ;
struct iwl_d3_iter_data {struct ieee80211_vif* vif; scalar_t__ error; struct iwl_mvm* mvm; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum iwl_d3_status { ____Placeholder_iwl_d3_status } iwl_d3_status ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_NORMAL ; 
 int IWL_D3_STATUS_ALIVE ; 
 int /*<<< orphan*/  IWL_INFO (struct iwl_mvm*,char*) ; 
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_IN_HW_RESTART ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iwl_d3_iter_data*) ; 
 int /*<<< orphan*/  ieee80211_resume_disconnect (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_d3_iface_iterator ; 
 int /*<<< orphan*/  iwl_mvm_query_wakeup_reasons (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int iwl_trans_d3_resume (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int iwl_mvm_resume(struct ieee80211_hw *hw)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	struct iwl_d3_iter_data resume_iter_data = {
		.mvm = mvm,
	};
	struct ieee80211_vif *vif = NULL;
	int ret;
	enum iwl_d3_status d3_status;

	mutex_lock(&mvm->mutex);

	/* get the BSS vif pointer again */
	ieee80211_iterate_active_interfaces_atomic(
		mvm->hw, IEEE80211_IFACE_ITER_NORMAL,
		iwl_mvm_d3_iface_iterator, &resume_iter_data);

	if (WARN_ON(resume_iter_data.error || !resume_iter_data.vif))
		goto out_unlock;

	vif = resume_iter_data.vif;

	ret = iwl_trans_d3_resume(mvm->trans, &d3_status);
	if (ret)
		goto out_unlock;

	if (d3_status != IWL_D3_STATUS_ALIVE) {
		IWL_INFO(mvm, "Device was reset during suspend\n");
		goto out_unlock;
	}

	iwl_mvm_query_wakeup_reasons(mvm, vif);

 out_unlock:
	mutex_unlock(&mvm->mutex);

	if (vif)
		ieee80211_resume_disconnect(vif);

	/* return 1 to reconfigure the device */
	set_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status);
	return 1;
}