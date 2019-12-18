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
struct netdev_queue {struct Qdisc* qdisc_sleeping; } ;
struct net_device {unsigned int num_tx_queues; } ;
struct Qdisc {int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  __QDISC_STATE_RUNNING ; 
 int /*<<< orphan*/  __QDISC_STATE_SCHED ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,unsigned int) ; 
 int /*<<< orphan*/ * qdisc_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool some_qdisc_is_busy(struct net_device *dev)
{
	unsigned int i;

	for (i = 0; i < dev->num_tx_queues; i++) {
		struct netdev_queue *dev_queue;
		spinlock_t *root_lock;
		struct Qdisc *q;
		int val;

		dev_queue = netdev_get_tx_queue(dev, i);
		q = dev_queue->qdisc_sleeping;
		root_lock = qdisc_lock(q);

		spin_lock_bh(root_lock);

		val = (test_bit(__QDISC_STATE_RUNNING, &q->state) ||
		       test_bit(__QDISC_STATE_SCHED, &q->state));

		spin_unlock_bh(root_lock);

		if (val)
			return true;
	}
	return false;
}