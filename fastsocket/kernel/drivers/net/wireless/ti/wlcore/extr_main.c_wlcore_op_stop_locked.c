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
struct wl1271 {scalar_t__ state; int /*<<< orphan*/  reg_ch_conf_last; int /*<<< orphan*/ * target_mem_map; int /*<<< orphan*/ * tx_res_if; int /*<<< orphan*/ * fw_status_2; int /*<<< orphan*/ * fw_status_1; scalar_t__* tx_allocated_pkts; scalar_t__* tx_pkts_freed; scalar_t__ tx_blocks_freed; scalar_t__ flags; int /*<<< orphan*/  links_map; TYPE_1__* links; scalar_t__ active_link_count; scalar_t__ active_sta_count; int /*<<< orphan*/  session_ids; int /*<<< orphan*/  roc_map; int /*<<< orphan*/  roles_map; int /*<<< orphan*/  sleep_auth; scalar_t__ ap_ps_map; scalar_t__ ap_fw_ps_map; scalar_t__ time_offset; scalar_t__ tx_packets_count; scalar_t__ tx_results_count; scalar_t__ tx_allocated_blocks; scalar_t__ tx_blocks_available; int /*<<< orphan*/  channel_type; int /*<<< orphan*/  power_level; scalar_t__ rx_counter; int /*<<< orphan*/  band; int /*<<< orphan*/  mutex; int /*<<< orphan*/  tx_watchdog_work; int /*<<< orphan*/  elp_work; int /*<<< orphan*/  tx_work; int /*<<< orphan*/  netstack_work; int /*<<< orphan*/  scan_complete_work; int /*<<< orphan*/  recovery_work; } ;
struct TYPE_2__ {scalar_t__ prev_freed_pkts; scalar_t__ allocated_pkts; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_BAND_2GHZ ; 
 int /*<<< orphan*/  NL80211_CHAN_NO_HT ; 
 int NUM_TX_QUEUES ; 
 int /*<<< orphan*/  WL1271_DEFAULT_POWER_LEVEL ; 
 int /*<<< orphan*/  WL1271_FLAG_RECOVERY_IN_PROGRESS ; 
 int /*<<< orphan*/  WL1271_PSM_ILLEGAL ; 
 size_t WL12XX_SYSTEM_HLID ; 
 scalar_t__ WLCORE_STATE_OFF ; 
 int /*<<< orphan*/  __set_bit (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  wl1271_debugfs_reset (struct wl1271*) ; 
 int /*<<< orphan*/  wl1271_flush_deferred_work (struct wl1271*) ; 
 int /*<<< orphan*/  wl1271_power_off (struct wl1271*) ; 
 int /*<<< orphan*/  wl12xx_tx_reset (struct wl1271*) ; 
 int /*<<< orphan*/  wlcore_disable_interrupts_nosync (struct wl1271*) ; 
 int /*<<< orphan*/  wlcore_enable_interrupts (struct wl1271*) ; 
 int /*<<< orphan*/  wlcore_synchronize_interrupts (struct wl1271*) ; 

__attribute__((used)) static void wlcore_op_stop_locked(struct wl1271 *wl)
{
	int i;

	if (wl->state == WLCORE_STATE_OFF) {
		if (test_and_clear_bit(WL1271_FLAG_RECOVERY_IN_PROGRESS,
					&wl->flags))
			wlcore_enable_interrupts(wl);

		return;
	}

	/*
	 * this must be before the cancel_work calls below, so that the work
	 * functions don't perform further work.
	 */
	wl->state = WLCORE_STATE_OFF;

	/*
	 * Use the nosync variant to disable interrupts, so the mutex could be
	 * held while doing so without deadlocking.
	 */
	wlcore_disable_interrupts_nosync(wl);

	mutex_unlock(&wl->mutex);

	wlcore_synchronize_interrupts(wl);
	if (!test_bit(WL1271_FLAG_RECOVERY_IN_PROGRESS, &wl->flags))
		cancel_work_sync(&wl->recovery_work);
	wl1271_flush_deferred_work(wl);
	cancel_delayed_work_sync(&wl->scan_complete_work);
	cancel_work_sync(&wl->netstack_work);
	cancel_work_sync(&wl->tx_work);
	cancel_delayed_work_sync(&wl->elp_work);
	cancel_delayed_work_sync(&wl->tx_watchdog_work);

	/* let's notify MAC80211 about the remaining pending TX frames */
	mutex_lock(&wl->mutex);
	wl12xx_tx_reset(wl);

	wl1271_power_off(wl);
	/*
	 * In case a recovery was scheduled, interrupts were disabled to avoid
	 * an interrupt storm. Now that the power is down, it is safe to
	 * re-enable interrupts to balance the disable depth
	 */
	if (test_and_clear_bit(WL1271_FLAG_RECOVERY_IN_PROGRESS, &wl->flags))
		wlcore_enable_interrupts(wl);

	wl->band = IEEE80211_BAND_2GHZ;

	wl->rx_counter = 0;
	wl->power_level = WL1271_DEFAULT_POWER_LEVEL;
	wl->channel_type = NL80211_CHAN_NO_HT;
	wl->tx_blocks_available = 0;
	wl->tx_allocated_blocks = 0;
	wl->tx_results_count = 0;
	wl->tx_packets_count = 0;
	wl->time_offset = 0;
	wl->ap_fw_ps_map = 0;
	wl->ap_ps_map = 0;
	wl->sleep_auth = WL1271_PSM_ILLEGAL;
	memset(wl->roles_map, 0, sizeof(wl->roles_map));
	memset(wl->links_map, 0, sizeof(wl->links_map));
	memset(wl->roc_map, 0, sizeof(wl->roc_map));
	memset(wl->session_ids, 0, sizeof(wl->session_ids));
	wl->active_sta_count = 0;
	wl->active_link_count = 0;

	/* The system link is always allocated */
	wl->links[WL12XX_SYSTEM_HLID].allocated_pkts = 0;
	wl->links[WL12XX_SYSTEM_HLID].prev_freed_pkts = 0;
	__set_bit(WL12XX_SYSTEM_HLID, wl->links_map);

	/*
	 * this is performed after the cancel_work calls and the associated
	 * mutex_lock, so that wl1271_op_add_interface does not accidentally
	 * get executed before all these vars have been reset.
	 */
	wl->flags = 0;

	wl->tx_blocks_freed = 0;

	for (i = 0; i < NUM_TX_QUEUES; i++) {
		wl->tx_pkts_freed[i] = 0;
		wl->tx_allocated_pkts[i] = 0;
	}

	wl1271_debugfs_reset(wl);

	kfree(wl->fw_status_1);
	wl->fw_status_1 = NULL;
	wl->fw_status_2 = NULL;
	kfree(wl->tx_res_if);
	wl->tx_res_if = NULL;
	kfree(wl->target_mem_map);
	wl->target_mem_map = NULL;

	/*
	 * FW channels must be re-calibrated after recovery,
	 * clear the last Reg-Domain channel configuration.
	 */
	memset(wl->reg_ch_conf_last, 0, sizeof(wl->reg_ch_conf_last));
}