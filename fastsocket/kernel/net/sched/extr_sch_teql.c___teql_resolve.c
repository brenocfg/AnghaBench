#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct teql_sched_data {struct neighbour* ncache; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  protocol; } ;
struct netdev_queue {int /*<<< orphan*/  qdisc; } ;
struct net_device {int dummy; } ;
struct neighbour {int /*<<< orphan*/  lock; int /*<<< orphan*/  ha; int /*<<< orphan*/  primary_key; TYPE_2__* tbl; int /*<<< orphan*/  refcnt; } ;
struct TYPE_4__ {int /*<<< orphan*/  key_len; } ;
struct TYPE_3__ {struct neighbour* neighbour; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct neighbour*) ; 
 int PTR_ERR (struct neighbour*) ; 
 struct neighbour* __neigh_lookup_errno (TYPE_2__*,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int dev_hard_header (struct sk_buff*,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ neigh_event_send (struct neighbour*,struct sk_buff*) ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 struct teql_sched_data* qdisc_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  teql_neigh_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xchg (struct neighbour**,struct neighbour*) ; 

__attribute__((used)) static int
__teql_resolve(struct sk_buff *skb, struct sk_buff *skb_res, struct net_device *dev)
{
	struct netdev_queue *dev_queue = netdev_get_tx_queue(dev, 0);
	struct teql_sched_data *q = qdisc_priv(dev_queue->qdisc);
	struct neighbour *mn = skb_dst(skb)->neighbour;
	struct neighbour *n = q->ncache;

	if (mn->tbl == NULL)
		return -EINVAL;
	if (n && n->tbl == mn->tbl &&
	    memcmp(n->primary_key, mn->primary_key, mn->tbl->key_len) == 0) {
		atomic_inc(&n->refcnt);
	} else {
		n = __neigh_lookup_errno(mn->tbl, mn->primary_key, dev);
		if (IS_ERR(n))
			return PTR_ERR(n);
	}
	if (neigh_event_send(n, skb_res) == 0) {
		int err;

		read_lock(&n->lock);
		err = dev_hard_header(skb, dev, ntohs(skb->protocol),
				      n->ha, NULL, skb->len);
		read_unlock(&n->lock);

		if (err < 0) {
			neigh_release(n);
			return -EINVAL;
		}
		teql_neigh_release(xchg(&q->ncache, n));
		return 0;
	}
	neigh_release(n);
	return (skb_res == NULL) ? -EAGAIN : 1;
}