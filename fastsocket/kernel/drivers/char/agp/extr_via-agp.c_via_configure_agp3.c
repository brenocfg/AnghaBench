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
struct aper_size_info_16 {int dummy; } ;
struct TYPE_2__ {int gart_bus_addr; int gatt_bus_addr; int /*<<< orphan*/  dev; int /*<<< orphan*/  current_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_APBASE ; 
 struct aper_size_info_16* A_SIZE_16 (int /*<<< orphan*/ ) ; 
 int PCI_BASE_ADDRESS_MEM_MASK ; 
 int /*<<< orphan*/  VIA_AGP3_ATTBASE ; 
 int /*<<< orphan*/  VIA_AGP3_GARTCTRL ; 
 TYPE_1__* agp_bridge ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int via_configure_agp3(void)
{
	u32 temp;
	struct aper_size_info_16 *current_size;

	current_size = A_SIZE_16(agp_bridge->current_size);

	/* address to map too */
	pci_read_config_dword(agp_bridge->dev, AGP_APBASE, &temp);
	agp_bridge->gart_bus_addr = (temp & PCI_BASE_ADDRESS_MEM_MASK);

	/* attbase - aperture GATT base */
	pci_write_config_dword(agp_bridge->dev, VIA_AGP3_ATTBASE,
		agp_bridge->gatt_bus_addr & 0xfffff000);

	/* 1. Enable GTLB in RX90<7>, all AGP aperture access needs to fetch
	 *    translation table first.
	 * 2. Enable AGP aperture in RX91<0>. This bit controls the enabling of the
	 *    graphics AGP aperture for the AGP3.0 port.
	 */
	pci_read_config_dword(agp_bridge->dev, VIA_AGP3_GARTCTRL, &temp);
	pci_write_config_dword(agp_bridge->dev, VIA_AGP3_GARTCTRL, temp | (3<<7));
	return 0;
}