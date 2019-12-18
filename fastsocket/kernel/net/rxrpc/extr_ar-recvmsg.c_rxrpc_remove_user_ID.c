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
struct rxrpc_sock {int /*<<< orphan*/  call_lock; } ;
struct rxrpc_call {int /*<<< orphan*/  state_lock; int /*<<< orphan*/  events; int /*<<< orphan*/  flags; TYPE_1__* socket; int /*<<< orphan*/  sock_node; int /*<<< orphan*/  debug_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  calls; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXRPC_CALL_HAS_USERID ; 
 int /*<<< orphan*/  RXRPC_CALL_RELEASE ; 
 int /*<<< orphan*/  RXRPC_CALL_RELEASED ; 
 int /*<<< orphan*/  _debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxrpc_queue_call (struct rxrpc_call*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

void rxrpc_remove_user_ID(struct rxrpc_sock *rx, struct rxrpc_call *call)
{
	_debug("RELEASE CALL %d", call->debug_id);

	if (test_bit(RXRPC_CALL_HAS_USERID, &call->flags)) {
		write_lock_bh(&rx->call_lock);
		rb_erase(&call->sock_node, &call->socket->calls);
		clear_bit(RXRPC_CALL_HAS_USERID, &call->flags);
		write_unlock_bh(&rx->call_lock);
	}

	read_lock_bh(&call->state_lock);
	if (!test_bit(RXRPC_CALL_RELEASED, &call->flags) &&
	    !test_and_set_bit(RXRPC_CALL_RELEASE, &call->events))
		rxrpc_queue_call(call);
	read_unlock_bh(&call->state_lock);
}