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
struct sk_buff {int /*<<< orphan*/  priority; } ;
struct TYPE_2__ {int qlen; int /*<<< orphan*/  lock; } ;
struct sge_ofld_txq {TYPE_1__ sendq; } ;

/* Variables and functions */
 int NET_XMIT_SUCCESS ; 
 int /*<<< orphan*/  __skb_queue_tail (TYPE_1__*,struct sk_buff*) ; 
 int /*<<< orphan*/  calc_tx_flits_ofld (struct sk_buff*) ; 
 int /*<<< orphan*/  service_ofldq (struct sge_ofld_txq*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ofld_xmit(struct sge_ofld_txq *q, struct sk_buff *skb)
{
	skb->priority = calc_tx_flits_ofld(skb);       /* save for restart */
	spin_lock(&q->sendq.lock);
	__skb_queue_tail(&q->sendq, skb);
	if (q->sendq.qlen == 1)
		service_ofldq(q);
	spin_unlock(&q->sendq.lock);
	return NET_XMIT_SUCCESS;
}