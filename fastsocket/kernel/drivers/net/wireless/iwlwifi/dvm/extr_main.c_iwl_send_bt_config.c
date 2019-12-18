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
struct iwl_priv {scalar_t__ bt_enable_flag; } ;
struct iwl_bt_cmd {scalar_t__ flags; int /*<<< orphan*/  kill_cts_mask; int /*<<< orphan*/  kill_ack_mask; int /*<<< orphan*/  max_kill; int /*<<< orphan*/  lead_time; } ;
struct TYPE_2__ {int /*<<< orphan*/  bt_coex_active; } ;

/* Variables and functions */
 scalar_t__ BT_COEX_DISABLE ; 
 scalar_t__ BT_COEX_ENABLE ; 
 int /*<<< orphan*/  BT_LEAD_TIME_DEF ; 
 int /*<<< orphan*/  BT_MAX_KILL_DEF ; 
 int /*<<< orphan*/  CMD_SYNC ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_priv*,char*,char*) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*) ; 
 int /*<<< orphan*/  REPLY_BT_CONFIG ; 
 scalar_t__ iwl_dvm_send_cmd_pdu (struct iwl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_bt_cmd*) ; 
 TYPE_1__ iwlwifi_mod_params ; 

__attribute__((used)) static void iwl_send_bt_config(struct iwl_priv *priv)
{
	struct iwl_bt_cmd bt_cmd = {
		.lead_time = BT_LEAD_TIME_DEF,
		.max_kill = BT_MAX_KILL_DEF,
		.kill_ack_mask = 0,
		.kill_cts_mask = 0,
	};

	if (!iwlwifi_mod_params.bt_coex_active)
		bt_cmd.flags = BT_COEX_DISABLE;
	else
		bt_cmd.flags = BT_COEX_ENABLE;

	priv->bt_enable_flag = bt_cmd.flags;
	IWL_DEBUG_INFO(priv, "BT coex %s\n",
		(bt_cmd.flags == BT_COEX_DISABLE) ? "disable" : "active");

	if (iwl_dvm_send_cmd_pdu(priv, REPLY_BT_CONFIG,
			     CMD_SYNC, sizeof(struct iwl_bt_cmd), &bt_cmd))
		IWL_ERR(priv, "failed to send BT Coex Config\n");
}