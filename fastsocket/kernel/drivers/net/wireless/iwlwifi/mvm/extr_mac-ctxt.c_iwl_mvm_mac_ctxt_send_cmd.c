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
struct iwl_mvm {int dummy; } ;
struct iwl_mac_ctx_cmd {int /*<<< orphan*/  action; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SYNC ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MAC_CONTEXT_CMD ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_mac_ctx_cmd*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_mvm_mac_ctxt_send_cmd(struct iwl_mvm *mvm,
				     struct iwl_mac_ctx_cmd *cmd)
{
	int ret = iwl_mvm_send_cmd_pdu(mvm, MAC_CONTEXT_CMD, CMD_SYNC,
				       sizeof(*cmd), cmd);
	if (ret)
		IWL_ERR(mvm, "Failed to send MAC context (action:%d): %d\n",
			le32_to_cpu(cmd->action), ret);
	return ret;
}