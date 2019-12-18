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
typedef  scalar_t__ u16 ;
struct sk_buff {int /*<<< orphan*/  protocol; struct net_device* dev; } ;
struct TYPE_2__ {scalar_t__ napi; } ;
struct s2io_nic {TYPE_1__ config; scalar_t__ vlgrp; scalar_t__ vlan_strip_flag; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 struct s2io_nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  vlan_hwaccel_receive_skb (struct sk_buff*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vlan_hwaccel_rx (struct sk_buff*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void queue_rx_frame(struct sk_buff *skb, u16 vlan_tag)
{
	struct net_device *dev = skb->dev;
	struct s2io_nic *sp = netdev_priv(dev);

	skb->protocol = eth_type_trans(skb, dev);
	if (sp->vlgrp && vlan_tag && (sp->vlan_strip_flag)) {
		/* Queueing the vlan frame to the upper layer */
		if (sp->config.napi)
			vlan_hwaccel_receive_skb(skb, sp->vlgrp, vlan_tag);
		else
			vlan_hwaccel_rx(skb, sp->vlgrp, vlan_tag);
	} else {
		if (sp->config.napi)
			netif_receive_skb(skb);
		else
			netif_rx(skb);
	}
}