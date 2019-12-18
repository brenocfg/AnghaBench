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
struct sock {int sk_shutdown; int /*<<< orphan*/  sk_sleep; TYPE_1__* sk_socket; scalar_t__ sk_err; int /*<<< orphan*/  sk_receive_queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int RCV_SHUTDOWN ; 
 int /*<<< orphan*/  SOCK_ASYNC_WAITDATA ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 long schedule_timeout (long) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unix_state_lock (struct sock*) ; 
 int /*<<< orphan*/  unix_state_unlock (struct sock*) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static long unix_stream_data_wait(struct sock *sk, long timeo)
{
	DEFINE_WAIT(wait);

	unix_state_lock(sk);

	for (;;) {
		prepare_to_wait(sk->sk_sleep, &wait, TASK_INTERRUPTIBLE);

		if (!skb_queue_empty(&sk->sk_receive_queue) ||
		    sk->sk_err ||
		    (sk->sk_shutdown & RCV_SHUTDOWN) ||
		    signal_pending(current) ||
		    !timeo)
			break;

		set_bit(SOCK_ASYNC_WAITDATA, &sk->sk_socket->flags);
		unix_state_unlock(sk);
		timeo = schedule_timeout(timeo);
		unix_state_lock(sk);
		clear_bit(SOCK_ASYNC_WAITDATA, &sk->sk_socket->flags);
	}

	finish_wait(sk->sk_sleep, &wait);
	unix_state_unlock(sk);
	return timeo;
}