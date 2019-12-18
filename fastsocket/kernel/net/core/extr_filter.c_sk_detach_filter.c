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
struct sock {int /*<<< orphan*/  sk_filter; } ;
struct sk_filter {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sk_filter* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock_bh () ; 
 int /*<<< orphan*/  rcu_read_unlock_bh () ; 
 int /*<<< orphan*/  sk_filter_delayed_uncharge (struct sock*,struct sk_filter*) ; 

int sk_detach_filter(struct sock *sk)
{
	int ret = -ENOENT;
	struct sk_filter *filter;

	rcu_read_lock_bh();
	filter = rcu_dereference(sk->sk_filter);
	if (filter) {
		rcu_assign_pointer(sk->sk_filter, NULL);
		sk_filter_delayed_uncharge(sk, filter);
		ret = 0;
	}
	rcu_read_unlock_bh();
	return ret;
}