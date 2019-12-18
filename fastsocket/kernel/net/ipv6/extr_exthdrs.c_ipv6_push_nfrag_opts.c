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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct ipv6_txoptions {scalar_t__ hopopt; scalar_t__ dst0opt; scalar_t__ srcrt; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NEXTHDR_DEST ; 
 int /*<<< orphan*/  NEXTHDR_HOP ; 
 int /*<<< orphan*/  ipv6_push_exthdr (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ipv6_push_rthdr (struct sk_buff*,int /*<<< orphan*/ *,scalar_t__,struct in6_addr**) ; 

void ipv6_push_nfrag_opts(struct sk_buff *skb, struct ipv6_txoptions *opt,
			  u8 *proto,
			  struct in6_addr **daddr)
{
	if (opt->srcrt) {
		ipv6_push_rthdr(skb, proto, opt->srcrt, daddr);
		/*
		 * IPV6_RTHDRDSTOPTS is ignored
		 * unless IPV6_RTHDR is set (RFC3542).
		 */
		if (opt->dst0opt)
			ipv6_push_exthdr(skb, proto, NEXTHDR_DEST, opt->dst0opt);
	}
	if (opt->hopopt)
		ipv6_push_exthdr(skb, proto, NEXTHDR_HOP, opt->hopopt);
}