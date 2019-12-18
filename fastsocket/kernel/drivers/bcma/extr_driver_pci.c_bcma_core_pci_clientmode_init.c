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
struct bcma_drv_pci {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcma_core_pci_config_fixup (struct bcma_drv_pci*) ; 
 int /*<<< orphan*/  bcma_core_pci_fixcfg (struct bcma_drv_pci*) ; 
 int /*<<< orphan*/  bcma_pcicore_serdes_workaround (struct bcma_drv_pci*) ; 

__attribute__((used)) static void bcma_core_pci_clientmode_init(struct bcma_drv_pci *pc)
{
	bcma_core_pci_fixcfg(pc);
	bcma_pcicore_serdes_workaround(pc);
	bcma_core_pci_config_fixup(pc);
}