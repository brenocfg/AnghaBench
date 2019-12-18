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
 scalar_t__ sort_by_size (struct pci_resource**) ; 

__attribute__((used)) static struct pci_resource *get_io_resource(struct pci_resource **head, u32 size)
{
	struct pci_resource *prevnode;
	struct pci_resource *node;
	struct pci_resource *split_node;
	u32 temp_dword;

	if (!(*head))
		return NULL;

	if (cpqhp_resource_sort_and_combine(head))
		return NULL;

	if (sort_by_size(head))
		return NULL;

	for (node = *head; node; node = node->next) {
		if (node->length < size)
			continue;

		if (node->base & (size - 1)) {
			/* this one isn't base aligned properly
			 * so we'll make a new entry and split it up
			 */
			temp_dword = (node->base | (size-1)) + 1;

			/* Short circuit if adjusted size is too small */
			if ((node->length - (temp_dword - node->base)) < size)
				continue;

			split_node = kmalloc(sizeof(*split_node), GFP_KERNEL);

			if (!split_node)
				return NULL;

			split_node->base = node->base;
			split_node->length = temp_dword - node->base;
			node->base = temp_dword;
			node->length -= split_node->length;

			/* Put it in the list */
			split_node->next = node->next;
			node->next = split_node;
		} /* End of non-aligned base */

		/* Don't need to check if too small since we already did */
		if (node->length > size) {
			/* this one is longer than we need
			 * so we'll make a new entry and split it up
			 */
			split_node = kmalloc(sizeof(*split_node), GFP_KERNEL);

			if (!split_node)
				return NULL;

			split_node->base = node->base + size;
			split_node->length = node->length - size;
			node->length = size;

			/* Put it in the list */
			split_node->next = node->next;
			node->next = split_node;
		}  /* End of too big on top end */

		/* For IO make sure it's not in the ISA aliasing space */
		if (node->base & 0x300L)
			continue;

		/* If we got here, then it is the right size
		 * Now take it out of the list and break
		 */
		if (*head == node) {
			*head = node->next;
		} else {
			prevnode = *head;
			while (prevnode->next != node)
				prevnode = prevnode->next;

			prevnode->next = node->next;
		}
		node->next = NULL;
		break;
	}

	return node;
}