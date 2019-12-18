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
struct iwl_phy_context_cmd {int dummy; } ;
struct iwl_mvm_phy_ctxt {int /*<<< orphan*/  id; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SYNC ; 
 int /*<<< orphan*/  FW_CTXT_ACTION_REMOVE ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_CONTEXT_CMD ; 
 int /*<<< orphan*/  iwl_mvm_phy_ctxt_cmd_hdr (struct iwl_mvm_phy_ctxt*,struct iwl_phy_context_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_phy_context_cmd*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void iwl_mvm_phy_ctxt_remove(struct iwl_mvm *mvm, struct iwl_mvm_phy_ctxt *ctxt)
{
	struct iwl_phy_context_cmd cmd;
	int ret;

	lockdep_assert_held(&mvm->mutex);

	iwl_mvm_phy_ctxt_cmd_hdr(ctxt, &cmd, FW_CTXT_ACTION_REMOVE, 0);
	ret = iwl_mvm_send_cmd_pdu(mvm, PHY_CONTEXT_CMD, CMD_SYNC,
				   sizeof(struct iwl_phy_context_cmd),
				   &cmd);
	if (ret)
		IWL_ERR(mvm, "Failed to send PHY remove: ctxt id=%d\n",
			ctxt->id);
}