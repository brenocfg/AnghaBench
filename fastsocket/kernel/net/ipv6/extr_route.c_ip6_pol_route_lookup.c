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
struct TYPE_2__ {int /*<<< orphan*/  dst; } ;
struct rt6_info {TYPE_1__ u; } ;
struct net {int dummy; } ;
struct flowi {int /*<<< orphan*/  fl6_src; int /*<<< orphan*/  oif; int /*<<< orphan*/  fl6_dst; } ;
struct fib6_table {int /*<<< orphan*/  tb6_lock; int /*<<< orphan*/  tb6_root; } ;
struct fib6_node {struct rt6_info* leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKTRACK (struct net*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dst_use (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct fib6_node* fib6_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 struct rt6_info* rt6_device_match (struct net*,struct rt6_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct rt6_info *ip6_pol_route_lookup(struct net *net,
					     struct fib6_table *table,
					     struct flowi *fl, int flags)
{
	struct fib6_node *fn;
	struct rt6_info *rt;

	read_lock_bh(&table->tb6_lock);
	fn = fib6_lookup(&table->tb6_root, &fl->fl6_dst, &fl->fl6_src);
restart:
	rt = fn->leaf;
	rt = rt6_device_match(net, rt, &fl->fl6_src, fl->oif, flags);
	BACKTRACK(net, &fl->fl6_src);
out:
	dst_use(&rt->u.dst, jiffies);
	read_unlock_bh(&table->tb6_lock);
	return rt;

}