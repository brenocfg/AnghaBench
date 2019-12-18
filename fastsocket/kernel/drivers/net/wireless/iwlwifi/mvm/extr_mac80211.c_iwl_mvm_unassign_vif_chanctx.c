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
struct iwl_mvm_vif {int monitor_active; int /*<<< orphan*/ * phy_ctxt; int /*<<< orphan*/  time_event_data; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int type; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_chanctx_conf {int dummy; } ;

/* Variables and functions */
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 int NL80211_IFTYPE_AP ; 
#define  NL80211_IFTYPE_MONITOR 128 
 int /*<<< orphan*/  iwl_mvm_binding_remove_vif (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_remove_time_event (struct iwl_mvm*,struct iwl_mvm_vif*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_mvm_update_quotas (struct iwl_mvm*,int /*<<< orphan*/ *) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_unassign_vif_chanctx(struct ieee80211_hw *hw,
					 struct ieee80211_vif *vif,
					 struct ieee80211_chanctx_conf *ctx)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);

	mutex_lock(&mvm->mutex);

	iwl_mvm_remove_time_event(mvm, mvmvif, &mvmvif->time_event_data);

	if (vif->type == NL80211_IFTYPE_AP)
		goto out_unlock;

	switch (vif->type) {
	case NL80211_IFTYPE_MONITOR:
		mvmvif->monitor_active = false;
		iwl_mvm_update_quotas(mvm, NULL);
		break;
	default:
		break;
	}

	iwl_mvm_binding_remove_vif(mvm, vif);
out_unlock:
	mvmvif->phy_ctxt = NULL;
	mutex_unlock(&mvm->mutex);
}