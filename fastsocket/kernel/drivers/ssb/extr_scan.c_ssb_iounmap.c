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
struct ssb_bus {int bustype; int /*<<< orphan*/ * mapped_device; int /*<<< orphan*/ * mmio; int /*<<< orphan*/  host_pci; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSB_BUG_ON (int) ; 
#define  SSB_BUSTYPE_PCI 131 
#define  SSB_BUSTYPE_PCMCIA 130 
#define  SSB_BUSTYPE_SDIO 129 
#define  SSB_BUSTYPE_SSB 128 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_iounmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ssb_iounmap(struct ssb_bus *bus)
{
	switch (bus->bustype) {
	case SSB_BUSTYPE_SSB:
	case SSB_BUSTYPE_PCMCIA:
		iounmap(bus->mmio);
		break;
	case SSB_BUSTYPE_PCI:
#ifdef CONFIG_SSB_PCIHOST
		pci_iounmap(bus->host_pci, bus->mmio);
#else
		SSB_BUG_ON(1); /* Can't reach this code. */
#endif
		break;
	case SSB_BUSTYPE_SDIO:
		break;
	}
	bus->mmio = NULL;
	bus->mapped_device = NULL;
}