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
struct pcilst_struct {unsigned short device; unsigned short vendor; int /*<<< orphan*/  used; struct pcilst_struct* next; } ;

/* Variables and functions */
 struct pcilst_struct* inova_devices ; 

__attribute__((used)) static struct pcilst_struct *find_free_pci_card_by_device(unsigned short
							  vendor_id,
							  unsigned short
							  device_id)
{
	struct pcilst_struct *inova, *next;

	for (inova = inova_devices; inova; inova = next) {
		next = inova->next;
		if ((!inova->used) && (inova->device == device_id)
		    && (inova->vendor == vendor_id))
			return inova;

	}

	return NULL;
}