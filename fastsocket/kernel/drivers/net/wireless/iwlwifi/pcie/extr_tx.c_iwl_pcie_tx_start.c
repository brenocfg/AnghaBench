#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_6__ {int dma; } ;
struct iwl_trans_pcie {scalar_t__ scd_base_addr; int /*<<< orphan*/  cmd_fifo; int /*<<< orphan*/  cmd_queue; TYPE_3__ scd_bc_tbls; int /*<<< orphan*/  queue_used; int /*<<< orphan*/  queue_stopped; } ;
struct iwl_trans {TYPE_2__* cfg; } ;
struct TYPE_5__ {TYPE_1__* base_params; } ;
struct TYPE_4__ {int num_of_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  APMG_PCIDEV_STT_REG ; 
 int /*<<< orphan*/  APMG_PCIDEV_STT_VAL_L1_ACT_DIS ; 
 int FH_TCSR_CHNL_NUM ; 
 int /*<<< orphan*/  FH_TCSR_CHNL_TX_CONFIG_REG (int) ; 
 scalar_t__ FH_TCSR_TX_CONFIG_REG_VAL_DMA_CHNL_ENABLE ; 
 scalar_t__ FH_TCSR_TX_CONFIG_REG_VAL_DMA_CREDIT_ENABLE ; 
 int /*<<< orphan*/  FH_TX_CHICKEN_BITS_REG ; 
 scalar_t__ FH_TX_CHICKEN_BITS_SCD_AUTO_RETRY_EN ; 
 int /*<<< orphan*/  IWL_MASK (int /*<<< orphan*/ ,int) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  SCD_CHAINEXT_EN ; 
 int SCD_CONTEXT_MEM_LOWER_BOUND ; 
 int /*<<< orphan*/  SCD_DRAM_BASE_ADDR ; 
 int /*<<< orphan*/  SCD_SRAM_BASE_ADDR ; 
 int SCD_TRANS_TBL_OFFSET_QUEUE (int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  iwl_clear_bits_prph (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_pcie_txq_set_sched (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_read_direct32 (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_read_prph (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_trans_ac_txq_enable (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_trans_write_mem (struct iwl_trans*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  iwl_write_direct32 (struct iwl_trans*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  iwl_write_prph (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void iwl_pcie_tx_start(struct iwl_trans *trans, u32 scd_base_addr)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	int nq = trans->cfg->base_params->num_of_queues;
	int chan;
	u32 reg_val;
	int clear_dwords = (SCD_TRANS_TBL_OFFSET_QUEUE(nq) -
				SCD_CONTEXT_MEM_LOWER_BOUND) / sizeof(u32);

	/* make sure all queue are not stopped/used */
	memset(trans_pcie->queue_stopped, 0, sizeof(trans_pcie->queue_stopped));
	memset(trans_pcie->queue_used, 0, sizeof(trans_pcie->queue_used));

	trans_pcie->scd_base_addr =
		iwl_read_prph(trans, SCD_SRAM_BASE_ADDR);

	WARN_ON(scd_base_addr != 0 &&
		scd_base_addr != trans_pcie->scd_base_addr);

	/* reset context data, TX status and translation data */
	iwl_trans_write_mem(trans, trans_pcie->scd_base_addr +
				   SCD_CONTEXT_MEM_LOWER_BOUND,
			    NULL, clear_dwords);

	iwl_write_prph(trans, SCD_DRAM_BASE_ADDR,
		       trans_pcie->scd_bc_tbls.dma >> 10);

	/* The chain extension of the SCD doesn't work well. This feature is
	 * enabled by default by the HW, so we need to disable it manually.
	 */
	iwl_write_prph(trans, SCD_CHAINEXT_EN, 0);

	iwl_trans_ac_txq_enable(trans, trans_pcie->cmd_queue,
				trans_pcie->cmd_fifo);

	/* Activate all Tx DMA/FIFO channels */
	iwl_pcie_txq_set_sched(trans, IWL_MASK(0, 7));

	/* Enable DMA channel */
	for (chan = 0; chan < FH_TCSR_CHNL_NUM; chan++)
		iwl_write_direct32(trans, FH_TCSR_CHNL_TX_CONFIG_REG(chan),
				   FH_TCSR_TX_CONFIG_REG_VAL_DMA_CHNL_ENABLE |
				   FH_TCSR_TX_CONFIG_REG_VAL_DMA_CREDIT_ENABLE);

	/* Update FH chicken bits */
	reg_val = iwl_read_direct32(trans, FH_TX_CHICKEN_BITS_REG);
	iwl_write_direct32(trans, FH_TX_CHICKEN_BITS_REG,
			   reg_val | FH_TX_CHICKEN_BITS_SCD_AUTO_RETRY_EN);

	/* Enable L1-Active */
	iwl_clear_bits_prph(trans, APMG_PCIDEV_STT_REG,
			    APMG_PCIDEV_STT_VAL_L1_ACT_DIS);
}