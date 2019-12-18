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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct tid_ampdu_tx {int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  mtx; } ;
struct sta_info {TYPE_1__ ampdu_mlme; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sub_if_data {struct ieee80211_local* local; } ;
struct ieee80211_local {int /*<<< orphan*/  sta_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  HT_AGG_STATE_DRV_READY ; 
 int /*<<< orphan*/  HT_AGG_STATE_RESPONSE_RECEIVED ; 
 int /*<<< orphan*/  IEEE80211_NUM_TIDS ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  ht_dbg (struct ieee80211_sub_if_data*,char*,...) ; 
 int /*<<< orphan*/  ieee80211_agg_tx_operational (struct ieee80211_local*,struct sta_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct tid_ampdu_tx* rcu_dereference_protected_tid_tx (struct sta_info*,int /*<<< orphan*/ ) ; 
 struct sta_info* sta_info_get_bss (struct ieee80211_sub_if_data*,int /*<<< orphan*/ *) ; 
 int test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_api_start_tx_ba_cb (struct ieee80211_sub_if_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ieee80211_sub_if_data* vif_to_sdata (struct ieee80211_vif*) ; 

void ieee80211_start_tx_ba_cb(struct ieee80211_vif *vif, u8 *ra, u16 tid)
{
	struct ieee80211_sub_if_data *sdata = vif_to_sdata(vif);
	struct ieee80211_local *local = sdata->local;
	struct sta_info *sta;
	struct tid_ampdu_tx *tid_tx;

	trace_api_start_tx_ba_cb(sdata, ra, tid);

	if (tid >= IEEE80211_NUM_TIDS) {
		ht_dbg(sdata, "Bad TID value: tid = %d (>= %d)\n",
		       tid, IEEE80211_NUM_TIDS);
		return;
	}

	mutex_lock(&local->sta_mtx);
	sta = sta_info_get_bss(sdata, ra);
	if (!sta) {
		mutex_unlock(&local->sta_mtx);
		ht_dbg(sdata, "Could not find station: %pM\n", ra);
		return;
	}

	mutex_lock(&sta->ampdu_mlme.mtx);
	tid_tx = rcu_dereference_protected_tid_tx(sta, tid);

	if (WARN_ON(!tid_tx)) {
		ht_dbg(sdata, "addBA was not requested!\n");
		goto unlock;
	}

	if (WARN_ON(test_and_set_bit(HT_AGG_STATE_DRV_READY, &tid_tx->state)))
		goto unlock;

	if (test_bit(HT_AGG_STATE_RESPONSE_RECEIVED, &tid_tx->state))
		ieee80211_agg_tx_operational(local, sta, tid);

 unlock:
	mutex_unlock(&sta->ampdu_mlme.mtx);
	mutex_unlock(&local->sta_mtx);
}