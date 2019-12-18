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
struct iwl_mvm {int dummy; } ;
struct iwl_lq_sta {int dummy; } ;
struct ieee80211_sta {scalar_t__ addr; } ;
struct TYPE_2__ {scalar_t__ auto_agg; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ IWL_AGG_LOAD_THRESHOLD ; 
 int /*<<< orphan*/  IWL_DEBUG_HT (struct iwl_mvm*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,scalar_t__) ; 
 int ieee80211_start_tx_ba_session (struct ieee80211_sta*,scalar_t__,int) ; 
 int /*<<< orphan*/  ieee80211_stop_tx_ba_session (struct ieee80211_sta*,scalar_t__) ; 
 TYPE_1__ iwlwifi_mod_params ; 
 scalar_t__ rs_tl_get_load (struct iwl_lq_sta*,scalar_t__) ; 

__attribute__((used)) static int rs_tl_turn_on_agg_for_tid(struct iwl_mvm *mvm,
				      struct iwl_lq_sta *lq_data, u8 tid,
				      struct ieee80211_sta *sta)
{
	int ret = -EAGAIN;
	u32 load;

	load = rs_tl_get_load(lq_data, tid);

	if ((iwlwifi_mod_params.auto_agg) || (load > IWL_AGG_LOAD_THRESHOLD)) {
		IWL_DEBUG_HT(mvm, "Starting Tx agg: STA: %pM tid: %d\n",
			     sta->addr, tid);
		ret = ieee80211_start_tx_ba_session(sta, tid, 5000);
		if (ret == -EAGAIN) {
			/*
			 * driver and mac80211 is out of sync
			 * this might be cause by reloading firmware
			 * stop the tx ba session here
			 */
			IWL_ERR(mvm, "Fail start Tx agg on tid: %d\n",
				tid);
			ieee80211_stop_tx_ba_session(sta, tid);
		}
	} else {
		IWL_DEBUG_HT(mvm,
			     "Aggregation not enabled for tid %d because load = %u\n",
			     tid, load);
	}
	return ret;
}