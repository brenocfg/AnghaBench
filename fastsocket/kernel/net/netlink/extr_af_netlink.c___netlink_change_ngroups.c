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
struct sock {size_t sk_protocol; } ;
struct netlink_table {unsigned int groups; unsigned long* listeners; } ;
struct listeners_rcu_head {unsigned long* ptr; int /*<<< orphan*/  rcu_head; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NLGRPLONGS (unsigned int) ; 
 scalar_t__ NLGRPSZ (unsigned int) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned long*,unsigned long*,scalar_t__) ; 
 int /*<<< orphan*/  netlink_free_old_listeners ; 
 struct netlink_table* nl_table ; 
 int /*<<< orphan*/  rcu_assign_pointer (unsigned long*,unsigned long*) ; 

int __netlink_change_ngroups(struct sock *sk, unsigned int groups)
{
	unsigned long *listeners, *old = NULL;
	struct listeners_rcu_head *old_rcu_head;
	struct netlink_table *tbl = &nl_table[sk->sk_protocol];

	if (groups < 32)
		groups = 32;

	if (NLGRPSZ(tbl->groups) < NLGRPSZ(groups)) {
		listeners = kzalloc(NLGRPSZ(groups) +
				    sizeof(struct listeners_rcu_head),
				    GFP_ATOMIC);
		if (!listeners)
			return -ENOMEM;
		old = tbl->listeners;
		memcpy(listeners, old, NLGRPSZ(tbl->groups));
		rcu_assign_pointer(tbl->listeners, listeners);
		/*
		 * Free the old memory after an RCU grace period so we
		 * don't leak it. We use call_rcu() here in order to be
		 * able to call this function from atomic contexts. The
		 * allocation of this memory will have reserved enough
		 * space for struct listeners_rcu_head at the end.
		 */
		old_rcu_head = (void *)(tbl->listeners +
					NLGRPLONGS(tbl->groups));
		old_rcu_head->ptr = old;
		call_rcu(&old_rcu_head->rcu_head, netlink_free_old_listeners);
	}
	tbl->groups = groups;

	return 0;
}