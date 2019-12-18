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
struct iwl_trans {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_GP_CNTRL ; 
 int /*<<< orphan*/  CSR_GP_CNTRL_REG_FLAG_INIT_DONE ; 
 int /*<<< orphan*/  CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ ; 
 int /*<<< orphan*/  CSR_UCODE_DRV_GP1_BIT_D3_CFG_COMPLETE ; 
 int /*<<< orphan*/  CSR_UCODE_DRV_GP1_SET ; 
 int /*<<< orphan*/  iwl_clear_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_disable_interrupts (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_disable_ict (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_set_pwr (struct iwl_trans*,int) ; 
 int /*<<< orphan*/  iwl_trans_pcie_tx_reset (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_write32 (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_trans_pcie_d3_suspend(struct iwl_trans *trans)
{
	/* let the ucode operate on its own */
	iwl_write32(trans, CSR_UCODE_DRV_GP1_SET,
		    CSR_UCODE_DRV_GP1_BIT_D3_CFG_COMPLETE);

	iwl_disable_interrupts(trans);
	iwl_pcie_disable_ict(trans);

	iwl_clear_bit(trans, CSR_GP_CNTRL,
		      CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ);
	iwl_clear_bit(trans, CSR_GP_CNTRL,
		      CSR_GP_CNTRL_REG_FLAG_INIT_DONE);

	/*
	 * reset TX queues -- some of their registers reset during S3
	 * so if we don't reset everything here the D3 image would try
	 * to execute some invalid memory upon resume
	 */
	iwl_trans_pcie_tx_reset(trans);

	iwl_pcie_set_pwr(trans, true);
}