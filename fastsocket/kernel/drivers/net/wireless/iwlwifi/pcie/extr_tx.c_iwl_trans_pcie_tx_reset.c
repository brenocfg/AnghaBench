#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int dma_addr; scalar_t__ write_ptr; scalar_t__ read_ptr; } ;
struct iwl_txq {TYPE_3__ q; } ;
struct TYPE_8__ {int dma; } ;
struct iwl_trans_pcie {int /*<<< orphan*/  scd_base_addr; TYPE_4__ kw; struct iwl_txq* txq; } ;
struct iwl_trans {TYPE_2__* cfg; } ;
struct TYPE_6__ {TYPE_1__* base_params; } ;
struct TYPE_5__ {int num_of_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  FH_KW_MEM_ADDR_REG ; 
 int /*<<< orphan*/  FH_MEM_CBBC_QUEUE (int) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_tx_start (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_pcie_txq_unmap (struct iwl_trans*,int) ; 
 int /*<<< orphan*/  iwl_write_direct32 (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 

void iwl_trans_pcie_tx_reset(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	int txq_id;

	for (txq_id = 0; txq_id < trans->cfg->base_params->num_of_queues;
	     txq_id++) {
		struct iwl_txq *txq = &trans_pcie->txq[txq_id];

		iwl_write_direct32(trans, FH_MEM_CBBC_QUEUE(txq_id),
				   txq->q.dma_addr >> 8);
		iwl_pcie_txq_unmap(trans, txq_id);
		txq->q.read_ptr = 0;
		txq->q.write_ptr = 0;
	}

	/* Tell NIC where to find the "keep warm" buffer */
	iwl_write_direct32(trans, FH_KW_MEM_ADDR_REG,
			   trans_pcie->kw.dma >> 4);

	iwl_pcie_tx_start(trans, trans_pcie->scd_base_addr);
}