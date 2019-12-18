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
struct isci_port {struct isci_host* owning_controller; } ;
struct isci_phy {int phy_index; } ;
struct isci_host {int invalid_phy_mask; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void sci_port_invalid_link_up(struct isci_port *iport, struct isci_phy *iphy)
{
	struct isci_host *ihost = iport->owning_controller;

	/*
	 * Check to see if we have alreay reported this link as bad and if
	 * not go ahead and tell the SCI_USER that we have discovered an
	 * invalid link.
	 */
	if ((ihost->invalid_phy_mask & (1 << iphy->phy_index)) == 0) {
		ihost->invalid_phy_mask |= 1 << iphy->phy_index;
		dev_warn(&ihost->pdev->dev, "Invalid link up!\n");
	}
}