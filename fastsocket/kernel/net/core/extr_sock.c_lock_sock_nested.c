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
struct TYPE_2__ {int owned; int /*<<< orphan*/  dep_map; int /*<<< orphan*/  slock; } ;
struct sock {TYPE_1__ sk_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  __lock_sock (struct sock*) ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  mutex_acquire (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void lock_sock_nested(struct sock *sk, int subclass)
{
	might_sleep();
	spin_lock_bh(&sk->sk_lock.slock);
	if (sk->sk_lock.owned)
		__lock_sock(sk);
	sk->sk_lock.owned = 1;
	spin_unlock(&sk->sk_lock.slock);
	/*
	 * The sk_lock has mutex_lock() semantics here:
	 */
	mutex_acquire(&sk->sk_lock.dep_map, subclass, 0, _RET_IP_);
	local_bh_enable();
}