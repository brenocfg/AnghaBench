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
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
struct bcma_device {TYPE_1__ id; TYPE_2__* bus; int /*<<< orphan*/  wrap; int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {struct bcma_device* mapped_core; int /*<<< orphan*/  host_pci; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_PCI_BAR0_WIN ; 
 int /*<<< orphan*/  BCMA_PCI_BAR0_WIN2 ; 
 int /*<<< orphan*/  bcma_debug (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcma_host_pci_switch_core(struct bcma_device *core)
{
	pci_write_config_dword(core->bus->host_pci, BCMA_PCI_BAR0_WIN,
			       core->addr);
	pci_write_config_dword(core->bus->host_pci, BCMA_PCI_BAR0_WIN2,
			       core->wrap);
	core->bus->mapped_core = core;
	bcma_debug(core->bus, "Switched to core: 0x%X\n", core->id.id);
}