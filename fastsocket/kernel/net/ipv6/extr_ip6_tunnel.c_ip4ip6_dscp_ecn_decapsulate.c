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
struct sk_buff {int dummy; } ;
struct ipv6hdr {int dummy; } ;
struct TYPE_2__ {int flags; } ;
struct ip6_tnl {TYPE_1__ parms; } ;
typedef  int __u8 ;

/* Variables and functions */
 int INET_ECN_MASK ; 
 scalar_t__ INET_ECN_is_ce (int) ; 
 int IP6_TNL_F_RCV_DSCP_COPY ; 
 int /*<<< orphan*/  IP_ECN_set_ce (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv4_change_dsfield (int /*<<< orphan*/ ,int,int) ; 
 int ipv6_get_dsfield (struct ipv6hdr*) ; 

__attribute__((used)) static void ip4ip6_dscp_ecn_decapsulate(struct ip6_tnl *t,
					struct ipv6hdr *ipv6h,
					struct sk_buff *skb)
{
	__u8 dsfield = ipv6_get_dsfield(ipv6h) & ~INET_ECN_MASK;

	if (t->parms.flags & IP6_TNL_F_RCV_DSCP_COPY)
		ipv4_change_dsfield(ip_hdr(skb), INET_ECN_MASK, dsfield);

	if (INET_ECN_is_ce(dsfield))
		IP_ECN_set_ce(ip_hdr(skb));
}