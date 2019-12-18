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
struct pci_resource {struct pci_resource* next; } ;

/* Variables and functions */

__attribute__((used)) static inline void return_resource(struct pci_resource **head,
				   struct pci_resource *node)
{
	if (!node || !head)
		return;
	node->next = *head;
	*head = node;
}