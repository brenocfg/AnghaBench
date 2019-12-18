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
struct TYPE_2__ {int /*<<< orphan*/  width; int /*<<< orphan*/  speed; int /*<<< orphan*/  type; } ;
struct pch_gbe_hw {TYPE_1__ bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  pch_gbe_bus_speed_2500 ; 
 int /*<<< orphan*/  pch_gbe_bus_type_pci_express ; 
 int /*<<< orphan*/  pch_gbe_bus_width_pcie_x1 ; 

__attribute__((used)) static void pch_gbe_plat_get_bus_info(struct pch_gbe_hw *hw)
{
	hw->bus.type  = pch_gbe_bus_type_pci_express;
	hw->bus.speed = pch_gbe_bus_speed_2500;
	hw->bus.width = pch_gbe_bus_width_pcie_x1;
}