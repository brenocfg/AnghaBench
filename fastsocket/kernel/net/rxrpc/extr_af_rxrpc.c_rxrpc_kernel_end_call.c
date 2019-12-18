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
struct rxrpc_call {int /*<<< orphan*/  socket; int /*<<< orphan*/  usage; int /*<<< orphan*/  debug_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxrpc_put_call (struct rxrpc_call*) ; 
 int /*<<< orphan*/  rxrpc_remove_user_ID (int /*<<< orphan*/ ,struct rxrpc_call*) ; 

void rxrpc_kernel_end_call(struct rxrpc_call *call)
{
	_enter("%d{%d}", call->debug_id, atomic_read(&call->usage));
	rxrpc_remove_user_ID(call->socket, call);
	rxrpc_put_call(call);
}