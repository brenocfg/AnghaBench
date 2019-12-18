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
typedef  int u32 ;
struct pci_resource {int length; int base; struct pci_resource* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ cpqhp_resource_sort_and_combine (struct pci_resource**) ; 
 struct pci_resource* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ sort_by_max_size (struct pci_resource**) ; 

__attribute__((used)) static struct pci_resource *get_max_resource(struct pci_resource **head, u32 size)
{
	struct pci_resource *max;
	struct pci_resource *temp;
	struct pci_resource *split_node;
	u32 temp_dword;

	if (cpqhp_resource_sort_and_combine(head))
		return NULL;

	if (sort_by_max_size(head))
		return NULL;

	for (max = *head; max; max = max->next) {
		/* If not big enough we could probably just bail,
		 * instead we'll continue to the next.
		 */
		if (max->length < size)
			continue;

		if (max->base & (size - 1)) {
			/* this one isn't base aligned properly
			 * so we'll make a new entry and split it up
			 */
			temp_dword = (max->base | (size-1)) + 1;

			/* Short circuit if adjusted size is too small */
			if ((max->length - (temp_dword - max->base)) < size)
				continue;

			split_node = kmalloc(sizeof(*split_node), GFP_KERNEL);

			if (!split_node)
				return NULL;

			split_node->base = max->base;
			split_node->length = temp_dword - max->base;
			max->base = temp_dword;
			max->length -= split_node->length;

			split_node->next = max->next;
			max->next = split_node;
		}

		if ((max->base + max->length) & (size - 1)) {
			/* this one isn't end aligned properly at the top
			 * so we'll make a new entry and split it up
			 */
			split_node = kmalloc(sizeof(*split_node), GFP_KERNEL);

			if (!split_node)
				return NULL;
			temp_dword = ((max->base + max->length) & ~(size - 1));
			split_node->base = temp_dword;
			split_node->length = max->length + max->base
					     - split_node->base;
			max->length -= split_node->length;

			split_node->next = max->next;
			max->next = split_node;
		}

		/* Make sure it didn't shrink too much when we aligned it */
		if (max->length < size)
			continue;

		/* Now take it out of the list */
		temp = *head;
		if (temp == max) {
			*head = max->next;
		} else {
			while (temp && temp->next != max) {
				temp = temp->next;
			}

			temp->next = max->next;
		}

		max->next = NULL;
		break;
	}

	return max;
}