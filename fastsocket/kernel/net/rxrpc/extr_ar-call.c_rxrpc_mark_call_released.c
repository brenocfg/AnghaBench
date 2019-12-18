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
struct rxrpc_call {scalar_t__ state; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  events; int /*<<< orphan*/  abort_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXRPC_CALL_ABORT ; 
 scalar_t__ RXRPC_CALL_COMPLETE ; 
 scalar_t__ RXRPC_CALL_DEAD ; 
 scalar_t__ RXRPC_CALL_LOCALLY_ABORTED ; 
 int /*<<< orphan*/  RXRPC_CALL_RELEASE ; 
 int /*<<< orphan*/  RX_CALL_DEAD ; 
 int /*<<< orphan*/  _debug (char*,struct rxrpc_call*) ; 
 int /*<<< orphan*/  rxrpc_queue_call (struct rxrpc_call*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rxrpc_mark_call_released(struct rxrpc_call *call)
{
	bool sched;

	write_lock(&call->state_lock);
	if (call->state < RXRPC_CALL_DEAD) {
		sched = false;
		if (call->state < RXRPC_CALL_COMPLETE) {
			_debug("abort call %p", call);
			call->state = RXRPC_CALL_LOCALLY_ABORTED;
			call->abort_code = RX_CALL_DEAD;
			if (!test_and_set_bit(RXRPC_CALL_ABORT, &call->events))
				sched = true;
		}
		if (!test_and_set_bit(RXRPC_CALL_RELEASE, &call->events))
			sched = true;
		if (sched)
			rxrpc_queue_call(call);
	}
	write_unlock(&call->state_lock);
}