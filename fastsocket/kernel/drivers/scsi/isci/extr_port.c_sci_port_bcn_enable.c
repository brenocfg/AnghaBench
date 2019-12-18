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
typedef  int /*<<< orphan*/  u32 ;
struct isci_port {struct isci_phy** phy_table; } ;
struct isci_phy {TYPE_1__* link_layer_registers; } ;
struct TYPE_2__ {int /*<<< orphan*/  link_layer_control; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct isci_phy**) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sci_port_bcn_enable(struct isci_port *iport)
{
	struct isci_phy *iphy;
	u32 val;
	int i;

	for (i = 0; i < ARRAY_SIZE(iport->phy_table); i++) {
		iphy = iport->phy_table[i];
		if (!iphy)
			continue;
		val = readl(&iphy->link_layer_registers->link_layer_control);
		/* clear the bit by writing 1. */
		writel(val, &iphy->link_layer_registers->link_layer_control);
	}
}