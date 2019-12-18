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
 int /*<<< orphan*/  POLLERR ; 
 int /*<<< orphan*/  POLL_ERR ; 
 int /*<<< orphan*/  SOCK_WAKE_IO ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ sk_has_sleeper (struct sock*) ; 
 int /*<<< orphan*/  sk_wake_async (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible_poll (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sock_def_error_report(struct sock *sk)
{
	read_lock(&sk->sk_callback_lock);
	if (sk_has_sleeper(sk))
		wake_up_interruptible_poll(sk->sk_sleep, POLLERR);
	sk_wake_async(sk, SOCK_WAKE_IO, POLL_ERR);
	read_unlock(&sk->sk_callback_lock);
}