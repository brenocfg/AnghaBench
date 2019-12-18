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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  tx_power_cmd ;
struct iwlagn_tx_power_dbm_cmd {scalar_t__ global_lmt; int /*<<< orphan*/  srv_chan_lmt; int /*<<< orphan*/  flags; } ;
struct iwl_priv {int tx_power_user_lmt; TYPE_2__* fw; TYPE_1__* nvm_data; int /*<<< orphan*/  status; } ;
typedef  scalar_t__ s8 ;
struct TYPE_4__ {int /*<<< orphan*/  ucode_ver; } ;
struct TYPE_3__ {scalar_t__ max_tx_pwr_half_dbm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SYNC ; 
 int EAGAIN ; 
 int /*<<< orphan*/  IWLAGN_TX_POWER_AUTO ; 
 int /*<<< orphan*/  IWLAGN_TX_POWER_NO_CLOSED ; 
 int IWL_UCODE_API (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REPLY_TX_POWER_DBM_CMD ; 
 int /*<<< orphan*/  REPLY_TX_POWER_DBM_CMD_V1 ; 
 int /*<<< orphan*/  STATUS_SCAN_HW ; 
 scalar_t__ WARN_ONCE (int /*<<< orphan*/ ,char*) ; 
 int iwl_dvm_send_cmd_pdu (struct iwl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwlagn_tx_power_dbm_cmd*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int iwlagn_send_tx_power(struct iwl_priv *priv)
{
	struct iwlagn_tx_power_dbm_cmd tx_power_cmd;
	u8 tx_ant_cfg_cmd;

	if (WARN_ONCE(test_bit(STATUS_SCAN_HW, &priv->status),
		      "TX Power requested while scanning!\n"))
		return -EAGAIN;

	/* half dBm need to multiply */
	tx_power_cmd.global_lmt = (s8)(2 * priv->tx_power_user_lmt);

	if (tx_power_cmd.global_lmt > priv->nvm_data->max_tx_pwr_half_dbm) {
		/*
		 * For the newer devices which using enhanced/extend tx power
		 * table in EEPROM, the format is in half dBm. driver need to
		 * convert to dBm format before report to mac80211.
		 * By doing so, there is a possibility of 1/2 dBm resolution
		 * lost. driver will perform "round-up" operation before
		 * reporting, but it will cause 1/2 dBm tx power over the
		 * regulatory limit. Perform the checking here, if the
		 * "tx_power_user_lmt" is higher than EEPROM value (in
		 * half-dBm format), lower the tx power based on EEPROM
		 */
		tx_power_cmd.global_lmt =
			priv->nvm_data->max_tx_pwr_half_dbm;
	}
	tx_power_cmd.flags = IWLAGN_TX_POWER_NO_CLOSED;
	tx_power_cmd.srv_chan_lmt = IWLAGN_TX_POWER_AUTO;

	if (IWL_UCODE_API(priv->fw->ucode_ver) == 1)
		tx_ant_cfg_cmd = REPLY_TX_POWER_DBM_CMD_V1;
	else
		tx_ant_cfg_cmd = REPLY_TX_POWER_DBM_CMD;

	return iwl_dvm_send_cmd_pdu(priv, tx_ant_cfg_cmd, CMD_SYNC,
			sizeof(tx_power_cmd), &tx_power_cmd);
}