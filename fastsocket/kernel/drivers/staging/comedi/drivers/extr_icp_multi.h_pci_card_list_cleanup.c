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
struct pcilst_struct {int /*<<< orphan*/  pcidev; struct pcilst_struct* next; } ;

/* Variables and functions */
 struct pcilst_struct* inova_devices ; 
 int /*<<< orphan*/  kfree (struct pcilst_struct*) ; 
 int /*<<< orphan*/  pci_dev_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pci_card_list_cleanup(unsigned short pci_vendor)
{
	struct pcilst_struct *inova, *next;

	for (inova = inova_devices; inova; inova = next) {
		next = inova->next;
		pci_dev_put(inova->pcidev);
		kfree(inova);
	}

	inova_devices = NULL;
}