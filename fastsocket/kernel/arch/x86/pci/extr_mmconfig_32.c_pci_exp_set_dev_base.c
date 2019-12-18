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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  FIX_PCIE_MCFG ; 
 int mmcfg_last_accessed_cpu ; 
 scalar_t__ mmcfg_last_accessed_device ; 
 int /*<<< orphan*/  set_fixmap_nocache (int /*<<< orphan*/ ,scalar_t__) ; 
 int smp_processor_id () ; 

__attribute__((used)) static void pci_exp_set_dev_base(unsigned int base, int bus, int devfn)
{
	u32 dev_base = base | (bus << 20) | (devfn << 12);
	int cpu = smp_processor_id();
	if (dev_base != mmcfg_last_accessed_device ||
	    cpu != mmcfg_last_accessed_cpu) {
		mmcfg_last_accessed_device = dev_base;
		mmcfg_last_accessed_cpu = cpu;
		set_fixmap_nocache(FIX_PCIE_MCFG, dev_base);
	}
}