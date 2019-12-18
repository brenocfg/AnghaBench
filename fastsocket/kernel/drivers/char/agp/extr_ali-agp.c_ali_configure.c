#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct aper_size_info_32 {int size_value; } ;
struct TYPE_5__ {int gatt_bus_addr; int gart_bus_addr; scalar_t__ type; TYPE_1__* dev; int /*<<< orphan*/  current_size; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_APBASE ; 
 int /*<<< orphan*/  ALI_ATTBASE ; 
 scalar_t__ ALI_M1541 ; 
 int /*<<< orphan*/  ALI_TLBCTRL ; 
 struct aper_size_info_32* A_SIZE_32 (int /*<<< orphan*/ ) ; 
 int PCI_BASE_ADDRESS_MEM_MASK ; 
 TYPE_3__* agp_bridge ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  pci_read_config_dword (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ali_configure(void)
{
	u32 temp;
	struct aper_size_info_32 *current_size;

	current_size = A_SIZE_32(agp_bridge->current_size);

	/* aperture size and gatt addr */
	pci_read_config_dword(agp_bridge->dev, ALI_ATTBASE, &temp);
	temp = (((temp & 0x00000ff0) | (agp_bridge->gatt_bus_addr & 0xfffff000))
			| (current_size->size_value & 0xf));
	pci_write_config_dword(agp_bridge->dev, ALI_ATTBASE, temp);

	/* tlb control */
	pci_read_config_dword(agp_bridge->dev, ALI_TLBCTRL, &temp);
	pci_write_config_dword(agp_bridge->dev, ALI_TLBCTRL, ((temp & 0xffffff00) | 0x00000010));

	/* address to map to */
	pci_read_config_dword(agp_bridge->dev, AGP_APBASE, &temp);
	agp_bridge->gart_bus_addr = (temp & PCI_BASE_ADDRESS_MEM_MASK);

#if 0
	if (agp_bridge->type == ALI_M1541) {
		u32 nlvm_addr = 0;

		switch (current_size->size_value) {
			case 0:  break;
			case 1:  nlvm_addr = 0x100000;break;
			case 2:  nlvm_addr = 0x200000;break;
			case 3:  nlvm_addr = 0x400000;break;
			case 4:  nlvm_addr = 0x800000;break;
			case 6:  nlvm_addr = 0x1000000;break;
			case 7:  nlvm_addr = 0x2000000;break;
			case 8:  nlvm_addr = 0x4000000;break;
			case 9:  nlvm_addr = 0x8000000;break;
			case 10: nlvm_addr = 0x10000000;break;
			default: break;
		}
		nlvm_addr--;
		nlvm_addr&=0xfff00000;

		nlvm_addr+= agp_bridge->gart_bus_addr;
		nlvm_addr|=(agp_bridge->gart_bus_addr>>12);
		dev_info(&agp_bridge->dev->dev, "nlvm top &base = %8x\n",
			 nlvm_addr);
	}
#endif

	pci_read_config_dword(agp_bridge->dev, ALI_TLBCTRL, &temp);
	temp &= 0xffffff7f;		//enable TLB
	pci_write_config_dword(agp_bridge->dev, ALI_TLBCTRL, temp);

	return 0;
}