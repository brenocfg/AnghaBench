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
struct fw_img {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_INT ; 
 int CSR_UCODE_DRV_GP1_BIT_CMD_BLOCKED ; 
 int /*<<< orphan*/  CSR_UCODE_DRV_GP1_CLR ; 
 int CSR_UCODE_SW_BIT_RFKILL ; 
 int EIO ; 
 int ERFKILL ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  IWL_WARN (struct iwl_trans*,char*) ; 
 int /*<<< orphan*/  STATUS_FW_ERROR ; 
 int /*<<< orphan*/  STATUS_RFKILL ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_enable_interrupts (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_enable_rfkill_int (struct iwl_trans*) ; 
 int iwl_is_rfkill_set (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_op_mode_hw_rf_kill (int /*<<< orphan*/ ,int) ; 
 int iwl_pcie_load_given_ucode (struct iwl_trans*,struct fw_img const*) ; 
 int iwl_pcie_nic_init (struct iwl_trans*) ; 
 scalar_t__ iwl_pcie_prepare_card_hw (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_write32 (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_trans_pcie_start_fw(struct iwl_trans *trans,
				   const struct fw_img *fw, bool run_in_rfkill)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	int ret;
	bool hw_rfkill;

	/* This may fail if AMT took ownership of the device */
	if (iwl_pcie_prepare_card_hw(trans)) {
		IWL_WARN(trans, "Exit HW not ready\n");
		return -EIO;
	}

	clear_bit(STATUS_FW_ERROR, &trans_pcie->status);

	iwl_enable_rfkill_int(trans);

	/* If platform's RF_KILL switch is NOT set to KILL */
	hw_rfkill = iwl_is_rfkill_set(trans);
	if (hw_rfkill)
		set_bit(STATUS_RFKILL, &trans_pcie->status);
	else
		clear_bit(STATUS_RFKILL, &trans_pcie->status);
	iwl_op_mode_hw_rf_kill(trans->op_mode, hw_rfkill);
	if (hw_rfkill && !run_in_rfkill)
		return -ERFKILL;

	iwl_write32(trans, CSR_INT, 0xFFFFFFFF);

	ret = iwl_pcie_nic_init(trans);
	if (ret) {
		IWL_ERR(trans, "Unable to init nic\n");
		return ret;
	}

	/* make sure rfkill handshake bits are cleared */
	iwl_write32(trans, CSR_UCODE_DRV_GP1_CLR, CSR_UCODE_SW_BIT_RFKILL);
	iwl_write32(trans, CSR_UCODE_DRV_GP1_CLR,
		    CSR_UCODE_DRV_GP1_BIT_CMD_BLOCKED);

	/* clear (again), then enable host interrupts */
	iwl_write32(trans, CSR_INT, 0xFFFFFFFF);
	iwl_enable_interrupts(trans);

	/* really make sure rfkill handshake bits are cleared */
	iwl_write32(trans, CSR_UCODE_DRV_GP1_CLR, CSR_UCODE_SW_BIT_RFKILL);
	iwl_write32(trans, CSR_UCODE_DRV_GP1_CLR, CSR_UCODE_SW_BIT_RFKILL);

	/* Load the given image to the HW */
	return iwl_pcie_load_given_ucode(trans, fw);
}