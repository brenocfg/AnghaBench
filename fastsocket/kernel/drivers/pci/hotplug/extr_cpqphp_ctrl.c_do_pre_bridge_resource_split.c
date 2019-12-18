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
struct pci_resource {scalar_t__ base; scalar_t__ length; struct pci_resource* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int cpqhp_resource_sort_and_combine (struct pci_resource**) ; 
 int /*<<< orphan*/  dbg (char*) ; 
 struct pci_resource* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pci_resource *do_pre_bridge_resource_split(struct pci_resource **head,
				struct pci_resource **orig_head, u32 alignment)
{
	struct pci_resource *prevnode = NULL;
	struct pci_resource *node;
	struct pci_resource *split_node;
	u32 rc;
	u32 temp_dword;
	dbg("do_pre_bridge_resource_split\n");

	if (!(*head) || !(*orig_head))
		return NULL;

	rc = cpqhp_resource_sort_and_combine(head);

	if (rc)
		return NULL;

	if ((*head)->base != (*orig_head)->base)
		return NULL;

	if ((*head)->length == (*orig_head)->length)
		return NULL;


	/* If we got here, there the bridge requires some of the resource, but
	 * we may be able to split some off of the front
	 */

	node = *head;

	if (node->length & (alignment -1)) {
		/* this one isn't an aligned length, so we'll make a new entry
		 * and split it up.
		 */
		split_node = kmalloc(sizeof(*split_node), GFP_KERNEL);

		if (!split_node)
			return NULL;

		temp_dword = (node->length | (alignment-1)) + 1 - alignment;

		split_node->base = node->base;
		split_node->length = temp_dword;

		node->length -= temp_dword;
		node->base += split_node->length;

		/* Put it in the list */
		*head = split_node;
		split_node->next = node;
	}

	if (node->length < alignment)
		return NULL;

	/* Now unlink it */
	if (*head == node) {
		*head = node->next;
	} else {
		prevnode = *head;
		while (prevnode->next != node)
			prevnode = prevnode->next;

		prevnode->next = node->next;
	}
	node->next = NULL;

	return node;
}