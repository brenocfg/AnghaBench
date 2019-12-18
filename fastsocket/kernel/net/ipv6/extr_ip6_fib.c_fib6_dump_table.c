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
struct sk_buff {int dummy; } ;
struct netlink_callback {int* args; } ;
struct fib6_walker_t {int /*<<< orphan*/ * root; } ;
struct fib6_table {int /*<<< orphan*/  tb6_lock; int /*<<< orphan*/  tb6_root; } ;

/* Variables and functions */
 int fib6_walk (struct fib6_walker_t*) ; 
 int fib6_walk_continue (struct fib6_walker_t*) ; 
 int /*<<< orphan*/  fib6_walker_unlink (struct fib6_walker_t*) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fib6_dump_table(struct fib6_table *table, struct sk_buff *skb,
			   struct netlink_callback *cb)
{
	struct fib6_walker_t *w;
	int res;

	w = (void *)cb->args[2];
	w->root = &table->tb6_root;

	if (cb->args[4] == 0) {
		read_lock_bh(&table->tb6_lock);
		res = fib6_walk(w);
		read_unlock_bh(&table->tb6_lock);
		if (res > 0)
			cb->args[4] = 1;
	} else {
		read_lock_bh(&table->tb6_lock);
		res = fib6_walk_continue(w);
		read_unlock_bh(&table->tb6_lock);
		if (res <= 0) {
			fib6_walker_unlink(w);
			cb->args[4] = 0;
		}
	}

	return res;
}