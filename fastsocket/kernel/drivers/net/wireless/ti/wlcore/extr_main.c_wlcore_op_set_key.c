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
struct wl1271 {scalar_t__ state; int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_key_conf {scalar_t__ cipher; } ;
struct ieee80211_hw {struct wl1271* priv; } ;
typedef  enum set_key_cmd { ____Placeholder_set_key_cmd } set_key_cmd ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ WL1271_CIPHER_SUITE_GEM ; 
 scalar_t__ WLAN_CIPHER_SUITE_TKIP ; 
 int /*<<< orphan*/  WLCORE_QUEUE_STOP_REASON_SPARE_BLK ; 
 scalar_t__ WLCORE_STATE_ON ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wl1271_ps_elp_sleep (struct wl1271*) ; 
 int wl1271_ps_elp_wakeup (struct wl1271*) ; 
 int /*<<< orphan*/  wl1271_tx_flush (struct wl1271*) ; 
 int wlcore_hw_set_key (struct wl1271*,int,struct ieee80211_vif*,struct ieee80211_sta*,struct ieee80211_key_conf*) ; 
 int /*<<< orphan*/  wlcore_stop_queues (struct wl1271*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlcore_wake_queues (struct wl1271*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wlcore_op_set_key(struct ieee80211_hw *hw, enum set_key_cmd cmd,
			     struct ieee80211_vif *vif,
			     struct ieee80211_sta *sta,
			     struct ieee80211_key_conf *key_conf)
{
	struct wl1271 *wl = hw->priv;
	int ret;
	bool might_change_spare =
		key_conf->cipher == WL1271_CIPHER_SUITE_GEM ||
		key_conf->cipher == WLAN_CIPHER_SUITE_TKIP;

	if (might_change_spare) {
		/*
		 * stop the queues and flush to ensure the next packets are
		 * in sync with FW spare block accounting
		 */
		wlcore_stop_queues(wl, WLCORE_QUEUE_STOP_REASON_SPARE_BLK);
		wl1271_tx_flush(wl);
	}

	mutex_lock(&wl->mutex);

	if (unlikely(wl->state != WLCORE_STATE_ON)) {
		ret = -EAGAIN;
		goto out_wake_queues;
	}

	ret = wl1271_ps_elp_wakeup(wl);
	if (ret < 0)
		goto out_wake_queues;

	ret = wlcore_hw_set_key(wl, cmd, vif, sta, key_conf);

	wl1271_ps_elp_sleep(wl);

out_wake_queues:
	if (might_change_spare)
		wlcore_wake_queues(wl, WLCORE_QUEUE_STOP_REASON_SPARE_BLK);

	mutex_unlock(&wl->mutex);

	return ret;
}