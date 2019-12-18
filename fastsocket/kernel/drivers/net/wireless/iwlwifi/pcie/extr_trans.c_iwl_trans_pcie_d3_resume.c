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
typedef  int u32 ;
struct iwl_trans {int dummy; } ;
typedef  enum iwl_d3_status { ____Placeholder_iwl_d3_status } iwl_d3_status ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_GP_CNTRL ; 
 int /*<<< orphan*/  CSR_GP_CNTRL_REG_FLAG_INIT_DONE ; 
 int /*<<< orphan*/  CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ ; 
 int /*<<< orphan*/  CSR_GP_CNTRL_REG_FLAG_MAC_CLOCK_READY ; 
 int /*<<< orphan*/  CSR_RESET ; 
 int CSR_RESET_REG_FLAG_NEVO_RESET ; 
 int /*<<< orphan*/  CSR_UCODE_DRV_GP1_BIT_D3_CFG_COMPLETE ; 
 int /*<<< orphan*/  CSR_UCODE_DRV_GP1_CLR ; 
 int IWL_D3_STATUS_ALIVE ; 
 int IWL_D3_STATUS_RESET ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*) ; 
 int /*<<< orphan*/  iwl_pcie_reset_ict (struct iwl_trans*) ; 
 int iwl_pcie_rx_init (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_set_pwr (struct iwl_trans*,int) ; 
 int iwl_poll_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int iwl_read32 (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_set_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_trans_pcie_tx_reset (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_write32 (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_trans_pcie_d3_resume(struct iwl_trans *trans,
				    enum iwl_d3_status *status)
{
	u32 val;
	int ret;

	iwl_pcie_set_pwr(trans, false);

	val = iwl_read32(trans, CSR_RESET);
	if (val & CSR_RESET_REG_FLAG_NEVO_RESET) {
		*status = IWL_D3_STATUS_RESET;
		return 0;
	}

	/*
	 * Also enables interrupts - none will happen as the device doesn't
	 * know we're waking it up, only when the opmode actually tells it
	 * after this call.
	 */
	iwl_pcie_reset_ict(trans);

	iwl_set_bit(trans, CSR_GP_CNTRL, CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ);
	iwl_set_bit(trans, CSR_GP_CNTRL, CSR_GP_CNTRL_REG_FLAG_INIT_DONE);

	ret = iwl_poll_bit(trans, CSR_GP_CNTRL,
			   CSR_GP_CNTRL_REG_FLAG_MAC_CLOCK_READY,
			   CSR_GP_CNTRL_REG_FLAG_MAC_CLOCK_READY,
			   25000);
	if (ret) {
		IWL_ERR(trans, "Failed to resume the device (mac ready)\n");
		return ret;
	}

	iwl_trans_pcie_tx_reset(trans);

	ret = iwl_pcie_rx_init(trans);
	if (ret) {
		IWL_ERR(trans, "Failed to resume the device (RX reset)\n");
		return ret;
	}

	iwl_write32(trans, CSR_UCODE_DRV_GP1_CLR,
		    CSR_UCODE_DRV_GP1_BIT_D3_CFG_COMPLETE);

	*status = IWL_D3_STATUS_ALIVE;
	return 0;
}