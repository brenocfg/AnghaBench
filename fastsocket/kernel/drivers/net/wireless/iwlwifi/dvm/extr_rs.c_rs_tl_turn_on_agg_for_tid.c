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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct iwl_priv {scalar_t__ bt_traffic_load; } ;
struct iwl_lq_sta {int dummy; } ;
struct ieee80211_sta {scalar_t__ addr; } ;
struct TYPE_2__ {scalar_t__ auto_agg; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ IWL_AGG_LOAD_THRESHOLD ; 
 scalar_t__ IWL_BT_COEX_TRAFFIC_LOAD_HIGH ; 
 int /*<<< orphan*/  IWL_DEBUG_COEX (struct iwl_priv*,char*,scalar_t__) ; 
 int /*<<< orphan*/  IWL_DEBUG_HT (struct iwl_priv*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*,scalar_t__) ; 
 int ieee80211_start_tx_ba_session (struct ieee80211_sta*,scalar_t__,int) ; 
 int /*<<< orphan*/  ieee80211_stop_tx_ba_session (struct ieee80211_sta*,scalar_t__) ; 
 TYPE_1__ iwlwifi_mod_params ; 
 scalar_t__ rs_tl_get_load (struct iwl_lq_sta*,scalar_t__) ; 

__attribute__((used)) static int rs_tl_turn_on_agg_for_tid(struct iwl_priv *priv,
				      struct iwl_lq_sta *lq_data, u8 tid,
				      struct ieee80211_sta *sta)
{
	int ret = -EAGAIN;
	u32 load;

	/*
	 * Don't create TX aggregation sessions when in high
	 * BT traffic, as they would just be disrupted by BT.
	 */
	if (priv->bt_traffic_load >= IWL_BT_COEX_TRAFFIC_LOAD_HIGH) {
		IWL_DEBUG_COEX(priv,
			       "BT traffic (%d), no aggregation allowed\n",
			       priv->bt_traffic_load);
		return ret;
	}

	load = rs_tl_get_load(lq_data, tid);

	if ((iwlwifi_mod_params.auto_agg) || (load > IWL_AGG_LOAD_THRESHOLD)) {
		IWL_DEBUG_HT(priv, "Starting Tx agg: STA: %pM tid: %d\n",
				sta->addr, tid);
		ret = ieee80211_start_tx_ba_session(sta, tid, 5000);
		if (ret == -EAGAIN) {
			/*
			 * driver and mac80211 is out of sync
			 * this might be cause by reloading firmware
			 * stop the tx ba session here
			 */
			IWL_ERR(priv, "Fail start Tx agg on tid: %d\n",
				tid);
			ieee80211_stop_tx_ba_session(sta, tid);
		}
	} else {
		IWL_DEBUG_HT(priv, "Aggregation not enabled for tid %d "
			"because load = %u\n", tid, load);
	}
	return ret;
}