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
struct iwl_trans_pcie {int /*<<< orphan*/  scd_bc_tbls; int /*<<< orphan*/  kw; int /*<<< orphan*/ * txq; } ;
struct iwl_trans {TYPE_2__* cfg; } ;
struct TYPE_4__ {TYPE_1__* base_params; } ;
struct TYPE_3__ {int num_of_queues; } ;

/* Variables and functions */
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_free_dma_ptr (struct iwl_trans*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_pcie_txq_free (struct iwl_trans*,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void iwl_pcie_tx_free(struct iwl_trans *trans)
{
	int txq_id;
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	/* Tx queues */
	if (trans_pcie->txq) {
		for (txq_id = 0;
		     txq_id < trans->cfg->base_params->num_of_queues; txq_id++)
			iwl_pcie_txq_free(trans, txq_id);
	}

	kfree(trans_pcie->txq);
	trans_pcie->txq = NULL;

	iwl_pcie_free_dma_ptr(trans, &trans_pcie->kw);

	iwl_pcie_free_dma_ptr(trans, &trans_pcie->scd_bc_tbls);
}