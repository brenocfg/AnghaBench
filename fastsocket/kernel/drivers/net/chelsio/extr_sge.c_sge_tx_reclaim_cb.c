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
struct sge {int /*<<< orphan*/  tx_reclaim_timer; TYPE_1__* adapter; struct cmdQ* cmdQ; } ;
struct cmdQ {int /*<<< orphan*/  lock; scalar_t__ in_use; } ;
struct TYPE_2__ {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ A_SG_DOORBELL ; 
 int /*<<< orphan*/  F_CMDQ0_ENABLE ; 
 int SGE_CMDQ_N ; 
 scalar_t__ TX_RECLAIM_PERIOD ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  reclaim_completed_tx (struct sge*,struct cmdQ*) ; 
 int /*<<< orphan*/  spin_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sge_tx_reclaim_cb(unsigned long data)
{
	int i;
	struct sge *sge = (struct sge *)data;

	for (i = 0; i < SGE_CMDQ_N; ++i) {
		struct cmdQ *q = &sge->cmdQ[i];

		if (!spin_trylock(&q->lock))
			continue;

		reclaim_completed_tx(sge, q);
		if (i == 0 && q->in_use) {    /* flush pending credits */
			writel(F_CMDQ0_ENABLE, sge->adapter->regs + A_SG_DOORBELL);
		}
		spin_unlock(&q->lock);
	}
	mod_timer(&sge->tx_reclaim_timer, jiffies + TX_RECLAIM_PERIOD);
}