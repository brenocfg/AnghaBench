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
struct iwl_trans_pcie {int /*<<< orphan*/  wait_command_queue; int /*<<< orphan*/  status; } ;
struct iwl_trans {int /*<<< orphan*/  op_mode; TYPE_1__* cfg; } ;
struct TYPE_2__ {scalar_t__ internal_wimax_coex; } ;

/* Variables and functions */
 int /*<<< orphan*/  APMG_CLK_CTRL_REG ; 
 int /*<<< orphan*/  APMG_PS_CTRL_REG ; 
 int APMG_PS_CTRL_VAL_RESET_REQ ; 
 int APMS_CLK_VAL_MRB_FUNC_MODE ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  STATUS_FW_ERROR ; 
 int /*<<< orphan*/  STATUS_HCMD_ACTIVE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_op_mode_nic_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_op_mode_wimax_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_pcie_dump_csr (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_dump_fh (struct iwl_trans*,int /*<<< orphan*/ *) ; 
 int iwl_read_prph (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_pcie_irq_handle_error(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	/* W/A for WiFi/WiMAX coex and WiMAX own the RF */
	if (trans->cfg->internal_wimax_coex &&
	    (!(iwl_read_prph(trans, APMG_CLK_CTRL_REG) &
			     APMS_CLK_VAL_MRB_FUNC_MODE) ||
	     (iwl_read_prph(trans, APMG_PS_CTRL_REG) &
			    APMG_PS_CTRL_VAL_RESET_REQ))) {
		clear_bit(STATUS_HCMD_ACTIVE, &trans_pcie->status);
		iwl_op_mode_wimax_active(trans->op_mode);
		wake_up(&trans_pcie->wait_command_queue);
		return;
	}

	iwl_pcie_dump_csr(trans);
	iwl_pcie_dump_fh(trans, NULL);

	set_bit(STATUS_FW_ERROR, &trans_pcie->status);
	clear_bit(STATUS_HCMD_ACTIVE, &trans_pcie->status);
	wake_up(&trans_pcie->wait_command_queue);

	local_bh_disable();
	iwl_op_mode_nic_error(trans->op_mode);
	local_bh_enable();
}