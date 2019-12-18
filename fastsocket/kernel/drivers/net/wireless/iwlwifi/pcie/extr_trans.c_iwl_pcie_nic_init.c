#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iwl_trans_pcie {int /*<<< orphan*/  irq_lock; } ;
struct iwl_trans {TYPE_2__* cfg; int /*<<< orphan*/  op_mode; } ;
struct TYPE_4__ {TYPE_1__* base_params; } ;
struct TYPE_3__ {scalar_t__ shadow_reg_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_INT_COALESCING ; 
 int /*<<< orphan*/  CSR_MAC_SHADOW_REG_CTRL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_trans*,char*) ; 
 int /*<<< orphan*/  IWL_HOST_INT_CALIB_TIMEOUT_DEF ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_op_mode_nic_config (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_pcie_apm_init (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_rx_init (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_set_pwr (struct iwl_trans*,int) ; 
 scalar_t__ iwl_pcie_tx_init (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_set_bit (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwl_write8 (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int iwl_pcie_nic_init(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	unsigned long flags;

	/* nic_init */
	spin_lock_irqsave(&trans_pcie->irq_lock, flags);
	iwl_pcie_apm_init(trans);

	/* Set interrupt coalescing calibration timer to default (512 usecs) */
	iwl_write8(trans, CSR_INT_COALESCING, IWL_HOST_INT_CALIB_TIMEOUT_DEF);

	spin_unlock_irqrestore(&trans_pcie->irq_lock, flags);

	iwl_pcie_set_pwr(trans, false);

	iwl_op_mode_nic_config(trans->op_mode);

	/* Allocate the RX queue, or reset if it is already allocated */
	iwl_pcie_rx_init(trans);

	/* Allocate or reset and init all Tx and Command queues */
	if (iwl_pcie_tx_init(trans))
		return -ENOMEM;

	if (trans->cfg->base_params->shadow_reg_enable) {
		/* enable shadow regs in HW */
		iwl_set_bit(trans, CSR_MAC_SHADOW_REG_CTRL, 0x800FFFFF);
		IWL_DEBUG_INFO(trans, "Enabling shadow registers in device\n");
	}

	return 0;
}