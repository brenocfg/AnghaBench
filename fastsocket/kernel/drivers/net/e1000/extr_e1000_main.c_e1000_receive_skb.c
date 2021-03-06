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
typedef  int u8 ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct e1000_adapter {int /*<<< orphan*/  napi; scalar_t__ vlgrp; int /*<<< orphan*/  netdev; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int E1000_RXD_SPC_VLAN_MASK ; 
 int E1000_RXD_STAT_VP ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlan_gro_receive (int /*<<< orphan*/ *,scalar_t__,int,struct sk_buff*) ; 

__attribute__((used)) static void e1000_receive_skb(struct e1000_adapter *adapter, u8 status,
			      __le16 vlan, struct sk_buff *skb)
{
	skb->protocol = eth_type_trans(skb, adapter->netdev);

	if ((unlikely(adapter->vlgrp && (status & E1000_RXD_STAT_VP))))
		vlan_gro_receive(&adapter->napi, adapter->vlgrp,
				 le16_to_cpu(vlan) & E1000_RXD_SPC_VLAN_MASK,
				 skb);
	else
		napi_gro_receive(&adapter->napi, skb);
}