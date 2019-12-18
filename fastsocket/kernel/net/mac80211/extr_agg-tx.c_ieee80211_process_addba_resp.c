#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct tid_ampdu_tx {scalar_t__ dialog_token; int buf_size; int /*<<< orphan*/  last_tx; scalar_t__ timeout; int /*<<< orphan*/  session_timer; int /*<<< orphan*/  state; int /*<<< orphan*/  addba_resp_timer; } ;
struct TYPE_12__ {int /*<<< orphan*/  mtx; scalar_t__* addba_req_num; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
struct sta_info {TYPE_6__ ampdu_mlme; TYPE_1__ sta; int /*<<< orphan*/  sdata; } ;
struct TYPE_8__ {scalar_t__ dialog_token; int /*<<< orphan*/  status; int /*<<< orphan*/  capab; } ;
struct TYPE_9__ {TYPE_2__ addba_resp; } ;
struct TYPE_10__ {TYPE_3__ u; } ;
struct TYPE_11__ {TYPE_4__ action; } ;
struct ieee80211_mgmt {TYPE_5__ u; } ;
struct ieee80211_local {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGG_STOP_DECLINED ; 
 int /*<<< orphan*/  HT_AGG_STATE_DRV_READY ; 
 int /*<<< orphan*/  HT_AGG_STATE_RESPONSE_RECEIVED ; 
 int /*<<< orphan*/  HT_AGG_STATE_STOPPING ; 
 int /*<<< orphan*/  HT_AGG_STATE_WANT_STOP ; 
 int IEEE80211_ADDBA_PARAM_BUF_SIZE_MASK ; 
 int IEEE80211_ADDBA_PARAM_TID_MASK ; 
 int /*<<< orphan*/  TU_TO_EXP_TIME (scalar_t__) ; 
 scalar_t__ WLAN_STATUS_SUCCESS ; 
 int /*<<< orphan*/  ___ieee80211_stop_tx_ba_session (struct sta_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ht_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ieee80211_agg_tx_operational (struct ieee80211_local*,struct sta_info*,int) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct tid_ampdu_tx* rcu_dereference_protected_tid_tx (struct sta_info*,int) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ieee80211_process_addba_resp(struct ieee80211_local *local,
				  struct sta_info *sta,
				  struct ieee80211_mgmt *mgmt,
				  size_t len)
{
	struct tid_ampdu_tx *tid_tx;
	u16 capab, tid;
	u8 buf_size;

	capab = le16_to_cpu(mgmt->u.action.u.addba_resp.capab);
	tid = (capab & IEEE80211_ADDBA_PARAM_TID_MASK) >> 2;
	buf_size = (capab & IEEE80211_ADDBA_PARAM_BUF_SIZE_MASK) >> 6;

	mutex_lock(&sta->ampdu_mlme.mtx);

	tid_tx = rcu_dereference_protected_tid_tx(sta, tid);
	if (!tid_tx)
		goto out;

	if (mgmt->u.action.u.addba_resp.dialog_token != tid_tx->dialog_token) {
		ht_dbg(sta->sdata, "wrong addBA response token, %pM tid %d\n",
		       sta->sta.addr, tid);
		goto out;
	}

	del_timer_sync(&tid_tx->addba_resp_timer);

	ht_dbg(sta->sdata, "switched off addBA timer for %pM tid %d\n",
	       sta->sta.addr, tid);

	/*
	 * addba_resp_timer may have fired before we got here, and
	 * caused WANT_STOP to be set. If the stop then was already
	 * processed further, STOPPING might be set.
	 */
	if (test_bit(HT_AGG_STATE_WANT_STOP, &tid_tx->state) ||
	    test_bit(HT_AGG_STATE_STOPPING, &tid_tx->state)) {
		ht_dbg(sta->sdata,
		       "got addBA resp for %pM tid %d but we already gave up\n",
		       sta->sta.addr, tid);
		goto out;
	}

	/*
	 * IEEE 802.11-2007 7.3.1.14:
	 * In an ADDBA Response frame, when the Status Code field
	 * is set to 0, the Buffer Size subfield is set to a value
	 * of at least 1.
	 */
	if (le16_to_cpu(mgmt->u.action.u.addba_resp.status)
			== WLAN_STATUS_SUCCESS && buf_size) {
		if (test_and_set_bit(HT_AGG_STATE_RESPONSE_RECEIVED,
				     &tid_tx->state)) {
			/* ignore duplicate response */
			goto out;
		}

		tid_tx->buf_size = buf_size;

		if (test_bit(HT_AGG_STATE_DRV_READY, &tid_tx->state))
			ieee80211_agg_tx_operational(local, sta, tid);

		sta->ampdu_mlme.addba_req_num[tid] = 0;

		if (tid_tx->timeout) {
			mod_timer(&tid_tx->session_timer,
				  TU_TO_EXP_TIME(tid_tx->timeout));
			tid_tx->last_tx = jiffies;
		}

	} else {
		___ieee80211_stop_tx_ba_session(sta, tid, AGG_STOP_DECLINED);
	}

 out:
	mutex_unlock(&sta->ampdu_mlme.mtx);
}