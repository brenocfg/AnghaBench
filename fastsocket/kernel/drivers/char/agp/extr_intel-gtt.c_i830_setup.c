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
struct TYPE_2__ {scalar_t__ gtt_bus_addr; int /*<<< orphan*/  registers; int /*<<< orphan*/  pcidev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  I810_MMADDR ; 
 scalar_t__ I810_PTE_BASE ; 
 int /*<<< orphan*/  KB (int) ; 
 TYPE_1__ intel_private ; 
 int /*<<< orphan*/  ioremap (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int i830_setup(void)
{
	u32 reg_addr;

	pci_read_config_dword(intel_private.pcidev, I810_MMADDR, &reg_addr);
	reg_addr &= 0xfff80000;

	intel_private.registers = ioremap(reg_addr, KB(64));
	if (!intel_private.registers)
		return -ENOMEM;

	intel_private.gtt_bus_addr = reg_addr + I810_PTE_BASE;

	return 0;
}