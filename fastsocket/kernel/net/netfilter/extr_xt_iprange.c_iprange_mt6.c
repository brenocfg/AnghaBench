#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct xt_match_param {struct xt_iprange_mtinfo* matchinfo; } ;
struct TYPE_8__ {int /*<<< orphan*/  in6; } ;
struct TYPE_7__ {int /*<<< orphan*/  in6; } ;
struct TYPE_6__ {int /*<<< orphan*/  in6; } ;
struct TYPE_5__ {int /*<<< orphan*/  in6; } ;
struct xt_iprange_mtinfo {int flags; TYPE_4__ dst_max; TYPE_3__ dst_min; TYPE_2__ src_max; TYPE_1__ src_min; } ;
struct sk_buff {int dummy; } ;
struct ipv6hdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 int IPRANGE_DST ; 
 int IPRANGE_DST_INV ; 
 int IPRANGE_SRC ; 
 int IPRANGE_SRC_INV ; 
 scalar_t__ iprange_ipv6_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff const*) ; 

__attribute__((used)) static bool
iprange_mt6(const struct sk_buff *skb, const struct xt_match_param *par)
{
	const struct xt_iprange_mtinfo *info = par->matchinfo;
	const struct ipv6hdr *iph = ipv6_hdr(skb);
	bool m;

	if (info->flags & IPRANGE_SRC) {
		m  = iprange_ipv6_sub(&iph->saddr, &info->src_min.in6) < 0;
		m |= iprange_ipv6_sub(&iph->saddr, &info->src_max.in6) > 0;
		m ^= !!(info->flags & IPRANGE_SRC_INV);
		if (m)
			return false;
	}
	if (info->flags & IPRANGE_DST) {
		m  = iprange_ipv6_sub(&iph->daddr, &info->dst_min.in6) < 0;
		m |= iprange_ipv6_sub(&iph->daddr, &info->dst_max.in6) > 0;
		m ^= !!(info->flags & IPRANGE_DST_INV);
		if (m)
			return false;
	}
	return true;
}