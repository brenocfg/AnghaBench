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
struct pcilst_struct {struct pcilst_struct* next; } ;

/* Variables and functions */
 struct pcilst_struct* amcc_devices ; 
 int /*<<< orphan*/  kfree (struct pcilst_struct*) ; 

void v_pci_card_list_cleanup(unsigned short pci_vendor)
{
	struct pcilst_struct *amcc, *next;

	for (amcc = amcc_devices; amcc; amcc = next) {
		next = amcc->next;
		kfree(amcc);
	}

	amcc_devices = NULL;
}