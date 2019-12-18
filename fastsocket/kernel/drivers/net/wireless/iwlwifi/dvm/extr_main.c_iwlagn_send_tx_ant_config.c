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
typedef  int /*<<< orphan*/  u8 ;
struct iwl_tx_ant_config_cmd {int /*<<< orphan*/  valid; } ;
struct iwl_priv {TYPE_1__* fw; } ;
struct TYPE_2__ {int /*<<< orphan*/  ucode_ver; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SYNC ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IWL_DEBUG_HC (struct iwl_priv*,char*,...) ; 
 int IWL_UCODE_API (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TX_ANT_CONFIGURATION_CMD ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int iwl_dvm_send_cmd_pdu (struct iwl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_tx_ant_config_cmd*) ; 

__attribute__((used)) static int iwlagn_send_tx_ant_config(struct iwl_priv *priv, u8 valid_tx_ant)
{
	struct iwl_tx_ant_config_cmd tx_ant_cmd = {
	  .valid = cpu_to_le32(valid_tx_ant),
	};

	if (IWL_UCODE_API(priv->fw->ucode_ver) > 1) {
		IWL_DEBUG_HC(priv, "select valid tx ant: %u\n", valid_tx_ant);
		return iwl_dvm_send_cmd_pdu(priv,
					TX_ANT_CONFIGURATION_CMD,
					CMD_SYNC,
					sizeof(struct iwl_tx_ant_config_cmd),
					&tx_ant_cmd);
	} else {
		IWL_DEBUG_HC(priv, "TX_ANT_CONFIGURATION_CMD not supported\n");
		return -EOPNOTSUPP;
	}
}