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
struct pcilst_struct {unsigned short vendor; unsigned short device; unsigned short pci_bus; unsigned short pci_slot; int /*<<< orphan*/  used; struct pcilst_struct* next; } ;

/* Variables and functions */
 struct pcilst_struct* amcc_devices ; 
 int /*<<< orphan*/  printk (char*,unsigned short,unsigned short) ; 

int i_find_free_pci_card_by_position(unsigned short vendor_id,
				     unsigned short device_id,
				     unsigned short pci_bus,
				     unsigned short pci_slot,
				     struct pcilst_struct **card)
{
	struct pcilst_struct *amcc, *next;

	*card = NULL;
	for (amcc = amcc_devices; amcc; amcc = next) {
		next = amcc->next;
		if ((amcc->vendor == vendor_id) && (amcc->device == device_id)
		    && (amcc->pci_bus == pci_bus)
		    && (amcc->pci_slot == pci_slot)) {
			if (!(amcc->used)) {
				*card = amcc;
				return 0;	/* ok, card is found */
			} else {
				printk(" - \nCard on requested position is used b:s %d:%d!\n",
					  pci_bus, pci_slot);
				return 2;	/* card exist but is used */
			}
		}
	}

	/* no card found */
	return 1;
}