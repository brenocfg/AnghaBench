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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct netdev_queue {int dummy; } ;
struct net_device {int dummy; } ;
struct Qdisc {int flags; int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int NET_XMIT_DROP ; 
 int NET_XMIT_SUCCESS ; 
 int TCQ_F_CAN_BYPASS ; 
 int /*<<< orphan*/  __QDISC_STATE_DEACTIVATED ; 
 int /*<<< orphan*/  __QDISC_STATE_RUNNING ; 
 int /*<<< orphan*/  __qdisc_run (struct Qdisc*) ; 
 int /*<<< orphan*/  __qdisc_update_bstats (struct Qdisc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int qdisc_enqueue_root (struct sk_buff*,struct Qdisc*) ; 
 int /*<<< orphan*/ * qdisc_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_qlen (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_run (struct Qdisc*) ; 
 scalar_t__ sch_direct_xmit (struct sk_buff*,struct Qdisc*,struct net_device*,struct netdev_queue*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int __dev_xmit_skb(struct sk_buff *skb, struct Qdisc *q,
				 struct net_device *dev,
				 struct netdev_queue *txq)
{
	spinlock_t *root_lock = qdisc_lock(q);
	int rc;

	spin_lock(root_lock);
	if (unlikely(test_bit(__QDISC_STATE_DEACTIVATED, &q->state))) {
		kfree_skb(skb);
		rc = NET_XMIT_DROP;
	} else if ((q->flags & TCQ_F_CAN_BYPASS) && !qdisc_qlen(q) &&
		   !test_and_set_bit(__QDISC_STATE_RUNNING, &q->state)) {
		/*
		 * This is a work-conserving queue; there are no old skbs
		 * waiting to be sent out; and the qdisc is not running -
		 * xmit the skb directly.
		 */
		__qdisc_update_bstats(q, skb->len);
		if (sch_direct_xmit(skb, q, dev, txq, root_lock))
			__qdisc_run(q);
		else
			clear_bit(__QDISC_STATE_RUNNING, &q->state);

		rc = NET_XMIT_SUCCESS;
	} else {
		rc = qdisc_enqueue_root(skb, q);
		qdisc_run(q);
	}
	spin_unlock(root_lock);

	return rc;
}