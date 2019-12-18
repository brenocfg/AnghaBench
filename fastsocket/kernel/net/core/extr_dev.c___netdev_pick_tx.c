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
typedef  int u16 ;
struct sock {int /*<<< orphan*/  sk_dst_cache; } ;
struct sk_buff {scalar_t__ ooo_okay; struct sock* sk; } ;
struct net_device {int real_num_tx_queues; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 int get_xps_queue (struct net_device*,struct sk_buff*) ; 
 struct dst_entry* rcu_dereference_check (int /*<<< orphan*/ ,int) ; 
 int sk_tx_queue_get (struct sock*) ; 
 int /*<<< orphan*/  sk_tx_queue_set (struct sock*,int) ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 
 int skb_tx_hash (struct net_device*,struct sk_buff*) ; 

u16 __netdev_pick_tx(struct net_device *dev, struct sk_buff *skb)
{
	struct sock *sk = skb->sk;
	int queue_index = sk_tx_queue_get(sk);

	if (queue_index < 0 || skb->ooo_okay ||
	    queue_index >= dev->real_num_tx_queues) {
		int new_index = get_xps_queue(dev, skb);
		if (new_index < 0)
			new_index = skb_tx_hash(dev, skb);

		if (queue_index != new_index && sk) {
			struct dst_entry *dst =
				    rcu_dereference_check(sk->sk_dst_cache, 1);

			if (dst && skb_dst(skb) == dst)
				sk_tx_queue_set(sk, new_index);

		}

		queue_index = new_index;
	}

	return queue_index;
}