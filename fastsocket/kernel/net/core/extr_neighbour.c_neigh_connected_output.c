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
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  protocol; } ;
struct net_device {int dummy; } ;
struct neighbour {TYPE_1__* ops; int /*<<< orphan*/  lock; int /*<<< orphan*/  ha; struct net_device* dev; } ;
struct dst_entry {struct neighbour* neighbour; } ;
struct TYPE_2__ {int (* queue_xmit ) (struct sk_buff*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int dev_hard_header (struct sk_buff*,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_network_offset (struct sk_buff*) ; 
 int stub1 (struct sk_buff*) ; 

int neigh_connected_output(struct sk_buff *skb)
{
	int err;
	struct dst_entry *dst = skb_dst(skb);
	struct neighbour *neigh = dst->neighbour;
	struct net_device *dev = neigh->dev;

	__skb_pull(skb, skb_network_offset(skb));

	read_lock_bh(&neigh->lock);
	err = dev_hard_header(skb, dev, ntohs(skb->protocol),
			      neigh->ha, NULL, skb->len);
	read_unlock_bh(&neigh->lock);
	if (err >= 0)
		err = neigh->ops->queue_xmit(skb);
	else {
		err = -EINVAL;
		kfree_skb(skb);
	}
	return err;
}