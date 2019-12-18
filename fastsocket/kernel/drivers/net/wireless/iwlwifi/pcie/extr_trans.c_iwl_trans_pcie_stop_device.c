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
struct iwl_trans_pcie {int /*<<< orphan*/  status; int /*<<< orphan*/  irq_lock; } ;
struct iwl_trans {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  APMG_CLK_DIS_REG ; 
 int /*<<< orphan*/  APMG_CLK_VAL_DMA_CLK_RQT ; 
 int /*<<< orphan*/  CSR_GP_CNTRL ; 
 int /*<<< orphan*/  CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ ; 
 int /*<<< orphan*/  CSR_RESET ; 
 int /*<<< orphan*/  CSR_RESET_REG_FLAG_NEVO_RESET ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  STATUS_DEVICE_ENABLED ; 
 int /*<<< orphan*/  STATUS_HCMD_ACTIVE ; 
 int /*<<< orphan*/  STATUS_INT_ENABLED ; 
 int /*<<< orphan*/  STATUS_RFKILL ; 
 int /*<<< orphan*/  STATUS_TPOWER_PMI ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_clear_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_disable_interrupts (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_enable_rfkill_int (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_apm_stop (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_disable_ict (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_rx_stop (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_tx_stop (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_write32 (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_write_prph (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void iwl_trans_pcie_stop_device(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	unsigned long flags;

	/* tell the device to stop sending interrupts */
	spin_lock_irqsave(&trans_pcie->irq_lock, flags);
	iwl_disable_interrupts(trans);
	spin_unlock_irqrestore(&trans_pcie->irq_lock, flags);

	/* device going down, Stop using ICT table */
	iwl_pcie_disable_ict(trans);

	/*
	 * If a HW restart happens during firmware loading,
	 * then the firmware loading might call this function
	 * and later it might be called again due to the
	 * restart. So don't process again if the device is
	 * already dead.
	 */
	if (test_bit(STATUS_DEVICE_ENABLED, &trans_pcie->status)) {
		iwl_pcie_tx_stop(trans);
		iwl_pcie_rx_stop(trans);

		/* Power-down device's busmaster DMA clocks */
		iwl_write_prph(trans, APMG_CLK_DIS_REG,
			       APMG_CLK_VAL_DMA_CLK_RQT);
		udelay(5);
	}

	/* Make sure (redundant) we've released our request to stay awake */
	iwl_clear_bit(trans, CSR_GP_CNTRL,
		      CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ);

	/* Stop the device, and put it in low power state */
	iwl_pcie_apm_stop(trans);

	/* Upon stop, the APM issues an interrupt if HW RF kill is set.
	 * Clean again the interrupt here
	 */
	spin_lock_irqsave(&trans_pcie->irq_lock, flags);
	iwl_disable_interrupts(trans);
	spin_unlock_irqrestore(&trans_pcie->irq_lock, flags);

	iwl_enable_rfkill_int(trans);

	/* stop and reset the on-board processor */
	iwl_write32(trans, CSR_RESET, CSR_RESET_REG_FLAG_NEVO_RESET);

	/* clear all status bits */
	clear_bit(STATUS_HCMD_ACTIVE, &trans_pcie->status);
	clear_bit(STATUS_INT_ENABLED, &trans_pcie->status);
	clear_bit(STATUS_DEVICE_ENABLED, &trans_pcie->status);
	clear_bit(STATUS_TPOWER_PMI, &trans_pcie->status);
	clear_bit(STATUS_RFKILL, &trans_pcie->status);
}