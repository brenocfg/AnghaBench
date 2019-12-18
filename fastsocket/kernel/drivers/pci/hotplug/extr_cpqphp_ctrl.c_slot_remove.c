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
struct pci_func {size_t bus; struct pci_func* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpqhp_destroy_board_resources (struct pci_func*) ; 
 struct pci_func** cpqhp_slot_list ; 
 int /*<<< orphan*/  kfree (struct pci_func*) ; 

__attribute__((used)) static int slot_remove(struct pci_func * old_slot)
{
	struct pci_func *next;

	if (old_slot == NULL)
		return 1;

	next = cpqhp_slot_list[old_slot->bus];
	if (next == NULL)
		return 1;

	if (next == old_slot) {
		cpqhp_slot_list[old_slot->bus] = old_slot->next;
		cpqhp_destroy_board_resources(old_slot);
		kfree(old_slot);
		return 0;
	}

	while ((next->next != old_slot) && (next->next != NULL))
		next = next->next;

	if (next->next == old_slot) {
		next->next = old_slot->next;
		cpqhp_destroy_board_resources(old_slot);
		kfree(old_slot);
		return 0;
	} else
		return 2;
}