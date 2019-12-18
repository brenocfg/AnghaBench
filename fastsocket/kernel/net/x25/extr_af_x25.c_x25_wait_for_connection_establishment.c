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
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  sk_sleep; TYPE_1__* sk_socket; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  SS_UNCONNECTED ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 scalar_t__ TCP_ESTABLISHED ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_wait_queue_exclusive (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int sock_error (struct sock*) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int x25_wait_for_connection_establishment(struct sock *sk)
{
	DECLARE_WAITQUEUE(wait, current);
	int rc;

	add_wait_queue_exclusive(sk->sk_sleep, &wait);
	for (;;) {
		__set_current_state(TASK_INTERRUPTIBLE);
		rc = -ERESTARTSYS;
		if (signal_pending(current))
			break;
		rc = sock_error(sk);
		if (rc) {
			sk->sk_socket->state = SS_UNCONNECTED;
			break;
		}
		rc = 0;
		if (sk->sk_state != TCP_ESTABLISHED) {
			release_sock(sk);
			schedule();
			lock_sock(sk);
		} else
			break;
	}
	__set_current_state(TASK_RUNNING);
	remove_wait_queue(sk->sk_sleep, &wait);
	return rc;
}