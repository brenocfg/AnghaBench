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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  tx_ant_cmd ;
struct iwl_tx_ant_cfg_cmd {int /*<<< orphan*/  valid; } ;
struct iwl_mvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SYNC ; 
 int /*<<< orphan*/  IWL_DEBUG_FW (struct iwl_mvm*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TX_ANT_CONFIGURATION_CMD ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_tx_ant_cfg_cmd*) ; 

__attribute__((used)) static int iwl_send_tx_ant_cfg(struct iwl_mvm *mvm, u8 valid_tx_ant)
{
	struct iwl_tx_ant_cfg_cmd tx_ant_cmd = {
		.valid = cpu_to_le32(valid_tx_ant),
	};

	IWL_DEBUG_FW(mvm, "select valid tx ant: %u\n", valid_tx_ant);
	return iwl_mvm_send_cmd_pdu(mvm, TX_ANT_CONFIGURATION_CMD, CMD_SYNC,
				    sizeof(tx_ant_cmd), &tx_ant_cmd);
}