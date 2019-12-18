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
 struct pcilst_struct* inova_devices ; 

__attribute__((used)) static int find_free_pci_card_by_position(unsigned short vendor_id,
					  unsigned short device_id,
					  unsigned short pci_bus,
					  unsigned short pci_slot,
					  struct pcilst_struct **card)
{
	struct pcilst_struct *inova, *next;

	*card = NULL;
	for (inova = inova_devices; inova; inova = next) {
		next = inova->next;
		if ((inova->vendor == vendor_id) && (inova->device == device_id)
		    && (inova->pci_bus == pci_bus)
		    && (inova->pci_slot == pci_slot)) {
			if (!(inova->used)) {
				*card = inova;
				return 0;	/* ok, card is found */
			} else {
				return 2;	/* card exist but is used */
			}
		}
	}

	return 1;		/* no card found */
}