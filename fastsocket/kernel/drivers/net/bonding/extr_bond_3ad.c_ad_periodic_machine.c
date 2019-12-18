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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int port_state; } ;
struct port {scalar_t__ sm_periodic_state; int sm_vars; int actor_oper_port_state; int ntt; scalar_t__ sm_periodic_timer_counter; int /*<<< orphan*/  actor_port_number; TYPE_1__ partner_oper; int /*<<< orphan*/  is_enabled; } ;
typedef  scalar_t__ periodic_states_t ;

/* Variables and functions */
#define  AD_FAST_PERIODIC 131 
 int /*<<< orphan*/  AD_FAST_PERIODIC_TIME ; 
#define  AD_NO_PERIODIC 130 
 int /*<<< orphan*/  AD_PERIODIC_TIMER ; 
#define  AD_PERIODIC_TX 129 
 int AD_PORT_BEGIN ; 
 int AD_PORT_LACP_ENABLED ; 
#define  AD_SLOW_PERIODIC 128 
 int /*<<< orphan*/  AD_SLOW_PERIODIC_TIME ; 
 int AD_STATE_LACP_ACTIVITY ; 
 int AD_STATE_LACP_TIMEOUT ; 
 int /*<<< orphan*/  __ad_timer_to_ticks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void ad_periodic_machine(struct port *port)
{
	periodic_states_t last_state;

	// keep current state machine state to compare later if it was changed
	last_state = port->sm_periodic_state;

	// check if port was reinitialized
	if (((port->sm_vars & AD_PORT_BEGIN) || !(port->sm_vars & AD_PORT_LACP_ENABLED) || !port->is_enabled) ||
	    (!(port->actor_oper_port_state & AD_STATE_LACP_ACTIVITY) && !(port->partner_oper.port_state & AD_STATE_LACP_ACTIVITY))
	   ) {
		port->sm_periodic_state = AD_NO_PERIODIC;	     // next state
	}
	// check if state machine should change state
	else if (port->sm_periodic_timer_counter) {
		// check if periodic state machine expired
		if (!(--port->sm_periodic_timer_counter)) {
			// if expired then do tx
			port->sm_periodic_state = AD_PERIODIC_TX;    // next state
		} else {
			// If not expired, check if there is some new timeout parameter from the partner state
			switch (port->sm_periodic_state) {
			case AD_FAST_PERIODIC:
				if (!(port->partner_oper.port_state & AD_STATE_LACP_TIMEOUT)) {
					port->sm_periodic_state = AD_SLOW_PERIODIC;  // next state
				}
				break;
			case AD_SLOW_PERIODIC:
				if ((port->partner_oper.port_state & AD_STATE_LACP_TIMEOUT)) {
					// stop current timer
					port->sm_periodic_timer_counter = 0;
					port->sm_periodic_state = AD_PERIODIC_TX;	 // next state
				}
				break;
			default:    //to silence the compiler
				break;
			}
		}
	} else {
		switch (port->sm_periodic_state) {
		case AD_NO_PERIODIC:
			port->sm_periodic_state = AD_FAST_PERIODIC;	 // next state
			break;
		case AD_PERIODIC_TX:
			if (!(port->partner_oper.port_state & AD_STATE_LACP_TIMEOUT)) {
				port->sm_periodic_state = AD_SLOW_PERIODIC;  // next state
			} else {
				port->sm_periodic_state = AD_FAST_PERIODIC;  // next state
			}
			break;
		default:    //to silence the compiler
			break;
		}
	}

	// check if the state machine was changed
	if (port->sm_periodic_state != last_state) {
		pr_debug("Periodic Machine: Port=%d, Last State=%d, Curr State=%d\n", port->actor_port_number, last_state, port->sm_periodic_state);
		switch (port->sm_periodic_state) {
		case AD_NO_PERIODIC:
			port->sm_periodic_timer_counter = 0;	   // zero timer
			break;
		case AD_FAST_PERIODIC:
			port->sm_periodic_timer_counter = __ad_timer_to_ticks(AD_PERIODIC_TIMER, (u16)(AD_FAST_PERIODIC_TIME))-1; // decrement 1 tick we lost in the PERIODIC_TX cycle
			break;
		case AD_SLOW_PERIODIC:
			port->sm_periodic_timer_counter = __ad_timer_to_ticks(AD_PERIODIC_TIMER, (u16)(AD_SLOW_PERIODIC_TIME))-1; // decrement 1 tick we lost in the PERIODIC_TX cycle
			break;
		case AD_PERIODIC_TX:
			port->ntt = true;
			break;
		default:    //to silence the compiler
			break;
		}
	}
}