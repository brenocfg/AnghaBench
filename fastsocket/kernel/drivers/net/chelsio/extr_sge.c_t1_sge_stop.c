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
struct sge {int /*<<< orphan*/ * espibug_skb; scalar_t__ tx_sched; int /*<<< orphan*/  tx_reclaim_timer; int /*<<< orphan*/  espibug_timer; TYPE_1__* adapter; } ;
struct TYPE_2__ {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ A_SG_CONTROL ; 
 int MAX_NPORTS ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ is_T2 (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  tx_sched_stop (struct sge*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void t1_sge_stop(struct sge *sge)
{
	int i;
	writel(0, sge->adapter->regs + A_SG_CONTROL);
	readl(sge->adapter->regs + A_SG_CONTROL); /* flush */

	if (is_T2(sge->adapter))
		del_timer_sync(&sge->espibug_timer);

	del_timer_sync(&sge->tx_reclaim_timer);
	if (sge->tx_sched)
		tx_sched_stop(sge);

	for (i = 0; i < MAX_NPORTS; i++)
		kfree_skb(sge->espibug_skb[i]);
}