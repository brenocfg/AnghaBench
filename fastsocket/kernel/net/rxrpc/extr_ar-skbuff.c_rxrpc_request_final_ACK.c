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
struct rxrpc_call {int state; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  ack_timer; int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXRPC_CALL_ACK_FINAL ; 
 int RXRPC_CALL_CLIENT_FINAL_ACK ; 
#define  RXRPC_CALL_CLIENT_RECV_REPLY 129 
 int RXRPC_CALL_SERVER_ACK_REQUEST ; 
#define  RXRPC_CALL_SERVER_RECV_REQUEST 128 
 int /*<<< orphan*/  _debug (char*) ; 
 int /*<<< orphan*/  rxrpc_get_call (struct rxrpc_call*) ; 
 int /*<<< orphan*/  rxrpc_queue_call (struct rxrpc_call*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_to_del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rxrpc_request_final_ACK(struct rxrpc_call *call)
{
	/* the call may be aborted before we have a chance to ACK it */
	write_lock(&call->state_lock);

	switch (call->state) {
	case RXRPC_CALL_CLIENT_RECV_REPLY:
		call->state = RXRPC_CALL_CLIENT_FINAL_ACK;
		_debug("request final ACK");

		/* get an extra ref on the call for the final-ACK generator to
		 * release */
		rxrpc_get_call(call);
		set_bit(RXRPC_CALL_ACK_FINAL, &call->events);
		if (try_to_del_timer_sync(&call->ack_timer) >= 0)
			rxrpc_queue_call(call);
		break;

	case RXRPC_CALL_SERVER_RECV_REQUEST:
		call->state = RXRPC_CALL_SERVER_ACK_REQUEST;
	default:
		break;
	}

	write_unlock(&call->state_lock);
}