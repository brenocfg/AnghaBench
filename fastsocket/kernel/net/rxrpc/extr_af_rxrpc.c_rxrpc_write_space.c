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
struct sock {int /*<<< orphan*/  sk_callback_lock; int /*<<< orphan*/  sk_sleep; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLL_OUT ; 
 int /*<<< orphan*/  SOCK_WAKE_SPACE ; 
 int /*<<< orphan*/  _enter (char*,struct sock*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ rxrpc_writable (struct sock*) ; 
 scalar_t__ sk_has_sleeper (struct sock*) ; 
 int /*<<< orphan*/  sk_wake_async (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rxrpc_write_space(struct sock *sk)
{
	_enter("%p", sk);
	read_lock(&sk->sk_callback_lock);
	if (rxrpc_writable(sk)) {
		if (sk_has_sleeper(sk))
			wake_up_interruptible(sk->sk_sleep);
		sk_wake_async(sk, SOCK_WAKE_SPACE, POLL_OUT);
	}
	read_unlock(&sk->sk_callback_lock);
}