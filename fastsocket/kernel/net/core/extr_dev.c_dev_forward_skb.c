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
struct TYPE_2__ {scalar_t__ tv64; } ;
struct sk_buff {scalar_t__ mark; int /*<<< orphan*/  protocol; int /*<<< orphan*/  pkt_type; TYPE_1__ tstamp; scalar_t__ iif; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int NET_RX_DROP ; 
 int /*<<< orphan*/  PACKET_HOST ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  is_skb_forwardable (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_reset (struct sk_buff*) ; 
 int /*<<< orphan*/  secpath_reset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

int dev_forward_skb(struct net_device *dev, struct sk_buff *skb)
{
	skb_orphan(skb);
	nf_reset(skb);

	if (unlikely(!is_skb_forwardable(dev, skb))) {
		kfree_skb(skb);
		return NET_RX_DROP;
	}
	skb->iif = 0;
	skb_dst_drop(skb);
	skb->tstamp.tv64 = 0;
	skb->pkt_type = PACKET_HOST;
	skb->protocol = eth_type_trans(skb, dev);
	skb->mark = 0;
	secpath_reset(skb);
	nf_reset(skb);
	return netif_rx(skb);
}