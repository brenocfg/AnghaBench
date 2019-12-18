#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
typedef  int resource_size_t ;
struct TYPE_6__ {unsigned long base_addr; } ;
struct TYPE_4__ {int start; } ;
struct TYPE_5__ {TYPE_1__ resource; } ;

/* Variables and functions */
 int DFX_BUS_EISA (struct device*) ; 
 int DFX_BUS_PCI (struct device*) ; 
 int DFX_BUS_TC (struct device*) ; 
 scalar_t__ DFX_MMIO ; 
 int PI_ESIC_K_CSR_IO_LEN ; 
 scalar_t__ PI_ESIC_K_MEM_ADD_CMP_0 ; 
 scalar_t__ PI_ESIC_K_MEM_ADD_CMP_1 ; 
 scalar_t__ PI_ESIC_K_MEM_ADD_CMP_2 ; 
 scalar_t__ PI_ESIC_K_MEM_ADD_MASK_0 ; 
 scalar_t__ PI_ESIC_K_MEM_ADD_MASK_1 ; 
 scalar_t__ PI_ESIC_K_MEM_ADD_MASK_2 ; 
 int PI_MEM_ADD_MASK_M ; 
 int PI_TC_K_CSR_LEN ; 
 int PI_TC_K_CSR_OFFSET ; 
 int inb (scalar_t__) ; 
 int pci_resource_len (int /*<<< orphan*/ ,int) ; 
 int pci_resource_start (int /*<<< orphan*/ ,int) ; 
 TYPE_3__* to_eisa_device (struct device*) ; 
 int /*<<< orphan*/  to_pci_dev (struct device*) ; 
 TYPE_2__* to_tc_dev (struct device*) ; 

__attribute__((used)) static void dfx_get_bars(struct device *bdev,
			 resource_size_t *bar_start, resource_size_t *bar_len)
{
	int dfx_bus_pci = DFX_BUS_PCI(bdev);
	int dfx_bus_eisa = DFX_BUS_EISA(bdev);
	int dfx_bus_tc = DFX_BUS_TC(bdev);
	int dfx_use_mmio = DFX_MMIO || dfx_bus_tc;

	if (dfx_bus_pci) {
		int num = dfx_use_mmio ? 0 : 1;

		*bar_start = pci_resource_start(to_pci_dev(bdev), num);
		*bar_len = pci_resource_len(to_pci_dev(bdev), num);
	}
	if (dfx_bus_eisa) {
		unsigned long base_addr = to_eisa_device(bdev)->base_addr;
		resource_size_t bar;

		if (dfx_use_mmio) {
			bar = inb(base_addr + PI_ESIC_K_MEM_ADD_CMP_2);
			bar <<= 8;
			bar |= inb(base_addr + PI_ESIC_K_MEM_ADD_CMP_1);
			bar <<= 8;
			bar |= inb(base_addr + PI_ESIC_K_MEM_ADD_CMP_0);
			bar <<= 16;
			*bar_start = bar;
			bar = inb(base_addr + PI_ESIC_K_MEM_ADD_MASK_2);
			bar <<= 8;
			bar |= inb(base_addr + PI_ESIC_K_MEM_ADD_MASK_1);
			bar <<= 8;
			bar |= inb(base_addr + PI_ESIC_K_MEM_ADD_MASK_0);
			bar <<= 16;
			*bar_len = (bar | PI_MEM_ADD_MASK_M) + 1;
		} else {
			*bar_start = base_addr;
			*bar_len = PI_ESIC_K_CSR_IO_LEN;
		}
	}
	if (dfx_bus_tc) {
		*bar_start = to_tc_dev(bdev)->resource.start +
			     PI_TC_K_CSR_OFFSET;
		*bar_len = PI_TC_K_CSR_LEN;
	}
}