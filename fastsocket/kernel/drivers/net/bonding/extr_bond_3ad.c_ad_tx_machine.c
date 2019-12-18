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
struct port {int sm_tx_timer_counter; int ntt; int sm_vars; int /*<<< orphan*/  actor_port_number; } ;

/* Variables and functions */
 int AD_MAX_TX_IN_SECOND ; 
 int AD_PORT_LACP_ENABLED ; 
 int /*<<< orphan*/  __update_lacpdu_from_port (struct port*) ; 
 scalar_t__ ad_lacpdu_send (struct port*) ; 
 int ad_ticks_per_sec ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ad_tx_machine(struct port *port)
{
	// check if tx timer expired, to verify that we do not send more than 3 packets per second
	if (port->sm_tx_timer_counter && !(--port->sm_tx_timer_counter)) {
		// check if there is something to send
		if (port->ntt && (port->sm_vars & AD_PORT_LACP_ENABLED)) {
			__update_lacpdu_from_port(port);

			if (ad_lacpdu_send(port) >= 0) {
				pr_debug("Sent LACPDU on port %d\n", port->actor_port_number);

				/* mark ntt as false, so it will not be sent again until
				   demanded */
				port->ntt = false;
			}
		}
		// restart tx timer(to verify that we will not exceed AD_MAX_TX_IN_SECOND
		port->sm_tx_timer_counter=ad_ticks_per_sec/AD_MAX_TX_IN_SECOND;
	}
}