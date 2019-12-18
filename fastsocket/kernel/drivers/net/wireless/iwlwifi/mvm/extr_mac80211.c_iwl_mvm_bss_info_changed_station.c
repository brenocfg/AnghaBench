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
typedef  int u32 ;
struct iwl_mvm_vif {scalar_t__ ap_sta_id; int /*<<< orphan*/  time_event_data; } ;
struct iwl_mvm {int vif_count; } ;
struct ieee80211_vif {int /*<<< orphan*/  addr; } ;
struct ieee80211_bss_conf {scalar_t__ assoc; } ;

/* Variables and functions */
 int BSS_CHANGED_ASSOC ; 
 int BSS_CHANGED_DTIM_PERIOD ; 
 int BSS_CHANGED_PS ; 
 int /*<<< orphan*/  IWL_DEBUG_MAC80211 (struct iwl_mvm*,char*,int) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,...) ; 
 scalar_t__ IWL_MVM_STATION_COUNT ; 
 int /*<<< orphan*/  iwl_mvm_bt_coex_vif_assoc (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_configure_mcast_filter (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int iwl_mvm_mac_ctxt_changed (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int iwl_mvm_power_update_mode (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_remove_time_event (struct iwl_mvm*,struct iwl_mvm_vif*,int /*<<< orphan*/ *) ; 
 int iwl_mvm_rm_sta_id (struct iwl_mvm*,struct ieee80211_vif*,scalar_t__) ; 
 int iwl_mvm_update_quotas (struct iwl_mvm*,struct ieee80211_vif*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 

__attribute__((used)) static void iwl_mvm_bss_info_changed_station(struct iwl_mvm *mvm,
					     struct ieee80211_vif *vif,
					     struct ieee80211_bss_conf *bss_conf,
					     u32 changes)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	int ret;

	ret = iwl_mvm_mac_ctxt_changed(mvm, vif);
	if (ret)
		IWL_ERR(mvm, "failed to update MAC %pM\n", vif->addr);

	if (changes & BSS_CHANGED_ASSOC) {
		if (bss_conf->assoc) {
			/* add quota for this interface */
			ret = iwl_mvm_update_quotas(mvm, vif);
			if (ret) {
				IWL_ERR(mvm, "failed to update quotas\n");
				return;
			}
			iwl_mvm_bt_coex_vif_assoc(mvm, vif);
			iwl_mvm_configure_mcast_filter(mvm, vif);
		} else if (mvmvif->ap_sta_id != IWL_MVM_STATION_COUNT) {
			/* remove AP station now that the MAC is unassoc */
			ret = iwl_mvm_rm_sta_id(mvm, vif, mvmvif->ap_sta_id);
			if (ret)
				IWL_ERR(mvm, "failed to remove AP station\n");
			mvmvif->ap_sta_id = IWL_MVM_STATION_COUNT;
			/* remove quota for this interface */
			ret = iwl_mvm_update_quotas(mvm, NULL);
			if (ret)
				IWL_ERR(mvm, "failed to update quotas\n");
		}
	} else if (changes & BSS_CHANGED_DTIM_PERIOD) {
		/*
		 * We received a beacon _after_ association so
		 * remove the session protection.
		 */
		iwl_mvm_remove_time_event(mvm, mvmvif,
					  &mvmvif->time_event_data);
	} else if (changes & BSS_CHANGED_PS) {
		/*
		 * TODO: remove this temporary code.
		 * Currently MVM FW supports power management only on single
		 * MAC. Avoid power mode update if more than one interface
		 * is active.
		 */
		IWL_DEBUG_MAC80211(mvm, "Currently %d interfaces active\n",
				   mvm->vif_count);
		if (mvm->vif_count == 1) {
			ret = iwl_mvm_power_update_mode(mvm, vif);
			if (ret)
				IWL_ERR(mvm, "failed to update power mode\n");
		}
	}
}