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
struct sk_buff {int dummy; } ;
struct sge {struct cmdQ* cmdQ; struct adapter* adapter; } ;
struct cmdQ {unsigned int size; unsigned int in_use; unsigned int genbit; unsigned int pidx; int /*<<< orphan*/  lock; int /*<<< orphan*/  status; } ;
struct adapter {scalar_t__ regs; } ;
struct TYPE_2__ {int nr_frags; } ;

/* Variables and functions */
 scalar_t__ A_SG_DOORBELL ; 
 int /*<<< orphan*/  CMDQ_STAT_LAST_PKT_DB ; 
 int /*<<< orphan*/  CMDQ_STAT_RUNNING ; 
 int /*<<< orphan*/  F_CMDQ0_ENABLE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ compute_large_page_tx_descs (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int) ; 
 int /*<<< orphan*/  reclaim_completed_tx (struct sge*,struct cmdQ*) ; 
 struct sk_buff* sched_skb (struct sge*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_tx_descs (struct adapter*,struct sk_buff*,unsigned int,unsigned int,struct cmdQ*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void restart_sched(unsigned long arg)
{
	struct sge *sge = (struct sge *) arg;
	struct adapter *adapter = sge->adapter;
	struct cmdQ *q = &sge->cmdQ[0];
	struct sk_buff *skb;
	unsigned int credits, queued_skb = 0;

	spin_lock(&q->lock);
	reclaim_completed_tx(sge, q);

	credits = q->size - q->in_use;
	pr_debug("restart_sched credits=%d\n", credits);
	while ((skb = sched_skb(sge, NULL, credits)) != NULL) {
		unsigned int genbit, pidx, count;
	        count = 1 + skb_shinfo(skb)->nr_frags;
		count += compute_large_page_tx_descs(skb);
		q->in_use += count;
		genbit = q->genbit;
		pidx = q->pidx;
		q->pidx += count;
		if (q->pidx >= q->size) {
			q->pidx -= q->size;
			q->genbit ^= 1;
		}
		write_tx_descs(adapter, skb, pidx, genbit, q);
	        credits = q->size - q->in_use;
		queued_skb = 1;
	}

	if (queued_skb) {
		clear_bit(CMDQ_STAT_LAST_PKT_DB, &q->status);
		if (test_and_set_bit(CMDQ_STAT_RUNNING, &q->status) == 0) {
			set_bit(CMDQ_STAT_LAST_PKT_DB, &q->status);
			writel(F_CMDQ0_ENABLE, adapter->regs + A_SG_DOORBELL);
		}
	}
	spin_unlock(&q->lock);
}