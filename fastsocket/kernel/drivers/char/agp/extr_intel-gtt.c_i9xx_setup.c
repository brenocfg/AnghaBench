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
struct TYPE_2__ {int gtt_bus_addr; int /*<<< orphan*/  pcidev; int /*<<< orphan*/  registers; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  I915_MMADDR ; 
 int /*<<< orphan*/  I915_PTEADDR ; 
 int INTEL_GTT_GEN ; 
 int KB (int) ; 
 int /*<<< orphan*/  MB (int) ; 
 int /*<<< orphan*/  intel_i9xx_setup_flush () ; 
 TYPE_1__ intel_private ; 
 int /*<<< orphan*/  ioremap (int,int) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int i9xx_setup(void)
{
	u32 reg_addr, gtt_addr;
	int size = KB(512);

	pci_read_config_dword(intel_private.pcidev, I915_MMADDR, &reg_addr);

	reg_addr &= 0xfff80000;

	intel_private.registers = ioremap(reg_addr, size);
	if (!intel_private.registers)
		return -ENOMEM;

	switch (INTEL_GTT_GEN) {
	case 3:
		pci_read_config_dword(intel_private.pcidev,
				      I915_PTEADDR, &gtt_addr);
		intel_private.gtt_bus_addr = gtt_addr;
		break;
	case 5:
		intel_private.gtt_bus_addr = reg_addr + MB(2);
		break;
	default:
		intel_private.gtt_bus_addr = reg_addr + KB(512);
		break;
	}

	intel_i9xx_setup_flush();

	return 0;
}