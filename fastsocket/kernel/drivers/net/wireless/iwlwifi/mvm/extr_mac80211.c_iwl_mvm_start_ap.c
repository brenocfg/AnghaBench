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
struct iwl_mvm_vif {int ap_active; int /*<<< orphan*/  bcast_sta; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; scalar_t__ p2p_device_vif; } ;
struct ieee80211_vif {scalar_t__ p2p; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 int iwl_mvm_binding_add_vif (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_binding_remove_vif (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int iwl_mvm_mac_ctxt_add (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int iwl_mvm_mac_ctxt_beacon_changed (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_mac_ctxt_changed (struct iwl_mvm*,scalar_t__) ; 
 int /*<<< orphan*/  iwl_mvm_mac_ctxt_remove (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int iwl_mvm_send_bcast_sta (struct iwl_mvm*,struct ieee80211_vif*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_mvm_send_rm_bcast_sta (struct iwl_mvm*,int /*<<< orphan*/ *) ; 
 int iwl_mvm_update_quotas (struct iwl_mvm*,struct ieee80211_vif*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_mvm_start_ap(struct ieee80211_hw *hw, struct ieee80211_vif *vif)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	int ret;

	mutex_lock(&mvm->mutex);

	/* Send the beacon template */
	ret = iwl_mvm_mac_ctxt_beacon_changed(mvm, vif);
	if (ret)
		goto out_unlock;

	/* Add the mac context */
	ret = iwl_mvm_mac_ctxt_add(mvm, vif);
	if (ret)
		goto out_unlock;

	/* Perform the binding */
	ret = iwl_mvm_binding_add_vif(mvm, vif);
	if (ret)
		goto out_remove;

	mvmvif->ap_active = true;

	/* Send the bcast station. At this stage the TBTT and DTIM time events
	 * are added and applied to the scheduler */
	ret = iwl_mvm_send_bcast_sta(mvm, vif, &mvmvif->bcast_sta);
	if (ret)
		goto out_unbind;

	ret = iwl_mvm_update_quotas(mvm, vif);
	if (ret)
		goto out_rm_bcast;

	/* Need to update the P2P Device MAC */
	if (vif->p2p && mvm->p2p_device_vif)
		iwl_mvm_mac_ctxt_changed(mvm, mvm->p2p_device_vif);

	mutex_unlock(&mvm->mutex);
	return 0;

out_rm_bcast:
	iwl_mvm_send_rm_bcast_sta(mvm, &mvmvif->bcast_sta);
out_unbind:
	iwl_mvm_binding_remove_vif(mvm, vif);
out_remove:
	iwl_mvm_mac_ctxt_remove(mvm, vif);
out_unlock:
	mutex_unlock(&mvm->mutex);
	return ret;
}