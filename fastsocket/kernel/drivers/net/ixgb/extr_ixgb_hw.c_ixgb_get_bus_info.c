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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ type; int /*<<< orphan*/  width; void* speed; } ;
struct ixgb_hw {TYPE_1__ bus; } ;

/* Variables and functions */
 int IXGB_READ_REG (struct ixgb_hw*,int /*<<< orphan*/ ) ; 
 int IXGB_STATUS_BUS64 ; 
 int IXGB_STATUS_PCIX_MODE ; 
#define  IXGB_STATUS_PCIX_SPD_100 130 
#define  IXGB_STATUS_PCIX_SPD_133 129 
#define  IXGB_STATUS_PCIX_SPD_66 128 
 int IXGB_STATUS_PCIX_SPD_MASK ; 
 int IXGB_STATUS_PCI_SPD ; 
 int /*<<< orphan*/  STATUS ; 
 void* ixgb_bus_speed_100 ; 
 void* ixgb_bus_speed_133 ; 
 void* ixgb_bus_speed_33 ; 
 void* ixgb_bus_speed_66 ; 
 void* ixgb_bus_speed_reserved ; 
 scalar_t__ ixgb_bus_type_pci ; 
 scalar_t__ ixgb_bus_type_pcix ; 
 int /*<<< orphan*/  ixgb_bus_width_32 ; 
 int /*<<< orphan*/  ixgb_bus_width_64 ; 

__attribute__((used)) static void
ixgb_get_bus_info(struct ixgb_hw *hw)
{
	u32 status_reg;

	status_reg = IXGB_READ_REG(hw, STATUS);

	hw->bus.type = (status_reg & IXGB_STATUS_PCIX_MODE) ?
		ixgb_bus_type_pcix : ixgb_bus_type_pci;

	if (hw->bus.type == ixgb_bus_type_pci) {
		hw->bus.speed = (status_reg & IXGB_STATUS_PCI_SPD) ?
			ixgb_bus_speed_66 : ixgb_bus_speed_33;
	} else {
		switch (status_reg & IXGB_STATUS_PCIX_SPD_MASK) {
		case IXGB_STATUS_PCIX_SPD_66:
			hw->bus.speed = ixgb_bus_speed_66;
			break;
		case IXGB_STATUS_PCIX_SPD_100:
			hw->bus.speed = ixgb_bus_speed_100;
			break;
		case IXGB_STATUS_PCIX_SPD_133:
			hw->bus.speed = ixgb_bus_speed_133;
			break;
		default:
			hw->bus.speed = ixgb_bus_speed_reserved;
			break;
		}
	}

	hw->bus.width = (status_reg & IXGB_STATUS_BUS64) ?
		ixgb_bus_width_64 : ixgb_bus_width_32;

	return;
}