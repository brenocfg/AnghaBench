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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int dma_addr; } ;
struct iwl_txq {TYPE_1__ q; int /*<<< orphan*/  lock; scalar_t__ need_update; } ;
struct iwl_trans {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  FH_MEM_CBBC_QUEUE (int /*<<< orphan*/ ) ; 
 int TFD_QUEUE_SIZE_MAX ; 
 int iwl_queue_init (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_write_direct32 (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_pcie_txq_init(struct iwl_trans *trans, struct iwl_txq *txq,
			      int slots_num, u32 txq_id)
{
	int ret;

	txq->need_update = 0;

	/* TFD_QUEUE_SIZE_MAX must be power-of-two size, otherwise
	 * iwl_queue_inc_wrap and iwl_queue_dec_wrap are broken. */
	BUILD_BUG_ON(TFD_QUEUE_SIZE_MAX & (TFD_QUEUE_SIZE_MAX - 1));

	/* Initialize queue's high/low-water marks, and head/tail indexes */
	ret = iwl_queue_init(&txq->q, TFD_QUEUE_SIZE_MAX, slots_num,
			txq_id);
	if (ret)
		return ret;

	spin_lock_init(&txq->lock);

	/*
	 * Tell nic where to find circular buffer of Tx Frame Descriptors for
	 * given Tx queue, and enable the DMA channel used for that queue.
	 * Circular buffer (TFD queue in DRAM) physical base address */
	iwl_write_direct32(trans, FH_MEM_CBBC_QUEUE(txq_id),
			   txq->q.dma_addr >> 8);

	return 0;
}