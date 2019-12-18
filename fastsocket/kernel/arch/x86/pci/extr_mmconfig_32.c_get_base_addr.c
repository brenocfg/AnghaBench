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
typedef  int /*<<< orphan*/  u32 ;
struct acpi_mcfg_allocation {unsigned int pci_segment; int start_bus_number; int end_bus_number; int /*<<< orphan*/  address; } ;

/* Variables and functions */
 struct acpi_mcfg_allocation* pci_mmcfg_config ; 
 int pci_mmcfg_config_num ; 

__attribute__((used)) static u32 get_base_addr(unsigned int seg, int bus, unsigned devfn)
{
	struct acpi_mcfg_allocation *cfg;
	int cfg_num;

	for (cfg_num = 0; cfg_num < pci_mmcfg_config_num; cfg_num++) {
		cfg = &pci_mmcfg_config[cfg_num];
		if (cfg->pci_segment == seg &&
		    (cfg->start_bus_number <= bus) &&
		    (cfg->end_bus_number >= bus))
			return cfg->address;
	}

	/* Fall back to type 0 */
	return 0;
}