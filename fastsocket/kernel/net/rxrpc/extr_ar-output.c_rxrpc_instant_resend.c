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
struct rxrpc_call {scalar_t__ state; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  events; int /*<<< orphan*/  flags; int /*<<< orphan*/  resend_timer; } ;

/* Variables and functions */
 scalar_t__ RXRPC_CALL_COMPLETE ; 
 int /*<<< orphan*/  RXRPC_CALL_RESEND_TIMER ; 
 int /*<<< orphan*/  RXRPC_CALL_RUN_RTIMER ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxrpc_queue_call (struct rxrpc_call*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ try_to_del_timer_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void rxrpc_instant_resend(struct rxrpc_call *call)
{
	read_lock_bh(&call->state_lock);
	if (try_to_del_timer_sync(&call->resend_timer) >= 0) {
		clear_bit(RXRPC_CALL_RUN_RTIMER, &call->flags);
		if (call->state < RXRPC_CALL_COMPLETE &&
		    !test_and_set_bit(RXRPC_CALL_RESEND_TIMER, &call->events))
			rxrpc_queue_call(call);
	}
	read_unlock_bh(&call->state_lock);
}