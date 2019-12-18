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
struct wl12xx_vif {int dummy; } ;
struct TYPE_4__ {scalar_t__ state; int /*<<< orphan*/ * req; int /*<<< orphan*/  scanned_ch; } ;
struct wl1271 {scalar_t__ state; int /*<<< orphan*/  scan_complete_work; int /*<<< orphan*/  mutex; int /*<<< orphan*/  hw; TYPE_2__ scan; int /*<<< orphan*/ * scan_wlvif; TYPE_1__* ops; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct wl1271* priv; } ;
struct TYPE_3__ {int (* scan_stop ) (struct wl1271*,struct wl12xx_vif*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_MAC80211 ; 
 scalar_t__ WL1271_SCAN_STATE_DONE ; 
 scalar_t__ WL1271_SCAN_STATE_IDLE ; 
 scalar_t__ WLCORE_STATE_ON ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_scan_completed (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct wl1271*,struct wl12xx_vif*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_ps_elp_sleep (struct wl1271*) ; 
 int wl1271_ps_elp_wakeup (struct wl1271*) ; 
 int /*<<< orphan*/  wl12xx_rearm_tx_watchdog_locked (struct wl1271*) ; 
 struct wl12xx_vif* wl12xx_vif_to_data (struct ieee80211_vif*) ; 

__attribute__((used)) static void wl1271_op_cancel_hw_scan(struct ieee80211_hw *hw,
				     struct ieee80211_vif *vif)
{
	struct wl1271 *wl = hw->priv;
	struct wl12xx_vif *wlvif = wl12xx_vif_to_data(vif);
	int ret;

	wl1271_debug(DEBUG_MAC80211, "mac80211 cancel hw scan");

	mutex_lock(&wl->mutex);

	if (unlikely(wl->state != WLCORE_STATE_ON))
		goto out;

	if (wl->scan.state == WL1271_SCAN_STATE_IDLE)
		goto out;

	ret = wl1271_ps_elp_wakeup(wl);
	if (ret < 0)
		goto out;

	if (wl->scan.state != WL1271_SCAN_STATE_DONE) {
		ret = wl->ops->scan_stop(wl, wlvif);
		if (ret < 0)
			goto out_sleep;
	}

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

out_sleep:
	wl1271_ps_elp_sleep(wl);
out:
	mutex_unlock(&wl->mutex);

	cancel_delayed_work_sync(&wl->scan_complete_work);
}