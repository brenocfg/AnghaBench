#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_8__ {int /*<<< orphan*/  sta_hlid_map; int /*<<< orphan*/ * ucast_rate_idx; int /*<<< orphan*/  bcast_rate_idx; int /*<<< orphan*/  mgmt_rate_idx; void* global_hlid; void* bcast_hlid; } ;
struct TYPE_7__ {int /*<<< orphan*/  klv_template_id; int /*<<< orphan*/  p2p_rate_idx; int /*<<< orphan*/  ap_rate_idx; int /*<<< orphan*/  basic_rate_idx; void* hlid; } ;
struct wl12xx_vif {scalar_t__ bss_type; int /*<<< orphan*/  connection_loss_work; int /*<<< orphan*/  rx_streaming_disable_work; int /*<<< orphan*/  rx_streaming_enable_work; int /*<<< orphan*/  rx_streaming_timer; void* dev_role_id; void* role_id; TYPE_3__ ap; int /*<<< orphan*/  list; int /*<<< orphan*/ * probereq; TYPE_2__ sta; void* dev_hlid; int /*<<< orphan*/  flags; } ;
struct TYPE_9__ {scalar_t__ sta_sleep_auth; } ;
struct TYPE_10__ {TYPE_4__ conn; } ;
struct TYPE_6__ {scalar_t__ state; int /*<<< orphan*/ * req; int /*<<< orphan*/  scanned_ch; } ;
struct wl1271 {scalar_t__ state; scalar_t__ ap_count; int /*<<< orphan*/  mutex; TYPE_5__ conf; scalar_t__ sta_count; int /*<<< orphan*/  flags; struct wl12xx_vif* last_wlvif; int /*<<< orphan*/  hw; struct ieee80211_vif* roc_vif; struct wl12xx_vif* sched_vif; TYPE_1__ scan; struct wl12xx_vif* scan_wlvif; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 scalar_t__ BSS_TYPE_AP_BSS ; 
 scalar_t__ BSS_TYPE_IBSS ; 
 scalar_t__ BSS_TYPE_STA_BSS ; 
 int CONF_TX_MAX_AC_COUNT ; 
 int /*<<< orphan*/  DEBUG_MAC80211 ; 
 int /*<<< orphan*/  WL1271_FLAG_INTENDED_FW_RECOVERY ; 
 int /*<<< orphan*/  WL1271_FLAG_RECOVERY_IN_PROGRESS ; 
 scalar_t__ WL1271_PSM_ELP ; 
 scalar_t__ WL1271_PSM_ILLEGAL ; 
 scalar_t__ WL1271_SCAN_STATE_IDLE ; 
 void* WL12XX_INVALID_LINK_ID ; 
 void* WL12XX_INVALID_ROLE_ID ; 
 scalar_t__ WLCORE_STATE_OFF ; 
 int /*<<< orphan*/  WLVIF_FLAG_INITIALIZED ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_remain_on_channel_expired (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_scan_completed (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ieee80211_sched_scan_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl1271_acx_sleep_auth (struct wl1271*,scalar_t__) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_free_ap_keys (struct wl1271*,struct wl12xx_vif*) ; 
 int /*<<< orphan*/  wl1271_info (char*) ; 
 int /*<<< orphan*/  wl1271_ps_elp_sleep (struct wl1271*) ; 
 int wl1271_ps_elp_wakeup (struct wl1271*) ; 
 int wl12xx_cmd_role_disable (struct wl1271*,void**) ; 
 scalar_t__ wl12xx_dev_role_started (struct wl12xx_vif*) ; 
 int /*<<< orphan*/  wl12xx_free_rate_policy (struct wl1271*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl12xx_rearm_tx_watchdog_locked (struct wl1271*) ; 
 int /*<<< orphan*/  wl12xx_stop_dev (struct wl1271*,struct wl12xx_vif*) ; 
 int /*<<< orphan*/  wl12xx_tx_reset_wlvif (struct wl1271*,struct wl12xx_vif*) ; 
 struct wl12xx_vif* wl12xx_vif_to_data (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  wlcore_free_klv_template (struct wl1271*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __wl1271_op_remove_interface(struct wl1271 *wl,
					 struct ieee80211_vif *vif,
					 bool reset_tx_queues)
{
	struct wl12xx_vif *wlvif = wl12xx_vif_to_data(vif);
	int i, ret;
	bool is_ap = (wlvif->bss_type == BSS_TYPE_AP_BSS);

	wl1271_debug(DEBUG_MAC80211, "mac80211 remove interface");

	if (!test_and_clear_bit(WLVIF_FLAG_INITIALIZED, &wlvif->flags))
		return;

	/* because of hardware recovery, we may get here twice */
	if (wl->state == WLCORE_STATE_OFF)
		return;

	wl1271_info("down");

	if (wl->scan.state != WL1271_SCAN_STATE_IDLE &&
	    wl->scan_wlvif == wlvif) {
		/*
		 * Rearm the tx watchdog just before idling scan. This
		 * prevents just-finished scans from triggering the watchdog
		 */
		wl12xx_rearm_tx_watchdog_locked(wl);

		wl->scan.state = WL1271_SCAN_STATE_IDLE;
		memset(wl->scan.scanned_ch, 0, sizeof(wl->scan.scanned_ch));
		wl->scan_wlvif = NULL;
		wl->scan.req = NULL;
		ieee80211_scan_completed(wl->hw, true);
	}

	if (wl->sched_vif == wlvif) {
		ieee80211_sched_scan_stopped(wl->hw);
		wl->sched_vif = NULL;
	}

	if (wl->roc_vif == vif) {
		wl->roc_vif = NULL;
		ieee80211_remain_on_channel_expired(wl->hw);
	}

	if (!test_bit(WL1271_FLAG_RECOVERY_IN_PROGRESS, &wl->flags)) {
		/* disable active roles */
		ret = wl1271_ps_elp_wakeup(wl);
		if (ret < 0)
			goto deinit;

		if (wlvif->bss_type == BSS_TYPE_STA_BSS ||
		    wlvif->bss_type == BSS_TYPE_IBSS) {
			if (wl12xx_dev_role_started(wlvif))
				wl12xx_stop_dev(wl, wlvif);
		}

		ret = wl12xx_cmd_role_disable(wl, &wlvif->role_id);
		if (ret < 0)
			goto deinit;

		wl1271_ps_elp_sleep(wl);
	}
deinit:
	wl12xx_tx_reset_wlvif(wl, wlvif);

	/* clear all hlids (except system_hlid) */
	wlvif->dev_hlid = WL12XX_INVALID_LINK_ID;

	if (wlvif->bss_type == BSS_TYPE_STA_BSS ||
	    wlvif->bss_type == BSS_TYPE_IBSS) {
		wlvif->sta.hlid = WL12XX_INVALID_LINK_ID;
		wl12xx_free_rate_policy(wl, &wlvif->sta.basic_rate_idx);
		wl12xx_free_rate_policy(wl, &wlvif->sta.ap_rate_idx);
		wl12xx_free_rate_policy(wl, &wlvif->sta.p2p_rate_idx);
		wlcore_free_klv_template(wl, &wlvif->sta.klv_template_id);
	} else {
		wlvif->ap.bcast_hlid = WL12XX_INVALID_LINK_ID;
		wlvif->ap.global_hlid = WL12XX_INVALID_LINK_ID;
		wl12xx_free_rate_policy(wl, &wlvif->ap.mgmt_rate_idx);
		wl12xx_free_rate_policy(wl, &wlvif->ap.bcast_rate_idx);
		for (i = 0; i < CONF_TX_MAX_AC_COUNT; i++)
			wl12xx_free_rate_policy(wl,
						&wlvif->ap.ucast_rate_idx[i]);
		wl1271_free_ap_keys(wl, wlvif);
	}

	dev_kfree_skb(wlvif->probereq);
	wlvif->probereq = NULL;
	if (wl->last_wlvif == wlvif)
		wl->last_wlvif = NULL;
	list_del(&wlvif->list);
	memset(wlvif->ap.sta_hlid_map, 0, sizeof(wlvif->ap.sta_hlid_map));
	wlvif->role_id = WL12XX_INVALID_ROLE_ID;
	wlvif->dev_role_id = WL12XX_INVALID_ROLE_ID;

	if (is_ap)
		wl->ap_count--;
	else
		wl->sta_count--;

	/*
	 * Last AP, have more stations. Configure sleep auth according to STA.
	 * Don't do thin on unintended recovery.
	 */
	if (test_bit(WL1271_FLAG_RECOVERY_IN_PROGRESS, &wl->flags) &&
	    !test_bit(WL1271_FLAG_INTENDED_FW_RECOVERY, &wl->flags))
		goto unlock;

	if (wl->ap_count == 0 && is_ap && wl->sta_count) {
		u8 sta_auth = wl->conf.conn.sta_sleep_auth;
		/* Configure for power according to debugfs */
		if (sta_auth != WL1271_PSM_ILLEGAL)
			wl1271_acx_sleep_auth(wl, sta_auth);
		/* Configure for ELP power saving */
		else
			wl1271_acx_sleep_auth(wl, WL1271_PSM_ELP);
	}

unlock:
	mutex_unlock(&wl->mutex);

	del_timer_sync(&wlvif->rx_streaming_timer);
	cancel_work_sync(&wlvif->rx_streaming_enable_work);
	cancel_work_sync(&wlvif->rx_streaming_disable_work);
	cancel_delayed_work_sync(&wlvif->connection_loss_work);

	mutex_lock(&wl->mutex);
}