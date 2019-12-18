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
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct bnx2x_fastpath {int /*<<< orphan*/  napi; } ;
struct bnx2x {int /*<<< orphan*/  vlgrp; } ;
struct TYPE_2__ {scalar_t__ gso_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int) ; 
#define  ETH_P_IP 129 
#define  ETH_P_IPV6 128 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_gro_csum (struct bnx2x*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_gro_ip_csum ; 
 int /*<<< orphan*/  bnx2x_gro_ipv6_csum ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  vlan_gro_receive (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,struct sk_buff*) ; 

__attribute__((used)) static void bnx2x_gro_receive(struct bnx2x *bp, struct bnx2x_fastpath *fp,
			       struct sk_buff *skb, u16 vlan_tci)
{
#ifdef CONFIG_INET
	if (skb_shinfo(skb)->gso_size) {
		switch (be16_to_cpu(skb->protocol)) {
		case ETH_P_IP:
			bnx2x_gro_csum(bp, skb, bnx2x_gro_ip_csum);
			break;
		case ETH_P_IPV6:
			bnx2x_gro_csum(bp, skb, bnx2x_gro_ipv6_csum);
			break;
		default:
			BNX2X_ERR("Error: FW GRO supports only IPv4/IPv6, not 0x%04x\n",
				  be16_to_cpu(skb->protocol));
		}
	}
#endif
	/* RHEL: separate RX path for VLAN */
	if (vlan_tci)
		vlan_gro_receive(&fp->napi, bp->vlgrp, vlan_tci, skb);
	else
		napi_gro_receive(&fp->napi, skb);
}