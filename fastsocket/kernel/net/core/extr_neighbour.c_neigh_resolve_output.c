#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  protocol; } ;
struct net_device {TYPE_1__* header_ops; } ;
struct neighbour {TYPE_3__* ops; int /*<<< orphan*/  lock; int /*<<< orphan*/  ha; struct net_device* dev; } ;
struct dst_entry {struct neighbour* neighbour; TYPE_2__* ops; int /*<<< orphan*/  hh; } ;
struct TYPE_6__ {int (* queue_xmit ) (struct sk_buff*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  protocol; } ;
struct TYPE_4__ {scalar_t__ cache; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NEIGH_PRINTK1 (char*,struct dst_entry*,struct neighbour*) ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int dev_hard_header (struct sk_buff*,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  neigh_event_send (struct neighbour*,struct sk_buff*) ; 
 int /*<<< orphan*/  neigh_hh_init (struct neighbour*,struct dst_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_network_offset (struct sk_buff*) ; 
 int stub1 (struct sk_buff*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

int neigh_resolve_output(struct sk_buff *skb)
{
	struct dst_entry *dst = skb_dst(skb);
	struct neighbour *neigh;
	int rc = 0;

	if (!dst || !(neigh = dst->neighbour))
		goto discard;

	__skb_pull(skb, skb_network_offset(skb));

	if (!neigh_event_send(neigh, skb)) {
		int err;
		struct net_device *dev = neigh->dev;
		if (dev->header_ops->cache && !dst->hh) {
			write_lock_bh(&neigh->lock);
			if (!dst->hh)
				neigh_hh_init(neigh, dst, dst->ops->protocol);
			err = dev_hard_header(skb, dev, ntohs(skb->protocol),
					      neigh->ha, NULL, skb->len);
			write_unlock_bh(&neigh->lock);
		} else {
			read_lock_bh(&neigh->lock);
			err = dev_hard_header(skb, dev, ntohs(skb->protocol),
					      neigh->ha, NULL, skb->len);
			read_unlock_bh(&neigh->lock);
		}
		if (err >= 0)
			rc = neigh->ops->queue_xmit(skb);
		else
			goto out_kfree_skb;
	}
out:
	return rc;
discard:
	NEIGH_PRINTK1("neigh_resolve_output: dst=%p neigh=%p\n",
		      dst, dst ? dst->neighbour : NULL);
out_kfree_skb:
	rc = -EINVAL;
	kfree_skb(skb);
	goto out;
}