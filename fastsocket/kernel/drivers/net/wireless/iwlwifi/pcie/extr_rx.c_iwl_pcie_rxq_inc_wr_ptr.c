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
typedef  int u32 ;
struct iwl_trans_pcie {int /*<<< orphan*/  status; } ;
struct iwl_trans {TYPE_2__* cfg; } ;
struct iwl_rxq {scalar_t__ need_update; int write_actual; int write; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {TYPE_1__* base_params; } ;
struct TYPE_3__ {scalar_t__ shadow_reg_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_GP_CNTRL ; 
 int /*<<< orphan*/  CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ ; 
 int /*<<< orphan*/  CSR_UCODE_DRV_GP1 ; 
 int CSR_UCODE_DRV_GP1_BIT_MAC_SLEEP ; 
 int /*<<< orphan*/  FH_RSCSR_CHNL0_WPTR ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_trans*,char*,int) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  STATUS_TPOWER_PMI ; 
 int iwl_read32 (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_set_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_write32 (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwl_write_direct32 (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_pcie_rxq_inc_wr_ptr(struct iwl_trans *trans, struct iwl_rxq *q)
{
	unsigned long flags;
	u32 reg;

	spin_lock_irqsave(&q->lock, flags);

	if (q->need_update == 0)
		goto exit_unlock;

	if (trans->cfg->base_params->shadow_reg_enable) {
		/* shadow register enabled */
		/* Device expects a multiple of 8 */
		q->write_actual = (q->write & ~0x7);
		iwl_write32(trans, FH_RSCSR_CHNL0_WPTR, q->write_actual);
	} else {
		struct iwl_trans_pcie *trans_pcie =
			IWL_TRANS_GET_PCIE_TRANS(trans);

		/* If power-saving is in use, make sure device is awake */
		if (test_bit(STATUS_TPOWER_PMI, &trans_pcie->status)) {
			reg = iwl_read32(trans, CSR_UCODE_DRV_GP1);

			if (reg & CSR_UCODE_DRV_GP1_BIT_MAC_SLEEP) {
				IWL_DEBUG_INFO(trans,
					"Rx queue requesting wakeup,"
					" GP1 = 0x%x\n", reg);
				iwl_set_bit(trans, CSR_GP_CNTRL,
					CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ);
				goto exit_unlock;
			}

			q->write_actual = (q->write & ~0x7);
			iwl_write_direct32(trans, FH_RSCSR_CHNL0_WPTR,
					q->write_actual);

		/* Else device is assumed to be awake */
		} else {
			/* Device expects a multiple of 8 */
			q->write_actual = (q->write & ~0x7);
			iwl_write_direct32(trans, FH_RSCSR_CHNL0_WPTR,
				q->write_actual);
		}
	}
	q->need_update = 0;

 exit_unlock:
	spin_unlock_irqrestore(&q->lock, flags);
}