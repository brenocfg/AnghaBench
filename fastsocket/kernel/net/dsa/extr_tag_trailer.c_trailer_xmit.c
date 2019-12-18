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
typedef  int u8 ;
struct sk_buff {int len; int /*<<< orphan*/  dev; int /*<<< orphan*/  protocol; scalar_t__ head; } ;
struct TYPE_4__ {int tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_1__ stats; } ;
struct dsa_slave_priv {int port; TYPE_3__* parent; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_6__ {TYPE_2__* dst; } ;
struct TYPE_5__ {int /*<<< orphan*/  master_netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_TRAILER ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 scalar_t__ NET_IP_ALIGN ; 
 struct sk_buff* alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_queue_xmit (struct sk_buff*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 struct dsa_slave_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  skb_copy_and_csum_dev (struct sk_buff*,int*) ; 
 scalar_t__ skb_network_header (struct sk_buff*) ; 
 int* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_network_header (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_set_transport_header (struct sk_buff*,scalar_t__) ; 
 scalar_t__ skb_transport_header (struct sk_buff*) ; 

netdev_tx_t trailer_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct dsa_slave_priv *p = netdev_priv(dev);
	struct sk_buff *nskb;
	int padlen;
	u8 *trailer;

	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->len;

	/*
	 * We have to make sure that the trailer ends up as the very
	 * last 4 bytes of the packet.  This means that we have to pad
	 * the packet to the minimum ethernet frame size, if necessary,
	 * before adding the trailer.
	 */
	padlen = 0;
	if (skb->len < 60)
		padlen = 60 - skb->len;

	nskb = alloc_skb(NET_IP_ALIGN + skb->len + padlen + 4, GFP_ATOMIC);
	if (nskb == NULL) {
		kfree_skb(skb);
		return NETDEV_TX_OK;
	}
	skb_reserve(nskb, NET_IP_ALIGN);

	skb_reset_mac_header(nskb);
	skb_set_network_header(nskb, skb_network_header(skb) - skb->head);
	skb_set_transport_header(nskb, skb_transport_header(skb) - skb->head);
	skb_copy_and_csum_dev(skb, skb_put(nskb, skb->len));
	kfree_skb(skb);

	if (padlen) {
		u8 *pad = skb_put(nskb, padlen);
		memset(pad, 0, padlen);
	}

	trailer = skb_put(nskb, 4);
	trailer[0] = 0x80;
	trailer[1] = 1 << p->port;
	trailer[2] = 0x10;
	trailer[3] = 0x00;

	nskb->protocol = htons(ETH_P_TRAILER);

	nskb->dev = p->parent->dst->master_netdev;
	dev_queue_xmit(nskb);

	return NETDEV_TX_OK;
}