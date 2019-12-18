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
struct sk_filter {int /*<<< orphan*/  len; int /*<<< orphan*/  insns; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 struct sk_filter* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock_bh () ; 
 int /*<<< orphan*/  rcu_read_unlock_bh () ; 
 unsigned int sk_run_filter (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int run_filter(struct sk_buff *skb, struct sock *sk,
				      unsigned int res)
{
	struct sk_filter *filter;

	rcu_read_lock_bh();
	filter = rcu_dereference(sk->sk_filter);
	if (filter != NULL)
		res = sk_run_filter(skb, filter->insns, filter->len);
	rcu_read_unlock_bh();

	return res;
}