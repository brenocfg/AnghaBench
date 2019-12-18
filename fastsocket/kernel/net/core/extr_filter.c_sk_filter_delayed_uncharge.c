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
struct sock {int /*<<< orphan*/  sk_omem_alloc; } ;
struct sk_filter {int /*<<< orphan*/  rcu; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_sub (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_rcu_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int sk_filter_len (struct sk_filter*) ; 
 int /*<<< orphan*/  sk_filter_rcu_release ; 

__attribute__((used)) static void sk_filter_delayed_uncharge(struct sock *sk, struct sk_filter *fp)
{
	unsigned int size = sk_filter_len(fp);

	atomic_sub(size, &sk->sk_omem_alloc);
	call_rcu_bh(&fp->rcu, sk_filter_rcu_release);
}