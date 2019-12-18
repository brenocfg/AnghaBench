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
struct TYPE_8__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  rt_next; } ;
struct TYPE_6__ {TYPE_4__ dst; } ;
struct TYPE_5__ {scalar_t__ fl4_dst; scalar_t__ fl4_src; scalar_t__ iif; scalar_t__ oif; scalar_t__ mark; int fl4_tos; } ;
struct rtable {TYPE_2__ u; TYPE_1__ fl; } ;
struct net {int dummy; } ;
struct flowi {scalar_t__ fl4_dst; scalar_t__ fl4_src; scalar_t__ oif; scalar_t__ mark; int fl4_tos; } ;
struct TYPE_7__ {int /*<<< orphan*/  chain; } ;

/* Variables and functions */
 int IPTOS_RT_MASK ; 
 int RTO_ONLINK ; 
 int /*<<< orphan*/  RT_CACHE_STAT_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_use (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int ip_route_output_slow (struct net*,struct rtable**,struct flowi const*) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ net_eq (int /*<<< orphan*/ ,struct net*) ; 
 int /*<<< orphan*/  out_hit ; 
 int /*<<< orphan*/  out_hlist_search ; 
 struct rtable* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock_bh () ; 
 int /*<<< orphan*/  rcu_read_unlock_bh () ; 
 int /*<<< orphan*/  rt_caching (struct net*) ; 
 int /*<<< orphan*/  rt_genid (struct net*) ; 
 unsigned int rt_hash (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_3__* rt_hash_table ; 
 int /*<<< orphan*/  rt_is_expired (struct rtable*) ; 

int __ip_route_output_key(struct net *net, struct rtable **rp,
			  const struct flowi *flp)
{
	unsigned hash;
	struct rtable *rth;

	if (!rt_caching(net))
		goto slow_output;

	hash = rt_hash(flp->fl4_dst, flp->fl4_src, flp->oif, rt_genid(net));

	rcu_read_lock_bh();
	for (rth = rcu_dereference(rt_hash_table[hash].chain); rth;
		rth = rcu_dereference(rth->u.dst.rt_next)) {
		if (rth->fl.fl4_dst == flp->fl4_dst &&
		    rth->fl.fl4_src == flp->fl4_src &&
		    rth->fl.iif == 0 &&
		    rth->fl.oif == flp->oif &&
		    rth->fl.mark == flp->mark &&
		    !((rth->fl.fl4_tos ^ flp->fl4_tos) &
			    (IPTOS_RT_MASK | RTO_ONLINK)) &&
		    net_eq(dev_net(rth->u.dst.dev), net) &&
		    !rt_is_expired(rth)) {
			dst_use(&rth->u.dst, jiffies);
			RT_CACHE_STAT_INC(out_hit);
			rcu_read_unlock_bh();
			*rp = rth;
			return 0;
		}
		RT_CACHE_STAT_INC(out_hlist_search);
	}
	rcu_read_unlock_bh();

slow_output:
	return ip_route_output_slow(net, rp, flp);
}