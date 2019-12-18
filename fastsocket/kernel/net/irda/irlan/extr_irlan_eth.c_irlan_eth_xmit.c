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
struct sk_buff {scalar_t__ len; } ;
struct net_device {int /*<<< orphan*/  trans_start; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_dropped; } ;
struct irlan_cb {scalar_t__ max_header_size; TYPE_1__ stats; int /*<<< orphan*/  tsap_data; scalar_t__ use_udata; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int irttp_data_request (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int irttp_udata_request (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  jiffies ; 
 struct irlan_cb* netdev_priv (struct net_device*) ; 
 scalar_t__ skb_headroom (struct sk_buff*) ; 
 struct sk_buff* skb_realloc_headroom (struct sk_buff*,scalar_t__) ; 
 scalar_t__ skb_shared (struct sk_buff*) ; 

__attribute__((used)) static netdev_tx_t irlan_eth_xmit(struct sk_buff *skb,
					struct net_device *dev)
{
	struct irlan_cb *self = netdev_priv(dev);
	int ret;

	/* skb headroom large enough to contain all IrDA-headers? */
	if ((skb_headroom(skb) < self->max_header_size) || (skb_shared(skb))) {
		struct sk_buff *new_skb =
			skb_realloc_headroom(skb, self->max_header_size);

		/*  We have to free the original skb anyway */
		dev_kfree_skb(skb);

		/* Did the realloc succeed? */
		if (new_skb == NULL)
			return NETDEV_TX_OK;

		/* Use the new skb instead */
		skb = new_skb;
	}

	dev->trans_start = jiffies;

	/* Now queue the packet in the transport layer */
	if (self->use_udata)
		ret = irttp_udata_request(self->tsap_data, skb);
	else
		ret = irttp_data_request(self->tsap_data, skb);

	if (ret < 0) {
		/*
		 * IrTTPs tx queue is full, so we just have to
		 * drop the frame! You might think that we should
		 * just return -1 and don't deallocate the frame,
		 * but that is dangerous since it's possible that
		 * we have replaced the original skb with a new
		 * one with larger headroom, and that would really
		 * confuse do_dev_queue_xmit() in dev.c! I have
		 * tried :-) DB
		 */
		/* irttp_data_request already free the packet */
		self->stats.tx_dropped++;
	} else {
		self->stats.tx_packets++;
		self->stats.tx_bytes += skb->len;
	}

	return NETDEV_TX_OK;
}