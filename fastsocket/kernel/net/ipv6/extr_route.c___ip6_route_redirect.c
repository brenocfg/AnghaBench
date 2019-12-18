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
struct TYPE_8__ {struct rt6_info* rt6_next; } ;
struct TYPE_7__ {TYPE_4__ dst; } ;
struct rt6_info {int rt6i_flags; TYPE_3__ u; int /*<<< orphan*/  rt6i_gateway; TYPE_1__* rt6i_dev; } ;
struct TYPE_6__ {struct rt6_info* ip6_null_entry; } ;
struct net {TYPE_2__ ipv6; } ;
struct ip6rd_flowi {int /*<<< orphan*/  gateway; } ;
struct flowi {scalar_t__ oif; int /*<<< orphan*/  fl6_src; int /*<<< orphan*/  fl6_dst; } ;
struct fib6_table {int /*<<< orphan*/  tb6_lock; int /*<<< orphan*/  tb6_root; } ;
struct fib6_node {struct rt6_info* leaf; } ;
struct TYPE_5__ {scalar_t__ ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKTRACK (struct net*,int /*<<< orphan*/ *) ; 
 int RTF_GATEWAY ; 
 int /*<<< orphan*/  dst_hold (TYPE_4__*) ; 
 struct fib6_node* fib6_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipv6_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ rt6_check_expired (struct rt6_info*) ; 

__attribute__((used)) static struct rt6_info *__ip6_route_redirect(struct net *net,
					     struct fib6_table *table,
					     struct flowi *fl,
					     int flags)
{
	struct ip6rd_flowi *rdfl = (struct ip6rd_flowi *)fl;
	struct rt6_info *rt;
	struct fib6_node *fn;

	/*
	 * Get the "current" route for this destination and
	 * check if the redirect has come from approriate router.
	 *
	 * RFC 2461 specifies that redirects should only be
	 * accepted if they come from the nexthop to the target.
	 * Due to the way the routes are chosen, this notion
	 * is a bit fuzzy and one might need to check all possible
	 * routes.
	 */

	read_lock_bh(&table->tb6_lock);
	fn = fib6_lookup(&table->tb6_root, &fl->fl6_dst, &fl->fl6_src);
restart:
	for (rt = fn->leaf; rt; rt = rt->u.dst.rt6_next) {
		/*
		 * Current route is on-link; redirect is always invalid.
		 *
		 * Seems, previous statement is not true. It could
		 * be node, which looks for us as on-link (f.e. proxy ndisc)
		 * But then router serving it might decide, that we should
		 * know truth 8)8) --ANK (980726).
		 */
		if (rt6_check_expired(rt))
			continue;
		if (!(rt->rt6i_flags & RTF_GATEWAY))
			continue;
		if (fl->oif != rt->rt6i_dev->ifindex)
			continue;
		if (!ipv6_addr_equal(&rdfl->gateway, &rt->rt6i_gateway))
			continue;
		break;
	}

	if (!rt)
		rt = net->ipv6.ip6_null_entry;
	BACKTRACK(net, &fl->fl6_src);
out:
	dst_hold(&rt->u.dst);

	read_unlock_bh(&table->tb6_lock);

	return rt;
}