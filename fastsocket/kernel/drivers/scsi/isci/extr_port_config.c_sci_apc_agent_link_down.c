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
struct sci_port_configuration_agent {int phy_ready_mask; int phy_configured_mask; } ;
struct isci_port {int dummy; } ;
struct isci_phy {int phy_index; } ;
struct isci_host {int dummy; } ;
typedef  enum sci_status { ____Placeholder_sci_status } sci_status ;

/* Variables and functions */
 int SCI_SUCCESS ; 
 int sci_port_remove_phy (struct isci_port*,struct isci_phy*) ; 

__attribute__((used)) static void sci_apc_agent_link_down(
	struct isci_host *ihost,
	struct sci_port_configuration_agent *port_agent,
	struct isci_port *iport,
	struct isci_phy *iphy)
{
	port_agent->phy_ready_mask &= ~(1 << iphy->phy_index);

	if (!iport)
		return;
	if (port_agent->phy_configured_mask & (1 << iphy->phy_index)) {
		enum sci_status status;

		status = sci_port_remove_phy(iport, iphy);

		if (status == SCI_SUCCESS)
			port_agent->phy_configured_mask &= ~(1 << iphy->phy_index);
	}
}