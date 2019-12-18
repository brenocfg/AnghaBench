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
struct udphdr {int /*<<< orphan*/  source; int /*<<< orphan*/  dest; } ;
struct udp_table {struct udp_hslot* hash; } ;
struct udp_hslot {int /*<<< orphan*/  lock; int /*<<< orphan*/  head; } ;
struct sock {int dummy; } ;
struct sk_buff {TYPE_1__* dev; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 struct sock* sk_nulls_head (int /*<<< orphan*/ *) ; 
 struct sock* sk_nulls_next (struct sock*) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 size_t udp_hashfn (struct net*,int /*<<< orphan*/ ) ; 
 int udp_queue_rcv_skb (struct sock*,struct sk_buff*) ; 
 struct sock* udp_v4_mcast_next (struct net*,struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __udp4_lib_mcast_deliver(struct net *net, struct sk_buff *skb,
				    struct udphdr  *uh,
				    __be32 saddr, __be32 daddr,
				    struct udp_table *udptable)
{
	struct sock *sk;
	struct udp_hslot *hslot = &udptable->hash[udp_hashfn(net, ntohs(uh->dest))];
	int dif;

	spin_lock(&hslot->lock);
	sk = sk_nulls_head(&hslot->head);
	dif = skb->dev->ifindex;
	sk = udp_v4_mcast_next(net, sk, uh->dest, daddr, uh->source, saddr, dif);
	if (sk) {
		struct sock *sknext = NULL;

		do {
			struct sk_buff *skb1 = skb;

			sknext = udp_v4_mcast_next(net, sk_nulls_next(sk), uh->dest,
						   daddr, uh->source, saddr,
						   dif);
			if (sknext)
				skb1 = skb_clone(skb, GFP_ATOMIC);

			if (skb1) {
				int ret = udp_queue_rcv_skb(sk, skb1);
				if (ret > 0)
					/* we should probably re-process instead
					 * of dropping packets here. */
					kfree_skb(skb1);
			}
			sk = sknext;
		} while (sknext);
	} else
		consume_skb(skb);
	spin_unlock(&hslot->lock);
	return 0;
}