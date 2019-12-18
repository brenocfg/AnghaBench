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
struct rt6_info {struct fib6_table* rt6i_table; } ;
struct nl_info {int dummy; } ;
struct fib6_table {int /*<<< orphan*/  tb6_lock; int /*<<< orphan*/  tb6_root; } ;

/* Variables and functions */
 int fib6_add (int /*<<< orphan*/ *,struct rt6_info*,struct nl_info*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __ip6_ins_rt(struct rt6_info *rt, struct nl_info *info)
{
	int err;
	struct fib6_table *table;

	table = rt->rt6i_table;
	write_lock_bh(&table->tb6_lock);
	err = fib6_add(&table->tb6_root, rt, info);
	write_unlock_bh(&table->tb6_lock);

	return err;
}