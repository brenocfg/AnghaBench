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
typedef  int /*<<< orphan*/  u32 ;
struct rxrpc_call {scalar_t__ state; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  flags; int /*<<< orphan*/  events; int /*<<< orphan*/  ack_timer; int /*<<< orphan*/  resend_timer; int /*<<< orphan*/  abort_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXRPC_CALL_ABORT ; 
 int /*<<< orphan*/  RXRPC_CALL_ACK ; 
 scalar_t__ RXRPC_CALL_COMPLETE ; 
 scalar_t__ RXRPC_CALL_LOCALLY_ABORTED ; 
 int /*<<< orphan*/  RXRPC_CALL_RESEND_TIMER ; 
 int /*<<< orphan*/  RXRPC_CALL_RUN_RTIMER ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxrpc_queue_call (struct rxrpc_call*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rxrpc_send_abort(struct rxrpc_call *call, u32 abort_code)
{
	write_lock_bh(&call->state_lock);

	if (call->state <= RXRPC_CALL_COMPLETE) {
		call->state = RXRPC_CALL_LOCALLY_ABORTED;
		call->abort_code = abort_code;
		set_bit(RXRPC_CALL_ABORT, &call->events);
		del_timer_sync(&call->resend_timer);
		del_timer_sync(&call->ack_timer);
		clear_bit(RXRPC_CALL_RESEND_TIMER, &call->events);
		clear_bit(RXRPC_CALL_ACK, &call->events);
		clear_bit(RXRPC_CALL_RUN_RTIMER, &call->flags);
		rxrpc_queue_call(call);
	}

	write_unlock_bh(&call->state_lock);
}