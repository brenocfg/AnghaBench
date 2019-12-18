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
struct iwl_trans {int /*<<< orphan*/  op_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*,int) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  STATUS_RFKILL ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_enable_rfkill_int (struct iwl_trans*) ; 
 int iwl_is_rfkill_set (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_op_mode_hw_rf_kill (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwl_pcie_apm_init (struct iwl_trans*) ; 
 int iwl_pcie_prepare_card_hw (struct iwl_trans*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_trans_pcie_start_hw(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	bool hw_rfkill;
	int err;

	err = iwl_pcie_prepare_card_hw(trans);
	if (err) {
		IWL_ERR(trans, "Error while preparing HW: %d\n", err);
		return err;
	}

	iwl_pcie_apm_init(trans);

	/* From now on, the op_mode will be kept updated about RF kill state */
	iwl_enable_rfkill_int(trans);

	hw_rfkill = iwl_is_rfkill_set(trans);
	if (hw_rfkill)
		set_bit(STATUS_RFKILL, &trans_pcie->status);
	else
		clear_bit(STATUS_RFKILL, &trans_pcie->status);
	iwl_op_mode_hw_rf_kill(trans->op_mode, hw_rfkill);

	return 0;
}