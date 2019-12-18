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
struct rxrpc_sock {int /*<<< orphan*/  sk; } ;
struct rxrpc_call {int /*<<< orphan*/  tx_waitq; int /*<<< orphan*/  acks_winsz; int /*<<< orphan*/  acks_tail; int /*<<< orphan*/  acks_head; } ;

/* Variables and functions */
 scalar_t__ CIRC_SPACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  _enter (char*,scalar_t__,long) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  lock_sock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  myself ; 
 int /*<<< orphan*/  release_sock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 long schedule_timeout (long) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int sock_intr_errno (long) ; 

__attribute__((used)) static int rxrpc_wait_for_tx_window(struct rxrpc_sock *rx,
				    struct rxrpc_call *call,
				    long *timeo)
{
	DECLARE_WAITQUEUE(myself, current);
	int ret;

	_enter(",{%d},%ld",
	       CIRC_SPACE(call->acks_head, call->acks_tail, call->acks_winsz),
	       *timeo);

	add_wait_queue(&call->tx_waitq, &myself);

	for (;;) {
		set_current_state(TASK_INTERRUPTIBLE);
		ret = 0;
		if (CIRC_SPACE(call->acks_head, call->acks_tail,
			       call->acks_winsz) > 0)
			break;
		if (signal_pending(current)) {
			ret = sock_intr_errno(*timeo);
			break;
		}

		release_sock(&rx->sk);
		*timeo = schedule_timeout(*timeo);
		lock_sock(&rx->sk);
	}

	remove_wait_queue(&call->tx_waitq, &myself);
	set_current_state(TASK_RUNNING);
	_leave(" = %d", ret);
	return ret;
}