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
typedef  scalar_t__ u_int8_t ;
struct xt_pkttype_info {scalar_t__ pkttype; int invert; } ;
struct xt_match_param {scalar_t__ family; struct xt_pkttype_info* matchinfo; } ;
struct sk_buff {scalar_t__ pkt_type; } ;
struct TYPE_6__ {int /*<<< orphan*/  daddr; } ;
struct TYPE_4__ {int* s6_addr; } ;
struct TYPE_5__ {TYPE_1__ daddr; } ;

/* Variables and functions */
 scalar_t__ NFPROTO_IPV4 ; 
 scalar_t__ NFPROTO_IPV6 ; 
 scalar_t__ PACKET_BROADCAST ; 
 scalar_t__ PACKET_LOOPBACK ; 
 scalar_t__ PACKET_MULTICAST ; 
 TYPE_3__* ip_hdr (struct sk_buff const*) ; 
 scalar_t__ ipv4_is_multicast (int /*<<< orphan*/ ) ; 
 TYPE_2__* ipv6_hdr (struct sk_buff const*) ; 

__attribute__((used)) static bool
pkttype_mt(const struct sk_buff *skb, const struct xt_match_param *par)
{
	const struct xt_pkttype_info *info = par->matchinfo;
	u_int8_t type;

	if (skb->pkt_type != PACKET_LOOPBACK)
		type = skb->pkt_type;
	else if (par->family == NFPROTO_IPV4 &&
	    ipv4_is_multicast(ip_hdr(skb)->daddr))
		type = PACKET_MULTICAST;
	else if (par->family == NFPROTO_IPV6 &&
	    ipv6_hdr(skb)->daddr.s6_addr[0] == 0xFF)
		type = PACKET_MULTICAST;
	else
		type = PACKET_BROADCAST;

	return (type == info->pkttype) ^ info->invert;
}