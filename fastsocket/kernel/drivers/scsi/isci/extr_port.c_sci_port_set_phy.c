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
struct isci_port {struct isci_phy** phy_table; int /*<<< orphan*/  physical_port_index; int /*<<< orphan*/  logical_port_index; } ;
struct isci_phy {size_t phy_index; } ;
typedef  enum sci_status { ____Placeholder_sci_status } sci_status ;

/* Variables and functions */
 int SCI_FAILURE ; 
 int SCI_SUCCESS ; 
 int /*<<< orphan*/  phy_get_non_dummy_port (struct isci_phy*) ; 
 int /*<<< orphan*/  sci_phy_set_port (struct isci_phy*,struct isci_port*) ; 
 scalar_t__ sci_port_is_valid_phy_assignment (struct isci_port*,size_t) ; 

__attribute__((used)) static enum sci_status sci_port_set_phy(struct isci_port *iport, struct isci_phy *iphy)
{
	/* Check to see if we can add this phy to a port
	 * that means that the phy is not part of a port and that the port does
	 * not already have a phy assinged to the phy index.
	 */
	if (!iport->phy_table[iphy->phy_index] &&
	    !phy_get_non_dummy_port(iphy) &&
	    sci_port_is_valid_phy_assignment(iport, iphy->phy_index)) {
		/* Phy is being added in the stopped state so we are in MPC mode
		 * make logical port index = physical port index
		 */
		iport->logical_port_index = iport->physical_port_index;
		iport->phy_table[iphy->phy_index] = iphy;
		sci_phy_set_port(iphy, iport);

		return SCI_SUCCESS;
	}

	return SCI_FAILURE;
}