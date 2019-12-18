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
typedef  scalar_t__ u8 ;
struct tid_ampdu_tx {scalar_t__ stop_initiator; scalar_t__ tx_stop; int /*<<< orphan*/  state; } ;
struct TYPE_4__ {int /*<<< orphan*/  mtx; } ;
struct TYPE_3__ {scalar_t__* addr; } ;
struct sta_info {TYPE_2__ ampdu_mlme; int /*<<< orphan*/  lock; int /*<<< orphan*/  sdata; TYPE_1__ sta; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sub_if_data {struct ieee80211_local* local; } ;
struct ieee80211_local {int /*<<< orphan*/  sta_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  HT_AGG_STATE_STOPPING ; 
 scalar_t__ IEEE80211_NUM_TIDS ; 
 scalar_t__ WLAN_BACK_INITIATOR ; 
 int /*<<< orphan*/  WLAN_REASON_QSTA_NOT_USE ; 
 int /*<<< orphan*/  ht_dbg (struct ieee80211_sub_if_data*,char*,scalar_t__*,...) ; 
 int /*<<< orphan*/  ieee80211_remove_tid_tx (struct sta_info*,scalar_t__) ; 
 int /*<<< orphan*/  ieee80211_send_delba (int /*<<< orphan*/ ,scalar_t__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct tid_ampdu_tx* rcu_dereference_protected_tid_tx (struct sta_info*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct sta_info* sta_info_get_bss (struct ieee80211_sub_if_data*,scalar_t__*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_api_stop_tx_ba_cb (struct ieee80211_sub_if_data*,scalar_t__*,scalar_t__) ; 
 struct ieee80211_sub_if_data* vif_to_sdata (struct ieee80211_vif*) ; 

void ieee80211_stop_tx_ba_cb(struct ieee80211_vif *vif, u8 *ra, u8 tid)
{
	struct ieee80211_sub_if_data *sdata = vif_to_sdata(vif);
	struct ieee80211_local *local = sdata->local;
	struct sta_info *sta;
	struct tid_ampdu_tx *tid_tx;

	trace_api_stop_tx_ba_cb(sdata, ra, tid);

	if (tid >= IEEE80211_NUM_TIDS) {
		ht_dbg(sdata, "Bad TID value: tid = %d (>= %d)\n",
		       tid, IEEE80211_NUM_TIDS);
		return;
	}

	ht_dbg(sdata, "Stopping Tx BA session for %pM tid %d\n", ra, tid);

	mutex_lock(&local->sta_mtx);

	sta = sta_info_get_bss(sdata, ra);
	if (!sta) {
		ht_dbg(sdata, "Could not find station: %pM\n", ra);
		goto unlock;
	}

	mutex_lock(&sta->ampdu_mlme.mtx);
	spin_lock_bh(&sta->lock);
	tid_tx = rcu_dereference_protected_tid_tx(sta, tid);

	if (!tid_tx || !test_bit(HT_AGG_STATE_STOPPING, &tid_tx->state)) {
		ht_dbg(sdata,
		       "unexpected callback to A-MPDU stop for %pM tid %d\n",
		       sta->sta.addr, tid);
		goto unlock_sta;
	}

	if (tid_tx->stop_initiator == WLAN_BACK_INITIATOR && tid_tx->tx_stop)
		ieee80211_send_delba(sta->sdata, ra, tid,
			WLAN_BACK_INITIATOR, WLAN_REASON_QSTA_NOT_USE);

	ieee80211_remove_tid_tx(sta, tid);

 unlock_sta:
	spin_unlock_bh(&sta->lock);
	mutex_unlock(&sta->ampdu_mlme.mtx);
 unlock:
	mutex_unlock(&local->sta_mtx);
}