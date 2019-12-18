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
struct TYPE_4__ {int max_txq_num; } ;
struct TYPE_3__ {int dma; } ;
struct il_priv {TYPE_2__ hw_params; int /*<<< orphan*/  lock; TYPE_1__ kw; } ;

/* Variables and functions */
 int /*<<< orphan*/  FH49_KW_MEM_ADDR_REG ; 
 int /*<<< orphan*/  il4965_txq_set_sched (struct il_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il_tx_queue_reset (struct il_priv*,int) ; 
 int /*<<< orphan*/  il_wr (struct il_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
il4965_txq_ctx_reset(struct il_priv *il)
{
	int txq_id;
	unsigned long flags;

	spin_lock_irqsave(&il->lock, flags);

	/* Turn off all Tx DMA fifos */
	il4965_txq_set_sched(il, 0);
	/* Tell NIC where to find the "keep warm" buffer */
	il_wr(il, FH49_KW_MEM_ADDR_REG, il->kw.dma >> 4);

	spin_unlock_irqrestore(&il->lock, flags);

	/* Alloc and init all Tx queues, including the command queue (#4) */
	for (txq_id = 0; txq_id < il->hw_params.max_txq_num; txq_id++)
		il_tx_queue_reset(il, txq_id);
}