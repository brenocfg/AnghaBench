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
typedef  int /*<<< orphan*/  u32 ;
struct rxrpc_call {scalar_t__ state; TYPE_1__* socket; int /*<<< orphan*/  conn; int /*<<< orphan*/  user_call_ID; int /*<<< orphan*/  debug_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 scalar_t__ RXRPC_CALL_COMPLETE ; 
 int /*<<< orphan*/  _debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  lock_sock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_sock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxrpc_send_abort (struct rxrpc_call*,int /*<<< orphan*/ ) ; 

void rxrpc_kernel_abort_call(struct rxrpc_call *call, u32 abort_code)
{
	_enter("{%d},%d", call->debug_id, abort_code);

	lock_sock(&call->socket->sk);

	_debug("CALL %d USR %lx ST %d on CONN %p",
	       call->debug_id, call->user_call_ID, call->state, call->conn);

	if (call->state < RXRPC_CALL_COMPLETE)
		rxrpc_send_abort(call, abort_code);

	release_sock(&call->socket->sk);
	_leave("");
}