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
struct iwl_trans_pcie {int /*<<< orphan*/  reg_lock; } ;
struct iwl_trans {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_GP_CNTRL ; 
 int /*<<< orphan*/  CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  __acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __iwl_trans_pcie_clear_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void iwl_trans_pcie_release_nic_access(struct iwl_trans *trans,
					      unsigned long *flags)
{
	struct iwl_trans_pcie *pcie_trans = IWL_TRANS_GET_PCIE_TRANS(trans);

	lockdep_assert_held(&pcie_trans->reg_lock);

	/*
	 * Fool sparse by faking we acquiring the lock - sparse will
	 * track nic_access anyway.
	 */
	__acquire(&pcie_trans->reg_lock);

	__iwl_trans_pcie_clear_bit(trans, CSR_GP_CNTRL,
				   CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ);
	/*
	 * Above we read the CSR_GP_CNTRL register, which will flush
	 * any previous writes, but we need the write that clears the
	 * MAC_ACCESS_REQ bit to be performed before any other writes
	 * scheduled on different CPUs (after we drop reg_lock).
	 */
	mmiowb();
	spin_unlock_irqrestore(&pcie_trans->reg_lock, *flags);
}