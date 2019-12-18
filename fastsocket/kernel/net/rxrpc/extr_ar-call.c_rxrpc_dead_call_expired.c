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
struct rxrpc_call {int /*<<< orphan*/  state_lock; int /*<<< orphan*/  state; int /*<<< orphan*/  debug_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXRPC_CALL_DEAD ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_put_call (struct rxrpc_call*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rxrpc_dead_call_expired(unsigned long _call)
{
	struct rxrpc_call *call = (struct rxrpc_call *) _call;

	_enter("{%d}", call->debug_id);

	write_lock_bh(&call->state_lock);
	call->state = RXRPC_CALL_DEAD;
	write_unlock_bh(&call->state_lock);
	rxrpc_put_call(call);
}