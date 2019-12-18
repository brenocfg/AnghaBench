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
struct iwl_rx_packet {scalar_t__ data; } ;
struct iwl_rx_cmd_buffer {int dummy; } ;
struct iwl_radio_version_notif {int /*<<< orphan*/  radio_dash; int /*<<< orphan*/  radio_step; int /*<<< orphan*/  radio_flavor; } ;
struct iwl_mvm {int dummy; } ;
struct iwl_device_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_mvm*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 

int iwl_mvm_rx_radio_ver(struct iwl_mvm *mvm, struct iwl_rx_cmd_buffer *rxb,
			 struct iwl_device_cmd *cmd)
{
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	struct iwl_radio_version_notif *radio_version = (void *)pkt->data;

	/* TODO: what to do with that? */
	IWL_DEBUG_INFO(mvm,
		       "Radio version: flavor: 0x%08x, step 0x%08x, dash 0x%08x\n",
		       le32_to_cpu(radio_version->radio_flavor),
		       le32_to_cpu(radio_version->radio_step),
		       le32_to_cpu(radio_version->radio_dash));
	return 0;
}