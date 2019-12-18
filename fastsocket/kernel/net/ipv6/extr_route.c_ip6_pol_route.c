#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  __use; int /*<<< orphan*/  lastuse; } ;
struct TYPE_8__ {TYPE_4__ dst; } ;
struct rt6_info {int rt6i_flags; TYPE_3__ u; int /*<<< orphan*/  rt6i_nexthop; } ;
struct TYPE_7__ {struct rt6_info* ip6_null_entry; TYPE_1__* devconf_all; } ;
struct net {TYPE_2__ ipv6; } ;
struct flowi {int /*<<< orphan*/  fl6_dst; int /*<<< orphan*/  fl6_src; } ;
struct fib6_table {int /*<<< orphan*/  tb6_lock; int /*<<< orphan*/  tb6_root; } ;
struct fib6_node {int dummy; } ;
struct TYPE_6__ {scalar_t__ forwarding; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKTRACK (struct net*,int /*<<< orphan*/ *) ; 
 int RT6_LOOKUP_F_IFACE ; 
 int RT6_LOOKUP_F_REACHABLE ; 
 int RTF_CACHE ; 
 int RTF_LOCAL ; 
 int RTF_NONEXTHOP ; 
 int /*<<< orphan*/  dst_hold (TYPE_4__*) ; 
 int /*<<< orphan*/  dst_release (TYPE_4__*) ; 
 struct fib6_node* fib6_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ip6_ins_rt (struct rt6_info*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 struct rt6_info* rt6_alloc_clone (struct rt6_info*,int /*<<< orphan*/ *) ; 
 struct rt6_info* rt6_alloc_cow (struct rt6_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct rt6_info* rt6_select (struct fib6_node*,int,int) ; 

__attribute__((used)) static struct rt6_info *ip6_pol_route(struct net *net, struct fib6_table *table, int oif,
				      struct flowi *fl, int flags, bool input)
{
	struct fib6_node *fn;
	struct rt6_info *rt, *nrt;
	int strict = 0;
	int attempts = 3;
	int err;
	int reachable = net->ipv6.devconf_all->forwarding ? 0 : RT6_LOOKUP_F_REACHABLE;
	int local = RTF_NONEXTHOP;

	strict |= flags & RT6_LOOKUP_F_IFACE;
	if (input)
		local |= RTF_LOCAL;

relookup:
	read_lock_bh(&table->tb6_lock);

restart_2:
	fn = fib6_lookup(&table->tb6_root, &fl->fl6_dst, &fl->fl6_src);

restart:
	rt = rt6_select(fn, oif, strict | reachable);

	BACKTRACK(net, &fl->fl6_src);
	if (rt == net->ipv6.ip6_null_entry ||
	    rt->rt6i_flags & RTF_CACHE)
		goto out;

	dst_hold(&rt->u.dst);
	read_unlock_bh(&table->tb6_lock);

	if (!rt->rt6i_nexthop &&
	    !(rt->rt6i_flags & local))
		nrt = rt6_alloc_cow(rt, &fl->fl6_dst, &fl->fl6_src);
	else {
#if CLONE_OFFLINK_ROUTE
		nrt = rt6_alloc_clone(rt, &fl->fl6_dst);
#else
		goto out2;
#endif
	}

	dst_release(&rt->u.dst);
	rt = nrt ? : net->ipv6.ip6_null_entry;

	dst_hold(&rt->u.dst);
	if (nrt) {
		err = ip6_ins_rt(nrt);
		if (!err)
			goto out2;
	}

	if (--attempts <= 0)
		goto out2;

	/*
	 * Race condition! In the gap, when table->tb6_lock was
	 * released someone could insert this route.  Relookup.
	 */
	dst_release(&rt->u.dst);
	goto relookup;

out:
	if (reachable) {
		reachable = 0;
		goto restart_2;
	}
	dst_hold(&rt->u.dst);
	read_unlock_bh(&table->tb6_lock);
out2:
	rt->u.dst.lastuse = jiffies;
	rt->u.dst.__use++;

	return rt;
}