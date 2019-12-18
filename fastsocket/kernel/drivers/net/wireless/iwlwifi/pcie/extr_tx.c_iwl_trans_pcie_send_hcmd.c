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
struct iwl_trans_pcie {int /*<<< orphan*/  status; } ;
struct iwl_trans {int dummy; } ;
struct iwl_host_cmd {int flags; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int CMD_ASYNC ; 
 int EIO ; 
 int ERFKILL ; 
 int /*<<< orphan*/  IWL_DEBUG_RF_KILL (struct iwl_trans*,char*,int /*<<< orphan*/ ) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  STATUS_FW_ERROR ; 
 int /*<<< orphan*/  STATUS_RFKILL ; 
 int iwl_pcie_send_hcmd_async (struct iwl_trans*,struct iwl_host_cmd*) ; 
 int iwl_pcie_send_hcmd_sync (struct iwl_trans*,struct iwl_host_cmd*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int iwl_trans_pcie_send_hcmd(struct iwl_trans *trans, struct iwl_host_cmd *cmd)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	if (test_bit(STATUS_FW_ERROR, &trans_pcie->status))
		return -EIO;

	if (test_bit(STATUS_RFKILL, &trans_pcie->status)) {
		IWL_DEBUG_RF_KILL(trans, "Dropping CMD 0x%x: RF KILL\n",
				  cmd->id);
		return -ERFKILL;
	}

	if (cmd->flags & CMD_ASYNC)
		return iwl_pcie_send_hcmd_async(trans, cmd);

	/* We still can fail on RFKILL that can be asserted while we wait */
	return iwl_pcie_send_hcmd_sync(trans, cmd);
}