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
struct netdev_queue {struct Qdisc* qdisc_sleeping; } ;
struct net_device {scalar_t__ tx_queue_len; struct Qdisc* qdisc; } ;
struct Qdisc {TYPE_1__* ops; int /*<<< orphan*/  refcnt; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* attach ) (struct Qdisc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TC_H_ROOT ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  attach_one_default_qdisc ; 
 int /*<<< orphan*/  mq_qdisc_ops ; 
 int /*<<< orphan*/  netdev_for_each_tx_queue (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_is_multiqueue (struct net_device*) ; 
 struct Qdisc* qdisc_create_dflt (struct net_device*,struct netdev_queue*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct Qdisc*) ; 

__attribute__((used)) static void attach_default_qdiscs(struct net_device *dev)
{
	struct netdev_queue *txq;
	struct Qdisc *qdisc;

	txq = netdev_get_tx_queue(dev, 0);

	if (!netif_is_multiqueue(dev) || dev->tx_queue_len == 0) {
		netdev_for_each_tx_queue(dev, attach_one_default_qdisc, NULL);
		dev->qdisc = txq->qdisc_sleeping;
		atomic_inc(&dev->qdisc->refcnt);
	} else {
		qdisc = qdisc_create_dflt(dev, txq, &mq_qdisc_ops, TC_H_ROOT);
		if (qdisc) {
			qdisc->ops->attach(qdisc);
			dev->qdisc = qdisc;
		}
	}
}