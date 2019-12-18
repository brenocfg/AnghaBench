#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {char* i81x_gtt_table; int num_dcache_entries; TYPE_1__* pcidev; scalar_t__ registers; scalar_t__ gtt_bus_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ I810_DRAM_CTL ; 
 int I810_DRAM_ROW_0 ; 
 int I810_DRAM_ROW_0_SDRAM ; 
 int /*<<< orphan*/  I810_GTT_ORDER ; 
 int /*<<< orphan*/  I810_MMADDR ; 
 scalar_t__ I810_PGETBL_CTL ; 
 int I810_PGETBL_ENABLED ; 
 scalar_t__ I810_PTE_BASE ; 
 int /*<<< orphan*/  KB (int) ; 
 char* alloc_gatt_pages (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__ intel_private ; 
 scalar_t__ ioremap (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int readl (scalar_t__) ; 
 int virt_to_phys (char*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int i810_setup(void)
{
	u32 reg_addr;
	char *gtt_table;

	/* i81x does not preallocate the gtt. It's always 64kb in size. */
	gtt_table = alloc_gatt_pages(I810_GTT_ORDER);
	if (gtt_table == NULL)
		return -ENOMEM;
	intel_private.i81x_gtt_table = gtt_table;

	pci_read_config_dword(intel_private.pcidev, I810_MMADDR, &reg_addr);
	reg_addr &= 0xfff80000;

	intel_private.registers = ioremap(reg_addr, KB(64));
	if (!intel_private.registers)
		return -ENOMEM;

	writel(virt_to_phys(gtt_table) | I810_PGETBL_ENABLED,
	       intel_private.registers+I810_PGETBL_CTL);

	intel_private.gtt_bus_addr = reg_addr + I810_PTE_BASE;

	if ((readl(intel_private.registers+I810_DRAM_CTL)
		& I810_DRAM_ROW_0) == I810_DRAM_ROW_0_SDRAM) {
		dev_info(&intel_private.pcidev->dev,
			 "detected 4MB dedicated video ram\n");
		intel_private.num_dcache_entries = 1024;
	}

	return 0;
}