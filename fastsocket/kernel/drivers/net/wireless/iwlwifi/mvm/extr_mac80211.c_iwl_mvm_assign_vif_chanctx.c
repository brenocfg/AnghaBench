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
struct iwl_mvm_vif {int monitor_active; struct iwl_mvm_phy_ctxt* phy_ctxt; } ;
struct iwl_mvm_phy_ctxt {int dummy; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int type; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_chanctx_conf {scalar_t__ drv_priv; } ;

/* Variables and functions */
 int EINVAL ; 
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
#define  NL80211_IFTYPE_ADHOC 131 
#define  NL80211_IFTYPE_AP 130 
#define  NL80211_IFTYPE_MONITOR 129 
#define  NL80211_IFTYPE_STATION 128 
 int iwl_mvm_binding_add_vif (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_binding_remove_vif (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int iwl_mvm_update_quotas (struct iwl_mvm*,struct ieee80211_vif*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_mvm_assign_vif_chanctx(struct ieee80211_hw *hw,
				      struct ieee80211_vif *vif,
				      struct ieee80211_chanctx_conf *ctx)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	struct iwl_mvm_phy_ctxt *phyctx = (void *)ctx->drv_priv;
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	int ret;

	mutex_lock(&mvm->mutex);

	mvmvif->phy_ctxt = phyctx;

	switch (vif->type) {
	case NL80211_IFTYPE_AP:
		/*
		 * The AP binding flow is handled as part of the start_ap flow
		 * (in bss_info_changed).
		 */
		ret = 0;
		goto out_unlock;
	case NL80211_IFTYPE_STATION:
	case NL80211_IFTYPE_ADHOC:
	case NL80211_IFTYPE_MONITOR:
		break;
	default:
		ret = -EINVAL;
		goto out_unlock;
	}

	ret = iwl_mvm_binding_add_vif(mvm, vif);
	if (ret)
		goto out_unlock;

	/*
	 * Setting the quota at this stage is only required for monitor
	 * interfaces. For the other types, the bss_info changed flow
	 * will handle quota settings.
	 */
	if (vif->type == NL80211_IFTYPE_MONITOR) {
		mvmvif->monitor_active = true;
		ret = iwl_mvm_update_quotas(mvm, vif);
		if (ret)
			goto out_remove_binding;
	}

	goto out_unlock;

 out_remove_binding:
	iwl_mvm_binding_remove_vif(mvm, vif);
 out_unlock:
	mutex_unlock(&mvm->mutex);
	if (ret)
		mvmvif->phy_ctxt = NULL;
	return ret;
}