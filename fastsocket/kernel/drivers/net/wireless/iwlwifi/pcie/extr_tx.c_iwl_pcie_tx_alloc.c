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
typedef  int u16 ;
struct iwlagn_scd_bc_tbl {int dummy; } ;
struct iwl_txq {int dummy; } ;
struct iwl_trans_pcie {int cmd_queue; int /*<<< orphan*/ * txq; int /*<<< orphan*/  kw; int /*<<< orphan*/  scd_bc_tbls; } ;
struct iwl_trans {TYPE_2__* cfg; } ;
struct TYPE_4__ {TYPE_1__* base_params; } ;
struct TYPE_3__ {int num_of_queues; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*,...) ; 
 int IWL_KW_SIZE ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int TFD_CMD_SLOTS ; 
 int TFD_TX_CMD_SLOTS ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ *) ; 
 int iwl_pcie_alloc_dma_ptr (struct iwl_trans*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  iwl_pcie_tx_free (struct iwl_trans*) ; 
 int iwl_pcie_txq_alloc (struct iwl_trans*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_pcie_tx_alloc(struct iwl_trans *trans)
{
	int ret;
	int txq_id, slots_num;
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	u16 scd_bc_tbls_size = trans->cfg->base_params->num_of_queues *
			sizeof(struct iwlagn_scd_bc_tbl);

	/*It is not allowed to alloc twice, so warn when this happens.
	 * We cannot rely on the previous allocation, so free and fail */
	if (WARN_ON(trans_pcie->txq)) {
		ret = -EINVAL;
		goto error;
	}

	ret = iwl_pcie_alloc_dma_ptr(trans, &trans_pcie->scd_bc_tbls,
				   scd_bc_tbls_size);
	if (ret) {
		IWL_ERR(trans, "Scheduler BC Table allocation failed\n");
		goto error;
	}

	/* Alloc keep-warm buffer */
	ret = iwl_pcie_alloc_dma_ptr(trans, &trans_pcie->kw, IWL_KW_SIZE);
	if (ret) {
		IWL_ERR(trans, "Keep Warm allocation failed\n");
		goto error;
	}

	trans_pcie->txq = kcalloc(trans->cfg->base_params->num_of_queues,
				  sizeof(struct iwl_txq), GFP_KERNEL);
	if (!trans_pcie->txq) {
		IWL_ERR(trans, "Not enough memory for txq\n");
		ret = ENOMEM;
		goto error;
	}

	/* Alloc and init all Tx queues, including the command queue (#4/#9) */
	for (txq_id = 0; txq_id < trans->cfg->base_params->num_of_queues;
	     txq_id++) {
		slots_num = (txq_id == trans_pcie->cmd_queue) ?
					TFD_CMD_SLOTS : TFD_TX_CMD_SLOTS;
		ret = iwl_pcie_txq_alloc(trans, &trans_pcie->txq[txq_id],
					  slots_num, txq_id);
		if (ret) {
			IWL_ERR(trans, "Tx %d queue alloc failed\n", txq_id);
			goto error;
		}
	}

	return 0;

error:
	iwl_pcie_tx_free(trans);

	return ret;
}