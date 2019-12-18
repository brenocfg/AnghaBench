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
struct TYPE_2__ {int /*<<< orphan*/ * fib_table_hash; } ;
struct net {TYPE_1__ ipv6; } ;
struct fib6_table {int tb6_id; int /*<<< orphan*/  tb6_hlist; int /*<<< orphan*/  tb6_lock; } ;

/* Variables and functions */
 int FIB6_TABLE_HASHSZ ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fib6_link_table(struct net *net, struct fib6_table *tb)
{
	unsigned int h;

	/*
	 * Initialize table lock at a single place to give lockdep a key,
	 * tables aren't visible prior to being linked to the list.
	 */
	rwlock_init(&tb->tb6_lock);

	h = tb->tb6_id & (FIB6_TABLE_HASHSZ - 1);

	/*
	 * No protection necessary, this is the only list mutatation
	 * operation, tables never disappear once they exist.
	 */
	hlist_add_head_rcu(&tb->tb6_hlist, &net->ipv6.fib_table_hash[h]);
}