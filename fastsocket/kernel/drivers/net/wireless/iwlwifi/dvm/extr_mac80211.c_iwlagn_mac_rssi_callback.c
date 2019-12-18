#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iwl_priv {int bt_enable_pspoll; int /*<<< orphan*/  mutex; TYPE_2__* cfg; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum ieee80211_rssi_event { ____Placeholder_ieee80211_rssi_event } ieee80211_rssi_event ;
struct TYPE_4__ {TYPE_1__* bt_params; } ;
struct TYPE_3__ {scalar_t__ advanced_bt_coexist; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_MAC80211 (struct iwl_priv*,char*) ; 
 struct iwl_priv* IWL_MAC80211_GET_DVM (struct ieee80211_hw*) ; 
 int RSSI_EVENT_HIGH ; 
 int RSSI_EVENT_LOW ; 
 int /*<<< orphan*/  iwlagn_send_advance_bt_config (struct iwl_priv*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwlagn_mac_rssi_callback(struct ieee80211_hw *hw,
				     struct ieee80211_vif *vif,
				     enum ieee80211_rssi_event rssi_event)
{
	struct iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);

	IWL_DEBUG_MAC80211(priv, "enter\n");
	mutex_lock(&priv->mutex);

	if (priv->cfg->bt_params &&
			priv->cfg->bt_params->advanced_bt_coexist) {
		if (rssi_event == RSSI_EVENT_LOW)
			priv->bt_enable_pspoll = true;
		else if (rssi_event == RSSI_EVENT_HIGH)
			priv->bt_enable_pspoll = false;

		iwlagn_send_advance_bt_config(priv);
	} else {
		IWL_DEBUG_MAC80211(priv, "Advanced BT coex disabled,"
				"ignoring RSSI callback\n");
	}

	mutex_unlock(&priv->mutex);
	IWL_DEBUG_MAC80211(priv, "leave\n");
}