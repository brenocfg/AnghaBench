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
struct iwl_trans {int /*<<< orphan*/  op_mode; } ;

/* Variables and functions */
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  STATUS_RFKILL ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_disable_interrupts (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_enable_rfkill_int (struct iwl_trans*) ; 
 int iwl_is_rfkill_set (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_op_mode_hw_rf_kill (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwl_pcie_apm_stop (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_disable_ict (struct iwl_trans*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void iwl_trans_pcie_stop_hw(struct iwl_trans *trans,
				   bool op_mode_leaving)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	bool hw_rfkill;
	unsigned long flags;

	spin_lock_irqsave(&trans_pcie->irq_lock, flags);
	iwl_disable_interrupts(trans);
	spin_unlock_irqrestore(&trans_pcie->irq_lock, flags);

	iwl_pcie_apm_stop(trans);

	spin_lock_irqsave(&trans_pcie->irq_lock, flags);
	iwl_disable_interrupts(trans);
	spin_unlock_irqrestore(&trans_pcie->irq_lock, flags);

	iwl_pcie_disable_ict(trans);

	if (!op_mode_leaving) {
		/*
		 * Even if we stop the HW, we still want the RF kill
		 * interrupt
		 */
		iwl_enable_rfkill_int(trans);

		/*
		 * Check again since the RF kill state may have changed while
		 * all the interrupts were disabled, in this case we couldn't
		 * receive the RF kill interrupt and update the state in the
		 * op_mode.
		 */
		hw_rfkill = iwl_is_rfkill_set(trans);
		if (hw_rfkill)
			set_bit(STATUS_RFKILL, &trans_pcie->status);
		else
			clear_bit(STATUS_RFKILL, &trans_pcie->status);
		iwl_op_mode_hw_rf_kill(trans->op_mode, hw_rfkill);
	}
}