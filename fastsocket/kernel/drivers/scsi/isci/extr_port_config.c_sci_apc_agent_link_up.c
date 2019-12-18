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
struct sci_port_configuration_agent {int phy_ready_mask; } ;
struct isci_port {int dummy; } ;
struct isci_phy {int phy_index; } ;
struct isci_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_SDS_APC_WAIT_LINK_UP_NOTIFICATION ; 
 int /*<<< orphan*/  sci_apc_agent_start_timer (struct sci_port_configuration_agent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_port_link_up (struct isci_port*,struct isci_phy*) ; 

__attribute__((used)) static void sci_apc_agent_link_up(struct isci_host *ihost,
				       struct sci_port_configuration_agent *port_agent,
				       struct isci_port *iport,
				       struct isci_phy *iphy)
{
	u8 phy_index  = iphy->phy_index;

	if (!iport) {
		/* the phy is not the part of this port */
		port_agent->phy_ready_mask |= 1 << phy_index;
		sci_apc_agent_start_timer(port_agent,
					  SCIC_SDS_APC_WAIT_LINK_UP_NOTIFICATION);
	} else {
		/* the phy is already the part of the port */
		port_agent->phy_ready_mask |= 1 << phy_index;
		sci_port_link_up(iport, iphy);
	}
}