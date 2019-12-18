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
struct sci_port_configuration_agent {int phy_ready_mask; int phy_configured_mask; int timer_pending; int /*<<< orphan*/  timer; } ;
struct isci_port {int dummy; } ;
struct isci_phy {int phy_index; } ;
struct isci_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_SDS_MPC_RECONFIGURATION_TIMEOUT ; 
 int /*<<< orphan*/  sci_mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_port_link_down (struct isci_port*,struct isci_phy*) ; 

__attribute__((used)) static void sci_mpc_agent_link_down(
	struct isci_host *ihost,
	struct sci_port_configuration_agent *port_agent,
	struct isci_port *iport,
	struct isci_phy *iphy)
{
	if (iport != NULL) {
		/*
		 * If we can form a new port from the remainder of the phys
		 * then we want to start the timer to allow the SCI User to
		 * cleanup old devices and rediscover the port before
		 * rebuilding the port with the phys that remain in the ready
		 * state.
		 */
		port_agent->phy_ready_mask &= ~(1 << iphy->phy_index);
		port_agent->phy_configured_mask &= ~(1 << iphy->phy_index);

		/*
		 * Check to see if there are more phys waiting to be
		 * configured into a port. If there are allow the SCI User
		 * to tear down this port, if necessary, and then reconstruct
		 * the port after the timeout.
		 */
		if ((port_agent->phy_configured_mask == 0x0000) &&
		    (port_agent->phy_ready_mask != 0x0000) &&
		    !port_agent->timer_pending) {
			port_agent->timer_pending = true;

			sci_mod_timer(&port_agent->timer,
				      SCIC_SDS_MPC_RECONFIGURATION_TIMEOUT);
		}

		sci_port_link_down(iport, iphy);
	}
}