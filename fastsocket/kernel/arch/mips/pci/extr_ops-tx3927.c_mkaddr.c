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
struct pci_bus {int number; int /*<<< orphan*/ * parent; } ;
struct TYPE_2__ {int ica; int /*<<< orphan*/  pcistatim; int /*<<< orphan*/  pcistat; } ;

/* Variables and functions */
 unsigned char PCI_DEVFN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_STATUS_REC_MASTER_ABORT ; 
 int /*<<< orphan*/  TX3927_PCIC_MAX_DEVNU ; 
 TYPE_1__* tx3927_pcicptr ; 

__attribute__((used)) static int mkaddr(struct pci_bus *bus, unsigned char devfn, unsigned char where)
{
	if (bus->parent == NULL &&
	    devfn >= PCI_DEVFN(TX3927_PCIC_MAX_DEVNU, 0))
		return -1;
	tx3927_pcicptr->ica =
		((bus->number & 0xff) << 0x10) |
		((devfn & 0xff) << 0x08) |
		(where & 0xfc) | (bus->parent ? 1 : 0);

	/* clear M_ABORT and Disable M_ABORT Int. */
	tx3927_pcicptr->pcistat |= PCI_STATUS_REC_MASTER_ABORT;
	tx3927_pcicptr->pcistatim &= ~PCI_STATUS_REC_MASTER_ABORT;
	return 0;
}