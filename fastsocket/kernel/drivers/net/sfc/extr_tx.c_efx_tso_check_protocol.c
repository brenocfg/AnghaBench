#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vlan_ethhdr {scalar_t__ h_vlan_encapsulated_proto; } ;
struct sk_buff {scalar_t__ protocol; scalar_t__ data; } ;
struct ethhdr {scalar_t__ h_proto; } ;
typedef  scalar_t__ __be16 ;
struct TYPE_7__ {scalar_t__ protocol; } ;
struct TYPE_6__ {scalar_t__ nexthdr; } ;
struct TYPE_5__ {unsigned int doff; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_BUG_ON_PARANOID (int) ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ NEXTHDR_TCP ; 
 scalar_t__ PTR_DIFF (TYPE_1__*,scalar_t__) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 TYPE_3__* ip_hdr (struct sk_buff*) ; 
 TYPE_2__* ipv6_hdr (struct sk_buff*) ; 
 scalar_t__ skb_headlen (struct sk_buff*) ; 
 TYPE_1__* tcp_hdr (struct sk_buff*) ; 

__attribute__((used)) static __be16 efx_tso_check_protocol(struct sk_buff *skb)
{
	__be16 protocol = skb->protocol;

	EFX_BUG_ON_PARANOID(((struct ethhdr *)skb->data)->h_proto !=
			    protocol);
	if (protocol == htons(ETH_P_8021Q)) {
		struct vlan_ethhdr *veh = (struct vlan_ethhdr *)skb->data;
		protocol = veh->h_vlan_encapsulated_proto;
	}

	if (protocol == htons(ETH_P_IP)) {
		EFX_BUG_ON_PARANOID(ip_hdr(skb)->protocol != IPPROTO_TCP);
	} else {
		EFX_BUG_ON_PARANOID(protocol != htons(ETH_P_IPV6));
		EFX_BUG_ON_PARANOID(ipv6_hdr(skb)->nexthdr != NEXTHDR_TCP);
	}
	EFX_BUG_ON_PARANOID((PTR_DIFF(tcp_hdr(skb), skb->data)
			     + (tcp_hdr(skb)->doff << 2u)) >
			    skb_headlen(skb));

	return protocol;
}