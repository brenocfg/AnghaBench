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
typedef  size_t u8 ;
struct pci_func {int configured; struct pci_func* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct pci_func** cpqhp_slot_list ; 
 struct pci_func* kzalloc (int,int /*<<< orphan*/ ) ; 

struct pci_func *cpqhp_slot_create(u8 busnumber)
{
	struct pci_func *new_slot;
	struct pci_func *next;

	new_slot = kzalloc(sizeof(*new_slot), GFP_KERNEL);
	if (new_slot == NULL)
		return new_slot;

	new_slot->next = NULL;
	new_slot->configured = 1;

	if (cpqhp_slot_list[busnumber] == NULL) {
		cpqhp_slot_list[busnumber] = new_slot;
	} else {
		next = cpqhp_slot_list[busnumber];
		while (next->next != NULL)
			next = next->next;
		next->next = new_slot;
	}
	return new_slot;
}