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
struct isci_port {scalar_t__ logical_port_index; int /*<<< orphan*/ * port_pe_configuration_register; struct isci_host* owning_controller; } ;
struct isci_phy {scalar_t__ protocol; size_t phy_index; } ;
struct isci_host {struct isci_port* ports; } ;

/* Variables and functions */
 scalar_t__ SAS_PROTOCOL_SATA ; 
 scalar_t__ SCIC_SDS_DUMMY_PORT ; 
 int /*<<< orphan*/  sci_port_invalid_link_up (struct isci_port*,struct isci_phy*) ; 
 scalar_t__ sci_port_is_wide (struct isci_port*) ; 
 int /*<<< orphan*/  writel (size_t,int /*<<< orphan*/ *) ; 

bool sci_port_link_detected(struct isci_port *iport, struct isci_phy *iphy)
{
	if ((iport->logical_port_index != SCIC_SDS_DUMMY_PORT) &&
	    (iphy->protocol == SAS_PROTOCOL_SATA)) {
		if (sci_port_is_wide(iport)) {
			sci_port_invalid_link_up(iport, iphy);
			return false;
		} else {
			struct isci_host *ihost = iport->owning_controller;
			struct isci_port *dst_port = &(ihost->ports[iphy->phy_index]);
			writel(iphy->phy_index,
			       &dst_port->port_pe_configuration_register[iphy->phy_index]);
		}
	}

	return true;
}