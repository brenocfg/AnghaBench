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
struct iwl_mvm_vif {scalar_t__ ap_sta_id; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; int /*<<< orphan*/  hw; int /*<<< orphan*/  last_bt_notif; } ;
struct iwl_bt_iterator_data {int reduced_tx_power; scalar_t__ num_bss_ifaces; struct iwl_mvm* mvm; } ;
struct TYPE_2__ {int /*<<< orphan*/  bssid; } ;
struct ieee80211_vif {TYPE_1__ bss_conf; scalar_t__ drv_priv; } ;
typedef  enum ieee80211_rssi_event { ____Placeholder_ieee80211_rssi_event } ieee80211_rssi_event ;

/* Variables and functions */
 int /*<<< orphan*/  BT_MBOX_MSG (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_NORMAL ; 
 int /*<<< orphan*/  IWL_DEBUG_COEX (struct iwl_mvm*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 scalar_t__ IWL_MVM_STATION_COUNT ; 
 int /*<<< orphan*/  OPEN_CON_2 ; 
 int RSSI_EVENT_HIGH ; 
 int RSSI_EVENT_LOW ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iwl_bt_iterator_data*) ; 
 scalar_t__ is_loose_coex () ; 
 int iwl_mvm_bt_coex_reduced_txp (struct iwl_mvm*,scalar_t__,int) ; 
 int /*<<< orphan*/  iwl_mvm_bt_rssi_iterator ; 
 scalar_t__ iwl_mvm_bt_udpate_ctrl_kill_msk (struct iwl_mvm*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void iwl_mvm_bt_rssi_event(struct iwl_mvm *mvm, struct ieee80211_vif *vif,
			   enum ieee80211_rssi_event rssi_event)
{
	struct iwl_mvm_vif *mvmvif = (void *)vif->drv_priv;
	struct iwl_bt_iterator_data data = {
		.mvm = mvm,
		.reduced_tx_power = true,
	};
	int ret;

	mutex_lock(&mvm->mutex);

	/* Rssi update while not associated ?! */
	if (WARN_ON_ONCE(mvmvif->ap_sta_id == IWL_MVM_STATION_COUNT))
		goto out_unlock;

	/* No open connection - reports should be disabled */
	if (!BT_MBOX_MSG(&mvm->last_bt_notif, 3, OPEN_CON_2))
		goto out_unlock;

	IWL_DEBUG_COEX(mvm, "RSSI for %pM is now %s\n", vif->bss_conf.bssid,
		       rssi_event == RSSI_EVENT_HIGH ? "HIGH" : "LOW");

	/*
	 * Check if rssi is good enough for reduced Tx power, but not in loose
	 * scheme.
	 */
	if (rssi_event == RSSI_EVENT_LOW || is_loose_coex())
		ret = iwl_mvm_bt_coex_reduced_txp(mvm, mvmvif->ap_sta_id,
						  false);
	else
		ret = iwl_mvm_bt_coex_reduced_txp(mvm, mvmvif->ap_sta_id, true);

	if (ret)
		IWL_ERR(mvm, "couldn't send BT_CONFIG HCMD upon RSSI event\n");

	ieee80211_iterate_active_interfaces_atomic(
		mvm->hw, IEEE80211_IFACE_ITER_NORMAL,
		iwl_mvm_bt_rssi_iterator, &data);

	/*
	 * If there are no BSS / P2P client interfaces, reduced Tx Power is
	 * irrelevant since it is based on the RSSI coming from the beacon.
	 * Use BT_KILL_MSK_DEFAULT in that case.
	 */
	data.reduced_tx_power = data.reduced_tx_power && data.num_bss_ifaces;

	if (iwl_mvm_bt_udpate_ctrl_kill_msk(mvm, data.reduced_tx_power))
		IWL_ERR(mvm, "Failed to update the ctrl_kill_msk\n");

 out_unlock:
	mutex_unlock(&mvm->mutex);
}