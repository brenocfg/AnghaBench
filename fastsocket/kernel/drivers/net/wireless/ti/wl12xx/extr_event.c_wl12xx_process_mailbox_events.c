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
typedef  int u32 ;
struct wl12xx_event_mailbox {int scheduled_scan_status; int /*<<< orphan*/  sta_aging_status; int /*<<< orphan*/  sta_tx_retry_exceeded; int /*<<< orphan*/  channel_switch_status; int /*<<< orphan*/  rx_ba_allowed; int /*<<< orphan*/  role_id; int /*<<< orphan*/  rssi_snr_trigger_metric; int /*<<< orphan*/  soft_gemini_sense_info; int /*<<< orphan*/  events_mask; int /*<<< orphan*/  events_vector; } ;
struct wl1271 {scalar_t__ scan_wlvif; struct wl12xx_event_mailbox* mbox; } ;

/* Variables and functions */
 int BA_SESSION_RX_CONSTRAINT_EVENT_ID ; 
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int BSS_LOSE_EVENT_ID ; 
 int CHANNEL_SWITCH_COMPLETE_EVENT_ID ; 
 int /*<<< orphan*/  DEBUG_EVENT ; 
 int DUMMY_PACKET_EVENT_ID ; 
 int INACTIVE_STA_EVENT_ID ; 
 int MAX_TX_RETRY_EVENT_ID ; 
 int PERIODIC_SCAN_COMPLETE_EVENT_ID ; 
 int PERIODIC_SCAN_REPORT_EVENT_ID ; 
 int REMAIN_ON_CHANNEL_COMPLETE_EVENT_ID ; 
 int RSSI_SNR_TRIGGER_0_EVENT_ID ; 
 int SCAN_COMPLETE_EVENT_ID ; 
 int SOFT_GEMINI_SENSE_EVENT_ID ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wl12xx_scan_completed (struct wl1271*,scalar_t__) ; 
 int /*<<< orphan*/  wlcore_event_ba_rx_constraint (struct wl1271*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlcore_event_beacon_loss (struct wl1271*,int) ; 
 int /*<<< orphan*/  wlcore_event_channel_switch (struct wl1271*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlcore_event_dummy_packet (struct wl1271*) ; 
 int /*<<< orphan*/  wlcore_event_inactive_sta (struct wl1271*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlcore_event_max_tx_failure (struct wl1271*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlcore_event_roc_complete (struct wl1271*) ; 
 int /*<<< orphan*/  wlcore_event_rssi_trigger (struct wl1271*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlcore_event_sched_scan_completed (struct wl1271*,int) ; 
 int /*<<< orphan*/  wlcore_event_soft_gemini_sense (struct wl1271*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlcore_scan_sched_scan_results (struct wl1271*) ; 

int wl12xx_process_mailbox_events(struct wl1271 *wl)
{
	struct wl12xx_event_mailbox *mbox = wl->mbox;
	u32 vector;


	vector = le32_to_cpu(mbox->events_vector);
	vector &= ~(le32_to_cpu(mbox->events_mask));

	wl1271_debug(DEBUG_EVENT, "MBOX vector: 0x%x", vector);

	if (vector & SCAN_COMPLETE_EVENT_ID) {
		wl1271_debug(DEBUG_EVENT, "status: 0x%x",
			     mbox->scheduled_scan_status);

		if (wl->scan_wlvif)
			wl12xx_scan_completed(wl, wl->scan_wlvif);
	}

	if (vector & PERIODIC_SCAN_REPORT_EVENT_ID) {
		wl1271_debug(DEBUG_EVENT,
			     "PERIODIC_SCAN_REPORT_EVENT (status 0x%0x)",
			     mbox->scheduled_scan_status);

		wlcore_scan_sched_scan_results(wl);
	}

	if (vector & PERIODIC_SCAN_COMPLETE_EVENT_ID)
		wlcore_event_sched_scan_completed(wl,
						  mbox->scheduled_scan_status);
	if (vector & SOFT_GEMINI_SENSE_EVENT_ID)
		wlcore_event_soft_gemini_sense(wl,
					       mbox->soft_gemini_sense_info);

	if (vector & BSS_LOSE_EVENT_ID)
		wlcore_event_beacon_loss(wl, 0xff);

	if (vector & RSSI_SNR_TRIGGER_0_EVENT_ID)
		wlcore_event_rssi_trigger(wl, mbox->rssi_snr_trigger_metric);

	if (vector & BA_SESSION_RX_CONSTRAINT_EVENT_ID)
		wlcore_event_ba_rx_constraint(wl,
					      BIT(mbox->role_id),
					      mbox->rx_ba_allowed);

	if (vector & CHANNEL_SWITCH_COMPLETE_EVENT_ID)
		wlcore_event_channel_switch(wl, 0xff,
					    mbox->channel_switch_status);

	if (vector & DUMMY_PACKET_EVENT_ID)
		wlcore_event_dummy_packet(wl);

	/*
	 * "TX retries exceeded" has a different meaning according to mode.
	 * In AP mode the offending station is disconnected.
	 */
	if (vector & MAX_TX_RETRY_EVENT_ID)
		wlcore_event_max_tx_failure(wl,
				le16_to_cpu(mbox->sta_tx_retry_exceeded));

	if (vector & INACTIVE_STA_EVENT_ID)
		wlcore_event_inactive_sta(wl,
					  le16_to_cpu(mbox->sta_aging_status));

	if (vector & REMAIN_ON_CHANNEL_COMPLETE_EVENT_ID)
		wlcore_event_roc_complete(wl);

	return 0;
}