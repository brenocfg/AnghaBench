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
struct net_device {unsigned int num_tx_queues; } ;
struct mq_sched {scalar_t__* qdiscs; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 int /*<<< orphan*/  qdisc_destroy (scalar_t__) ; 
 struct net_device* qdisc_dev (struct Qdisc*) ; 
 struct mq_sched* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static void mq_destroy(struct Qdisc *sch)
{
	struct net_device *dev = qdisc_dev(sch);
	struct mq_sched *priv = qdisc_priv(sch);
	unsigned int ntx;

	if (!priv->qdiscs)
		return;
	for (ntx = 0; ntx < dev->num_tx_queues && priv->qdiscs[ntx]; ntx++)
		qdisc_destroy(priv->qdiscs[ntx]);
	kfree(priv->qdiscs);
}