#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int max_txq_num; } ;
struct il_priv {int cmd_queue; int /*<<< orphan*/  scd_bc_tbls; int /*<<< orphan*/  kw; TYPE_1__ hw_params; scalar_t__ txq; } ;

/* Variables and functions */
 int /*<<< orphan*/  il4965_free_dma_ptr (struct il_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  il_cmd_queue_free (struct il_priv*) ; 
 int /*<<< orphan*/  il_free_txq_mem (struct il_priv*) ; 
 int /*<<< orphan*/  il_tx_queue_free (struct il_priv*,int) ; 

void
il4965_hw_txq_ctx_free(struct il_priv *il)
{
	int txq_id;

	/* Tx queues */
	if (il->txq) {
		for (txq_id = 0; txq_id < il->hw_params.max_txq_num; txq_id++)
			if (txq_id == il->cmd_queue)
				il_cmd_queue_free(il);
			else
				il_tx_queue_free(il, txq_id);
	}
	il4965_free_dma_ptr(il, &il->kw);

	il4965_free_dma_ptr(il, &il->scd_bc_tbls);

	/* free tx queue structure */
	il_free_txq_mem(il);
}