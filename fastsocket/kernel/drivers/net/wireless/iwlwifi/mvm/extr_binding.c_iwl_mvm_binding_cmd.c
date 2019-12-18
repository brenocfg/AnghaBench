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
typedef  scalar_t__ u32 ;
struct iwl_mvm_phy_ctxt {int /*<<< orphan*/  color; int /*<<< orphan*/  id; } ;
struct iwl_mvm_iface_iterator_data {int idx; int /*<<< orphan*/ * colors; int /*<<< orphan*/ * ids; struct iwl_mvm_phy_ctxt* phyctxt; } ;
struct iwl_mvm {int dummy; } ;
struct iwl_binding_cmd {void** macs; void* phy; void* action; void* id_and_color; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  BINDING_CONTEXT_CMD ; 
 int EIO ; 
 scalar_t__ FW_CMD_ID_AND_COLOR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FW_CTXT_INVALID ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,scalar_t__,...) ; 
 int MAX_MACS_IN_BINDING ; 
 void* cpu_to_le32 (scalar_t__) ; 
 int iwl_mvm_send_cmd_pdu_status (struct iwl_mvm*,int /*<<< orphan*/ ,int,struct iwl_binding_cmd*,scalar_t__*) ; 
 int /*<<< orphan*/  memset (struct iwl_binding_cmd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int iwl_mvm_binding_cmd(struct iwl_mvm *mvm, u32 action,
			       struct iwl_mvm_iface_iterator_data *data)
{
	struct iwl_binding_cmd cmd;
	struct iwl_mvm_phy_ctxt *phyctxt = data->phyctxt;
	int i, ret;
	u32 status;

	memset(&cmd, 0, sizeof(cmd));

	cmd.id_and_color = cpu_to_le32(FW_CMD_ID_AND_COLOR(phyctxt->id,
							   phyctxt->color));
	cmd.action = cpu_to_le32(action);
	cmd.phy = cpu_to_le32(FW_CMD_ID_AND_COLOR(phyctxt->id,
						  phyctxt->color));

	for (i = 0; i < MAX_MACS_IN_BINDING; i++)
		cmd.macs[i] = cpu_to_le32(FW_CTXT_INVALID);
	for (i = 0; i < data->idx; i++)
		cmd.macs[i] = cpu_to_le32(FW_CMD_ID_AND_COLOR(data->ids[i],
							      data->colors[i]));

	status = 0;
	ret = iwl_mvm_send_cmd_pdu_status(mvm, BINDING_CONTEXT_CMD,
					  sizeof(cmd), &cmd, &status);
	if (ret) {
		IWL_ERR(mvm, "Failed to send binding (action:%d): %d\n",
			action, ret);
		return ret;
	}

	if (status) {
		IWL_ERR(mvm, "Binding command failed: %u\n", status);
		ret = -EIO;
	}

	return ret;
}