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
struct nlattr {int dummy; } ;
struct netdev_queue {int dummy; } ;
struct net_device {unsigned int num_tx_queues; } ;
struct mq_sched {struct Qdisc** qdiscs; } ;
struct Qdisc {scalar_t__ parent; int /*<<< orphan*/  flags; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TCQ_F_CAN_BYPASS ; 
 int /*<<< orphan*/  TCQ_F_MQROOT ; 
 int /*<<< orphan*/  TC_H_MAJ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TC_H_MAKE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TC_H_MIN (unsigned int) ; 
 scalar_t__ TC_H_ROOT ; 
 struct Qdisc** kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mq_destroy (struct Qdisc*) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,unsigned int) ; 
 int /*<<< orphan*/  netif_is_multiqueue (struct net_device*) ; 
 int /*<<< orphan*/  pfifo_fast_ops ; 
 struct Qdisc* qdisc_create_dflt (struct net_device*,struct netdev_queue*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct net_device* qdisc_dev (struct Qdisc*) ; 
 struct mq_sched* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static int mq_init(struct Qdisc *sch, struct nlattr *opt)
{
	struct net_device *dev = qdisc_dev(sch);
	struct mq_sched *priv = qdisc_priv(sch);
	struct netdev_queue *dev_queue;
	struct Qdisc *qdisc;
	unsigned int ntx;

	if (sch->parent != TC_H_ROOT)
		return -EOPNOTSUPP;

	if (!netif_is_multiqueue(dev))
		return -EOPNOTSUPP;

	/* pre-allocate qdiscs, attachment can't fail */
	priv->qdiscs = kcalloc(dev->num_tx_queues, sizeof(priv->qdiscs[0]),
			       GFP_KERNEL);
	if (priv->qdiscs == NULL)
		return -ENOMEM;

	for (ntx = 0; ntx < dev->num_tx_queues; ntx++) {
		dev_queue = netdev_get_tx_queue(dev, ntx);
		qdisc = qdisc_create_dflt(dev, dev_queue, &pfifo_fast_ops,
					  TC_H_MAKE(TC_H_MAJ(sch->handle),
						    TC_H_MIN(ntx + 1)));
		if (qdisc == NULL)
			goto err;
		qdisc->flags |= TCQ_F_CAN_BYPASS;
		priv->qdiscs[ntx] = qdisc;
	}

	sch->flags |= TCQ_F_MQROOT;
	return 0;

err:
	mq_destroy(sch);
	return -ENOMEM;
}