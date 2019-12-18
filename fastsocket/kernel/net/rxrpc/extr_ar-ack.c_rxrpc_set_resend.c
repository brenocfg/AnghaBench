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
typedef  int u8 ;
struct rxrpc_call {scalar_t__ state; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  flags; int /*<<< orphan*/  events; int /*<<< orphan*/  resend_timer; } ;

/* Variables and functions */
 scalar_t__ RXRPC_CALL_COMPLETE ; 
 int /*<<< orphan*/  RXRPC_CALL_RESEND ; 
 int /*<<< orphan*/  RXRPC_CALL_RESEND_TIMER ; 
 int /*<<< orphan*/  RXRPC_CALL_RUN_RTIMER ; 
 int /*<<< orphan*/  _debug (char*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rxrpc_set_resend(struct rxrpc_call *call, u8 resend,
			     unsigned long resend_at)
{
	read_lock_bh(&call->state_lock);
	if (call->state >= RXRPC_CALL_COMPLETE)
		resend = 0;

	if (resend & 1) {
		_debug("SET RESEND");
		set_bit(RXRPC_CALL_RESEND, &call->events);
	}

	if (resend & 2) {
		_debug("MODIFY RESEND TIMER");
		set_bit(RXRPC_CALL_RUN_RTIMER, &call->flags);
		mod_timer(&call->resend_timer, resend_at);
	} else {
		_debug("KILL RESEND TIMER");
		del_timer_sync(&call->resend_timer);
		clear_bit(RXRPC_CALL_RESEND_TIMER, &call->events);
		clear_bit(RXRPC_CALL_RUN_RTIMER, &call->flags);
	}
	read_unlock_bh(&call->state_lock);
}