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
struct iwl_scan_complete_notif {scalar_t__ status; int /*<<< orphan*/  scanned_channels; } ;
struct iwl_rx_packet {scalar_t__ data; } ;
struct iwl_rx_cmd_buffer {int dummy; } ;
struct iwl_mvm {int /*<<< orphan*/  hw; int /*<<< orphan*/  scan_status; } ;
struct iwl_device_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_SCAN (struct iwl_mvm*,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_MVM_SCAN_NONE ; 
 scalar_t__ SCAN_COMP_STATUS_OK ; 
 int /*<<< orphan*/  ieee80211_scan_completed (int /*<<< orphan*/ ,int) ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 

int iwl_mvm_rx_scan_complete(struct iwl_mvm *mvm, struct iwl_rx_cmd_buffer *rxb,
			  struct iwl_device_cmd *cmd)
{
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	struct iwl_scan_complete_notif *notif = (void *)pkt->data;

	IWL_DEBUG_SCAN(mvm, "Scan complete: status=0x%x scanned channels=%d\n",
		       notif->status, notif->scanned_channels);

	mvm->scan_status = IWL_MVM_SCAN_NONE;
	ieee80211_scan_completed(mvm->hw, notif->status != SCAN_COMP_STATUS_OK);

	return 0;
}