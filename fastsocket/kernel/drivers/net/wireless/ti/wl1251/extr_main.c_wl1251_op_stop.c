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
struct wl1251 {scalar_t__ state; int scanning; int listen_int; int elp; int tx_queue_stopped; int /*<<< orphan*/  mutex; int /*<<< orphan*/  channel; scalar_t__ rssi_thold; int /*<<< orphan*/  power_level; int /*<<< orphan*/  station_mode; scalar_t__ next_tx_complete; scalar_t__ rx_last_id; scalar_t__ rx_current_buffer; scalar_t__ rx_handled; scalar_t__ rx_counter; scalar_t__ data_in_count; int /*<<< orphan*/  bss_type; int /*<<< orphan*/  bssid; int /*<<< orphan*/  elp_work; int /*<<< orphan*/  tx_work; int /*<<< orphan*/  irq_work; int /*<<< orphan*/  hw; } ;
struct ieee80211_hw {struct wl1251* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_MAC80211 ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  MAX_BSS_TYPE ; 
 int /*<<< orphan*/  STATION_ACTIVE_MODE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WL1251_DEFAULT_CHANNEL ; 
 int /*<<< orphan*/  WL1251_DEFAULT_POWER_LEVEL ; 
 scalar_t__ WL1251_STATE_OFF ; 
 scalar_t__ WL1251_STATE_ON ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_scan_completed (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1251_debugfs_reset (struct wl1251*) ; 
 int /*<<< orphan*/  wl1251_disable_interrupts (struct wl1251*) ; 
 int /*<<< orphan*/  wl1251_info (char*) ; 
 int /*<<< orphan*/  wl1251_power_off (struct wl1251*) ; 
 int /*<<< orphan*/  wl1251_tx_flush (struct wl1251*) ; 

__attribute__((used)) static void wl1251_op_stop(struct ieee80211_hw *hw)
{
	struct wl1251 *wl = hw->priv;

	wl1251_info("down");

	wl1251_debug(DEBUG_MAC80211, "mac80211 stop");

	mutex_lock(&wl->mutex);

	WARN_ON(wl->state != WL1251_STATE_ON);

	if (wl->scanning) {
		ieee80211_scan_completed(wl->hw, true);
		wl->scanning = false;
	}

	wl->state = WL1251_STATE_OFF;

	wl1251_disable_interrupts(wl);

	mutex_unlock(&wl->mutex);

	cancel_work_sync(&wl->irq_work);
	cancel_work_sync(&wl->tx_work);
	cancel_delayed_work_sync(&wl->elp_work);

	mutex_lock(&wl->mutex);

	/* let's notify MAC80211 about the remaining pending TX frames */
	wl1251_tx_flush(wl);
	wl1251_power_off(wl);

	memset(wl->bssid, 0, ETH_ALEN);
	wl->listen_int = 1;
	wl->bss_type = MAX_BSS_TYPE;

	wl->data_in_count = 0;
	wl->rx_counter = 0;
	wl->rx_handled = 0;
	wl->rx_current_buffer = 0;
	wl->rx_last_id = 0;
	wl->next_tx_complete = 0;
	wl->elp = false;
	wl->station_mode = STATION_ACTIVE_MODE;
	wl->tx_queue_stopped = false;
	wl->power_level = WL1251_DEFAULT_POWER_LEVEL;
	wl->rssi_thold = 0;
	wl->channel = WL1251_DEFAULT_CHANNEL;

	wl1251_debugfs_reset(wl);

	mutex_unlock(&wl->mutex);
}