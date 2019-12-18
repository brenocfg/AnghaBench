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
struct socket {struct sock* sk; } ;
struct TYPE_2__ {unsigned long data; int /*<<< orphan*/  function; scalar_t__ expires; } ;
struct sock {TYPE_1__ sk_timer; int /*<<< orphan*/  sk_receive_queue; int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;} ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  econet_destroy_timer ; 
 int /*<<< orphan*/  econet_mutex ; 
 int /*<<< orphan*/  econet_remove_socket (int /*<<< orphan*/ *,struct sock*) ; 
 int /*<<< orphan*/  econet_sklist ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_free (struct sock*) ; 
 scalar_t__ sk_has_allocations (struct sock*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_orphan (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static int econet_release(struct socket *sock)
{
	struct sock *sk;

	mutex_lock(&econet_mutex);

	sk = sock->sk;
	if (!sk)
		goto out_unlock;

	econet_remove_socket(&econet_sklist, sk);

	/*
	 *	Now the socket is dead. No more input will appear.
	 */

	sk->sk_state_change(sk);	/* It is useless. Just for sanity. */

	sock_orphan(sk);

	/* Purge queues */

	skb_queue_purge(&sk->sk_receive_queue);

	if (sk_has_allocations(sk)) {
		sk->sk_timer.data     = (unsigned long)sk;
		sk->sk_timer.expires  = jiffies + HZ;
		sk->sk_timer.function = econet_destroy_timer;
		add_timer(&sk->sk_timer);

		goto out_unlock;
	}

	sk_free(sk);

out_unlock:
	mutex_unlock(&econet_mutex);
	return 0;
}