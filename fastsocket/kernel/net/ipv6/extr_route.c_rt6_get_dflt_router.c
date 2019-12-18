#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct rt6_info* rt6_next; } ;
struct TYPE_5__ {TYPE_3__ dst; } ;
struct rt6_info {int rt6i_flags; TYPE_2__ u; int /*<<< orphan*/  rt6i_gateway; struct net_device* rt6i_dev; } ;
struct net_device {int dummy; } ;
struct in6_addr {int dummy; } ;
struct TYPE_4__ {struct rt6_info* leaf; } ;
struct fib6_table {int /*<<< orphan*/  tb6_lock; TYPE_1__ tb6_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT6_TABLE_DFLT ; 
 int RTF_ADDRCONF ; 
 int RTF_DEFAULT ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  dst_hold (TYPE_3__*) ; 
 struct fib6_table* fib6_get_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ipv6_addr_equal (int /*<<< orphan*/ *,struct in6_addr*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

struct rt6_info *rt6_get_dflt_router(struct in6_addr *addr, struct net_device *dev)
{
	struct rt6_info *rt;
	struct fib6_table *table;

	table = fib6_get_table(dev_net(dev), RT6_TABLE_DFLT);
	if (table == NULL)
		return NULL;

	write_lock_bh(&table->tb6_lock);
	for (rt = table->tb6_root.leaf; rt; rt=rt->u.dst.rt6_next) {
		if (dev == rt->rt6i_dev &&
		    ((rt->rt6i_flags & (RTF_ADDRCONF | RTF_DEFAULT)) == (RTF_ADDRCONF | RTF_DEFAULT)) &&
		    ipv6_addr_equal(&rt->rt6i_gateway, addr))
			break;
	}
	if (rt)
		dst_hold(&rt->u.dst);
	write_unlock_bh(&table->tb6_lock);
	return rt;
}