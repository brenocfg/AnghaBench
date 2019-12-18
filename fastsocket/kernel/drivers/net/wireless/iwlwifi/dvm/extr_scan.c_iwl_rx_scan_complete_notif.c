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
struct iwl_scancomplete_notification {scalar_t__ bt_status; int /*<<< orphan*/  status; int /*<<< orphan*/  tsf_high; int /*<<< orphan*/  tsf_low; int /*<<< orphan*/  scanned_channels; } ;
struct iwl_rx_packet {scalar_t__ data; } ;
struct iwl_rx_cmd_buffer {int dummy; } ;
struct iwl_priv {scalar_t__ scan_band; scalar_t__ iw_mode; scalar_t__ bt_status; int /*<<< orphan*/  bt_traffic_change_work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  bt_traffic_load; int /*<<< orphan*/  bt_ch_announce; int /*<<< orphan*/  scan_completed; int /*<<< orphan*/  status; scalar_t__ scan_start; } ;
struct iwl_device_cmd {int dummy; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_BAND_2GHZ ; 
 int /*<<< orphan*/  IWL_BT_COEX_TRAFFIC_LOAD_HIGH ; 
 int /*<<< orphan*/  IWL_BT_COEX_TRAFFIC_LOAD_NONE ; 
 int /*<<< orphan*/  IWL_DEBUG_SCAN (struct iwl_priv*,char*,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  STATUS_SCAN_COMPLETE ; 
 int /*<<< orphan*/  STATUS_SCAN_HW ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ iwl_advanced_bt_coexist (struct iwl_priv*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (scalar_t__) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_rx_scan_complete_notif(struct iwl_priv *priv,
				       struct iwl_rx_cmd_buffer *rxb,
				       struct iwl_device_cmd *cmd)
{
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	struct iwl_scancomplete_notification *scan_notif = (void *)pkt->data;

	IWL_DEBUG_SCAN(priv, "Scan complete: %d channels (TSF 0x%08X:%08X) - %d\n",
		       scan_notif->scanned_channels,
		       scan_notif->tsf_low,
		       scan_notif->tsf_high, scan_notif->status);

	IWL_DEBUG_SCAN(priv, "Scan on %sGHz took %dms\n",
		       (priv->scan_band == IEEE80211_BAND_2GHZ) ? "2.4" : "5.2",
		       jiffies_to_msecs(jiffies - priv->scan_start));

	/*
	 * When aborting, we run the scan completed background work inline
	 * and the background work must then do nothing. The SCAN_COMPLETE
	 * bit helps implement that logic and thus needs to be set before
	 * queueing the work. Also, since the scan abort waits for SCAN_HW
	 * to clear, we need to set SCAN_COMPLETE before clearing SCAN_HW
	 * to avoid a race there.
	 */
	set_bit(STATUS_SCAN_COMPLETE, &priv->status);
	clear_bit(STATUS_SCAN_HW, &priv->status);
	queue_work(priv->workqueue, &priv->scan_completed);

	if (priv->iw_mode != NL80211_IFTYPE_ADHOC &&
	    iwl_advanced_bt_coexist(priv) &&
	    priv->bt_status != scan_notif->bt_status) {
		if (scan_notif->bt_status) {
			/* BT on */
			if (!priv->bt_ch_announce)
				priv->bt_traffic_load =
					IWL_BT_COEX_TRAFFIC_LOAD_HIGH;
			/*
			 * otherwise, no traffic load information provided
			 * no changes made
			 */
		} else {
			/* BT off */
			priv->bt_traffic_load =
				IWL_BT_COEX_TRAFFIC_LOAD_NONE;
		}
		priv->bt_status = scan_notif->bt_status;
		queue_work(priv->workqueue,
			   &priv->bt_traffic_change_work);
	}
	return 0;
}