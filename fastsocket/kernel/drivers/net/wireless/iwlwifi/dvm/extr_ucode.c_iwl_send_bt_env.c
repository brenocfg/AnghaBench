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
typedef  void* u8 ;
struct iwl_priv {int dummy; } ;
struct iwl_bt_coex_prot_env_cmd {void* type; void* action; } ;
typedef  int /*<<< orphan*/  env_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SYNC ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*) ; 
 int /*<<< orphan*/  REPLY_BT_COEX_PROT_ENV ; 
 int iwl_dvm_send_cmd_pdu (struct iwl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_bt_coex_prot_env_cmd*) ; 

int iwl_send_bt_env(struct iwl_priv *priv, u8 action, u8 type)
{
	struct iwl_bt_coex_prot_env_cmd env_cmd;
	int ret;

	env_cmd.action = action;
	env_cmd.type = type;
	ret = iwl_dvm_send_cmd_pdu(priv,
			       REPLY_BT_COEX_PROT_ENV, CMD_SYNC,
			       sizeof(env_cmd), &env_cmd);
	if (ret)
		IWL_ERR(priv, "failed to send BT env command\n");
	return ret;
}