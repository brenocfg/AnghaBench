#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
struct nouveau_pll_vals {int dummy; } ;
struct drm_device {int pci_device; } ;
typedef  enum nvbios_pll_type { ____Placeholder_nvbios_pll_type } nvbios_pll_type ;

/* Variables and functions */
 int CHIPSET_NFORCE ; 
 int CHIPSET_NFORCE2 ; 
 int PLL_MEMORY ; 
 int nouveau_hw_get_pllvals (struct drm_device*,int,struct nouveau_pll_vals*) ; 
 int nouveau_hw_pllvals_to_clk (struct nouveau_pll_vals*) ; 
 int /*<<< orphan*/  pci_get_bus_and_slot (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int,int*) ; 

int
nouveau_hw_get_clock(struct drm_device *dev, enum nvbios_pll_type plltype)
{
	struct nouveau_pll_vals pllvals;
	int ret;

	if (plltype == PLL_MEMORY &&
	    (dev->pci_device & 0x0ff0) == CHIPSET_NFORCE) {
		uint32_t mpllP;

		pci_read_config_dword(pci_get_bus_and_slot(0, 3), 0x6c, &mpllP);
		if (!mpllP)
			mpllP = 4;

		return 400000 / mpllP;
	} else
	if (plltype == PLL_MEMORY &&
	    (dev->pci_device & 0xff0) == CHIPSET_NFORCE2) {
		uint32_t clock;

		pci_read_config_dword(pci_get_bus_and_slot(0, 5), 0x4c, &clock);
		return clock;
	}

	ret = nouveau_hw_get_pllvals(dev, plltype, &pllvals);
	if (ret)
		return ret;

	return nouveau_hw_pllvals_to_clk(&pllvals);
}