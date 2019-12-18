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
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  protocol; } ;
struct cp_private {int /*<<< orphan*/  vlgrp; TYPE_2__* dev; } ;
struct cp_desc {int opts2; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  RxVlanTagged ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,TYPE_2__*) ; 
 int le32_to_cpu (int) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  swab16 (int) ; 
 int /*<<< orphan*/  vlan_hwaccel_receive_skb (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cp_rx_skb (struct cp_private *cp, struct sk_buff *skb,
			      struct cp_desc *desc)
{
	skb->protocol = eth_type_trans (skb, cp->dev);

	cp->dev->stats.rx_packets++;
	cp->dev->stats.rx_bytes += skb->len;

#if CP_VLAN_TAG_USED
	if (cp->vlgrp && (desc->opts2 & cpu_to_le32(RxVlanTagged))) {
		vlan_hwaccel_receive_skb(skb, cp->vlgrp,
					 swab16(le32_to_cpu(desc->opts2) & 0xffff));
	} else
#endif
		netif_receive_skb(skb);
}