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
struct sk_buff {int /*<<< orphan*/  protocol; scalar_t__ data; } ;
struct rxfcb {int flags; int /*<<< orphan*/  vlctl; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  kernel_dropped; } ;
struct gfar_private {TYPE_1__ extra_stats; scalar_t__ vlgrp; scalar_t__ rx_csum_enable; } ;

/* Variables and functions */
 int NET_RX_DROP ; 
 int RXFCB_VLN ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  gfar_rx_checksum (struct sk_buff*,struct rxfcb*) ; 
 struct gfar_private* netdev_priv (struct net_device*) ; 
 int netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 
 int vlan_hwaccel_receive_skb (struct sk_buff*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gfar_process_frame(struct net_device *dev, struct sk_buff *skb,
			      int amount_pull)
{
	struct gfar_private *priv = netdev_priv(dev);
	struct rxfcb *fcb = NULL;

	int ret;

	/* fcb is at the beginning if exists */
	fcb = (struct rxfcb *)skb->data;

	/* Remove the FCB from the skb */
	/* Remove the padded bytes, if there are any */
	if (amount_pull)
		skb_pull(skb, amount_pull);

	if (priv->rx_csum_enable)
		gfar_rx_checksum(skb, fcb);

	/* Tell the skb what kind of packet this is */
	skb->protocol = eth_type_trans(skb, dev);

	/* Send the packet up the stack */
	if (unlikely(priv->vlgrp && (fcb->flags & RXFCB_VLN)))
		ret = vlan_hwaccel_receive_skb(skb, priv->vlgrp, fcb->vlctl);
	else
		ret = netif_receive_skb(skb);

	if (NET_RX_DROP == ret)
		priv->extra_stats.kernel_dropped++;

	return 0;
}