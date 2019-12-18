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
struct iwl_queue {scalar_t__ write_ptr; scalar_t__ read_ptr; int /*<<< orphan*/  n_bd; } ;
struct iwl_txq {int active; int /*<<< orphan*/  lock; struct iwl_queue q; } ;
struct iwl_trans_pcie {struct iwl_txq* txq; } ;
struct iwl_trans {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_TX_REPLY (struct iwl_trans*,char*,int,scalar_t__) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_txq_free_tfd (struct iwl_trans*,struct iwl_txq*) ; 
 scalar_t__ iwl_queue_inc_wrap (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_wake_queue (struct iwl_trans*,struct iwl_txq*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_pcie_txq_unmap(struct iwl_trans *trans, int txq_id)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	struct iwl_txq *txq = &trans_pcie->txq[txq_id];
	struct iwl_queue *q = &txq->q;

	if (!q->n_bd)
		return;

	spin_lock_bh(&txq->lock);
	while (q->write_ptr != q->read_ptr) {
		IWL_DEBUG_TX_REPLY(trans, "Q %d Free %d\n",
				   txq_id, q->read_ptr);
		iwl_pcie_txq_free_tfd(trans, txq);
		q->read_ptr = iwl_queue_inc_wrap(q->read_ptr, q->n_bd);
	}
	txq->active = false;
	spin_unlock_bh(&txq->lock);

	/* just in case - this queue may have been stopped */
	iwl_wake_queue(trans, txq);
}