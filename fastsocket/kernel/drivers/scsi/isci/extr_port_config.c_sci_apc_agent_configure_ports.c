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
typedef  size_t u8 ;
struct sci_port_configuration_agent {int phy_configured_mask; TYPE_1__* phy_valid_port_range; } ;
struct isci_port {int active_phy_mask; int physical_port_index; } ;
struct isci_phy {size_t phy_index; } ;
struct isci_host {struct isci_port* ports; } ;
typedef  enum sci_status { ____Placeholder_sci_status } sci_status ;
typedef  enum SCIC_SDS_APC_ACTIVITY { ____Placeholder_SCIC_SDS_APC_ACTIVITY } SCIC_SDS_APC_ACTIVITY ;
struct TYPE_2__ {size_t min_index; size_t max_index; } ;

/* Variables and functions */
#define  SCIC_SDS_APC_ADD_PHY 130 
#define  SCIC_SDS_APC_SKIP_PHY 129 
#define  SCIC_SDS_APC_START_TIMER 128 
 int /*<<< orphan*/  SCIC_SDS_APC_WAIT_LINK_UP_NOTIFICATION ; 
 int SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_apc_agent_start_timer (struct sci_port_configuration_agent*,int /*<<< orphan*/ ) ; 
 int sci_port_add_phy (struct isci_port*,struct isci_phy*) ; 
 struct isci_port* sci_port_configuration_agent_find_port (struct isci_host*,struct isci_phy*) ; 
 scalar_t__ sci_port_is_valid_phy_assignment (struct isci_port*,size_t) ; 

__attribute__((used)) static void sci_apc_agent_configure_ports(struct isci_host *ihost,
					       struct sci_port_configuration_agent *port_agent,
					       struct isci_phy *iphy,
					       bool start_timer)
{
	u8 port_index;
	enum sci_status status;
	struct isci_port *iport;
	enum SCIC_SDS_APC_ACTIVITY apc_activity = SCIC_SDS_APC_SKIP_PHY;

	iport = sci_port_configuration_agent_find_port(ihost, iphy);

	if (iport) {
		if (sci_port_is_valid_phy_assignment(iport, iphy->phy_index))
			apc_activity = SCIC_SDS_APC_ADD_PHY;
		else
			apc_activity = SCIC_SDS_APC_SKIP_PHY;
	} else {
		/*
		 * There is no matching Port for this PHY so lets search through the
		 * Ports and see if we can add the PHY to its own port or maybe start
		 * the timer and wait to see if a wider port can be made.
		 *
		 * Note the break when we reach the condition of the port id == phy id */
		for (port_index = port_agent->phy_valid_port_range[iphy->phy_index].min_index;
		     port_index <= port_agent->phy_valid_port_range[iphy->phy_index].max_index;
		     port_index++) {

			iport = &ihost->ports[port_index];

			/* First we must make sure that this PHY can be added to this Port. */
			if (sci_port_is_valid_phy_assignment(iport, iphy->phy_index)) {
				/*
				 * Port contains a PHY with a greater PHY ID than the current
				 * PHY that has gone link up.  This phy can not be part of any
				 * port so skip it and move on. */
				if (iport->active_phy_mask > (1 << iphy->phy_index)) {
					apc_activity = SCIC_SDS_APC_SKIP_PHY;
					break;
				}

				/*
				 * We have reached the end of our Port list and have not found
				 * any reason why we should not either add the PHY to the port
				 * or wait for more phys to become active. */
				if (iport->physical_port_index == iphy->phy_index) {
					/*
					 * The Port either has no active PHYs.
					 * Consider that if the port had any active PHYs we would have
					 * or active PHYs with
					 * a lower PHY Id than this PHY. */
					if (apc_activity != SCIC_SDS_APC_START_TIMER) {
						apc_activity = SCIC_SDS_APC_ADD_PHY;
					}

					break;
				}

				/*
				 * The current Port has no active PHYs and this PHY could be part
				 * of this Port.  Since we dont know as yet setup to start the
				 * timer and see if there is a better configuration. */
				if (iport->active_phy_mask == 0) {
					apc_activity = SCIC_SDS_APC_START_TIMER;
				}
			} else if (iport->active_phy_mask != 0) {
				/*
				 * The Port has an active phy and the current Phy can not
				 * participate in this port so skip the PHY and see if
				 * there is a better configuration. */
				apc_activity = SCIC_SDS_APC_SKIP_PHY;
			}
		}
	}

	/*
	 * Check to see if the start timer operations should instead map to an
	 * add phy operation.  This is caused because we have been waiting to
	 * add a phy to a port but could not becuase the automatic port
	 * configuration engine had a choice of possible ports for the phy.
	 * Since we have gone through a timeout we are going to restrict the
	 * choice to the smallest possible port. */
	if (
		(start_timer == false)
		&& (apc_activity == SCIC_SDS_APC_START_TIMER)
		) {
		apc_activity = SCIC_SDS_APC_ADD_PHY;
	}

	switch (apc_activity) {
	case SCIC_SDS_APC_ADD_PHY:
		status = sci_port_add_phy(iport, iphy);

		if (status == SCI_SUCCESS) {
			port_agent->phy_configured_mask |= (1 << iphy->phy_index);
		}
		break;

	case SCIC_SDS_APC_START_TIMER:
		sci_apc_agent_start_timer(port_agent,
					  SCIC_SDS_APC_WAIT_LINK_UP_NOTIFICATION);
		break;

	case SCIC_SDS_APC_SKIP_PHY:
	default:
		/* do nothing the PHY can not be made part of a port at this time. */
		break;
	}
}