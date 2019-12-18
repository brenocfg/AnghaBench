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
struct rxrpc_call {int state; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  flags; int /*<<< orphan*/  events; int /*<<< orphan*/  resend_timer; int /*<<< orphan*/  acks_latest; } ;

/* Variables and functions */
#define  RXRPC_CALL_CLIENT_AWAIT_REPLY 128 
 int RXRPC_CALL_CLIENT_RECV_REPLY ; 
 int /*<<< orphan*/  RXRPC_CALL_RCVD_ACKALL ; 
 int /*<<< orphan*/  RXRPC_CALL_RESEND ; 
 int /*<<< orphan*/  RXRPC_CALL_RESEND_TIMER ; 
 int /*<<< orphan*/  RXRPC_CALL_RUN_RTIMER ; 
 int /*<<< orphan*/  _debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_to_del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rxrpc_assume_implicit_ackall(struct rxrpc_call *call, u32 serial)
{
	write_lock_bh(&call->state_lock);

	switch (call->state) {
	case RXRPC_CALL_CLIENT_AWAIT_REPLY:
		call->state = RXRPC_CALL_CLIENT_RECV_REPLY;
		call->acks_latest = serial;

		_debug("implicit ACKALL %%%u", call->acks_latest);
		set_bit(RXRPC_CALL_RCVD_ACKALL, &call->events);
		write_unlock_bh(&call->state_lock);

		if (try_to_del_timer_sync(&call->resend_timer) >= 0) {
			clear_bit(RXRPC_CALL_RESEND_TIMER, &call->events);
			clear_bit(RXRPC_CALL_RESEND, &call->events);
			clear_bit(RXRPC_CALL_RUN_RTIMER, &call->flags);
		}
		break;

	default:
		write_unlock_bh(&call->state_lock);
		break;
	}
}