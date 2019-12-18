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

/* Variables and functions */
 scalar_t__ INET_ECN_is_ce (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IP6_ECN_set_ce (int /*<<< orphan*/ ) ; 
 int IP6_TNL_F_RCV_DSCP_COPY ; 
 int /*<<< orphan*/  ipv6_copy_dscp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv6_get_dsfield (struct ipv6hdr*) ; 
 int /*<<< orphan*/  ipv6_hdr (struct sk_buff*) ; 

__attribute__((used)) static void ip6ip6_dscp_ecn_decapsulate(struct ip6_tnl *t,
					struct ipv6hdr *ipv6h,
					struct sk_buff *skb)
{
	if (t->parms.flags & IP6_TNL_F_RCV_DSCP_COPY)
		ipv6_copy_dscp(ipv6_get_dsfield(ipv6h), ipv6_hdr(skb));

	if (INET_ECN_is_ce(ipv6_get_dsfield(ipv6h)))
		IP6_ECN_set_ce(ipv6_hdr(skb));
}