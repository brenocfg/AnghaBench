#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dst; } ;
struct rt6_info {TYPE_2__ u; struct fib6_table* rt6i_table; int /*<<< orphan*/  rt6i_dev; } ;
struct nl_info {int dummy; } ;
struct TYPE_3__ {struct rt6_info* ip6_null_entry; } ;
struct net {TYPE_1__ ipv6; } ;
struct fib6_table {int /*<<< orphan*/  tb6_lock; } ;

/* Variables and functions */
 int ENOENT ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_release (int /*<<< orphan*/ *) ; 
 int fib6_del (struct rt6_info*,struct nl_info*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __ip6_del_rt(struct rt6_info *rt, struct nl_info *info)
{
	int err;
	struct fib6_table *table;
	struct net *net = dev_net(rt->rt6i_dev);

	if (rt == net->ipv6.ip6_null_entry)
		return -ENOENT;

	table = rt->rt6i_table;
	write_lock_bh(&table->tb6_lock);

	err = fib6_del(rt, info);
	dst_release(&rt->u.dst);

	write_unlock_bh(&table->tb6_lock);

	return err;
}