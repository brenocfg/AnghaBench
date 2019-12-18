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
struct TYPE_7__ {int /*<<< orphan*/  dst; } ;
struct rt6_info {TYPE_3__ u; } ;
struct TYPE_5__ {struct rt6_info* ip6_null_entry; struct rt6_info* ip6_prohibit_entry; struct rt6_info* ip6_blk_hole_entry; } ;
struct net {TYPE_1__ ipv6; } ;
struct in6_addr {int dummy; } ;
struct flowi {int /*<<< orphan*/  fl6_src; int /*<<< orphan*/  fl6_dst; } ;
struct fib_rule {int action; int flags; int /*<<< orphan*/  table; struct net* fr_net; } ;
struct fib_lookup_arg {struct rt6_info* result; struct rt6_info* (* lookup_ptr ) (struct net*,struct fib6_table*,struct flowi*,int) ;} ;
struct fib6_table {int dummy; } ;
struct TYPE_6__ {scalar_t__ plen; int /*<<< orphan*/  addr; } ;
struct fib6_rule {TYPE_2__ src; } ;
typedef  struct rt6_info* (* pol_lookup_t ) (struct net*,struct fib6_table*,struct flowi*,int) ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int FIB_RULE_FIND_SADDR ; 
#define  FR_ACT_BLACKHOLE 131 
#define  FR_ACT_PROHIBIT 130 
#define  FR_ACT_TO_TBL 129 
#define  FR_ACT_UNREACHABLE 128 
 unsigned int IPV6_PREFER_SRC_COA ; 
 unsigned int IPV6_PREFER_SRC_PUBLIC ; 
 unsigned int IPV6_PREFER_SRC_TMP ; 
 int RT6_LOOKUP_F_HAS_SADDR ; 
 int RT6_LOOKUP_F_SRCPREF_COA ; 
 int RT6_LOOKUP_F_SRCPREF_PUBLIC ; 
 int RT6_LOOKUP_F_SRCPREF_TMP ; 
 int /*<<< orphan*/  dst_hold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dst_release (int /*<<< orphan*/ *) ; 
 struct fib6_table* fib6_get_table (struct net*,int /*<<< orphan*/ ) ; 
 TYPE_4__* ip6_dst_idev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipv6_addr_copy (int /*<<< orphan*/ *,struct in6_addr*) ; 
 scalar_t__ ipv6_dev_get_saddr (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,struct in6_addr*) ; 
 int /*<<< orphan*/  ipv6_prefix_equal (struct in6_addr*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int fib6_rule_action(struct fib_rule *rule, struct flowi *flp,
			    int flags, struct fib_lookup_arg *arg)
{
	struct rt6_info *rt = NULL;
	struct fib6_table *table;
	struct net *net = rule->fr_net;
	pol_lookup_t lookup = arg->lookup_ptr;

	switch (rule->action) {
	case FR_ACT_TO_TBL:
		break;
	case FR_ACT_UNREACHABLE:
		rt = net->ipv6.ip6_null_entry;
		goto discard_pkt;
	default:
	case FR_ACT_BLACKHOLE:
		rt = net->ipv6.ip6_blk_hole_entry;
		goto discard_pkt;
	case FR_ACT_PROHIBIT:
		rt = net->ipv6.ip6_prohibit_entry;
		goto discard_pkt;
	}

	table = fib6_get_table(net, rule->table);
	if (table)
		rt = lookup(net, table, flp, flags);

	if (rt != net->ipv6.ip6_null_entry) {
		struct fib6_rule *r = (struct fib6_rule *)rule;

		/*
		 * If we need to find a source address for this traffic,
		 * we check the result if it meets requirement of the rule.
		 */
		if ((rule->flags & FIB_RULE_FIND_SADDR) &&
		    r->src.plen && !(flags & RT6_LOOKUP_F_HAS_SADDR)) {
			struct in6_addr saddr;
			unsigned int srcprefs = 0;

			if (flags & RT6_LOOKUP_F_SRCPREF_TMP)
				srcprefs |= IPV6_PREFER_SRC_TMP;
			if (flags & RT6_LOOKUP_F_SRCPREF_PUBLIC)
				srcprefs |= IPV6_PREFER_SRC_PUBLIC;
			if (flags & RT6_LOOKUP_F_SRCPREF_COA)
				srcprefs |= IPV6_PREFER_SRC_COA;

			if (ipv6_dev_get_saddr(net,
					       ip6_dst_idev(&rt->u.dst)->dev,
					       &flp->fl6_dst, srcprefs,
					       &saddr))
				goto again;
			if (!ipv6_prefix_equal(&saddr, &r->src.addr,
					       r->src.plen))
				goto again;
			ipv6_addr_copy(&flp->fl6_src, &saddr);
		}
		goto out;
	}
again:
	dst_release(&rt->u.dst);
	rt = NULL;
	goto out;

discard_pkt:
	dst_hold(&rt->u.dst);
out:
	arg->result = rt;
	return rt == NULL ? -EAGAIN : 0;
}