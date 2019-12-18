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
struct tcmsg {int /*<<< orphan*/  tcm_parent; } ;
struct netdev_queue {int dummy; } ;
struct net_device {int dummy; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 unsigned int TC_H_MIN (int /*<<< orphan*/ ) ; 
 struct netdev_queue* mq_queue_get (struct Qdisc*,unsigned int) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,int /*<<< orphan*/ ) ; 
 struct net_device* qdisc_dev (struct Qdisc*) ; 

__attribute__((used)) static struct netdev_queue *mq_select_queue(struct Qdisc *sch,
					    struct tcmsg *tcm)
{
	unsigned int ntx = TC_H_MIN(tcm->tcm_parent);
	struct netdev_queue *dev_queue = mq_queue_get(sch, ntx);

	if (!dev_queue) {
		struct net_device *dev = qdisc_dev(sch);

		return netdev_get_tx_queue(dev, 0);
	}
	return dev_queue;
}