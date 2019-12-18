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
struct resource_list {struct resource_list* next; struct pci_dev* dev; struct resource* res; } ;
struct resource {int flags; scalar_t__ parent; } ;
struct pci_dev {int /*<<< orphan*/  dev; struct resource* resource; } ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IORESOURCE_PCI_FIXED ; 
 int PCI_NUM_RESOURCES ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,struct resource*) ; 
 struct resource_list* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ pci_resource_alignment (struct pci_dev*,struct resource*) ; 

void pdev_sort_resources(struct pci_dev *dev, struct resource_list *head)
{
	int i;

	for (i = 0; i < PCI_NUM_RESOURCES; i++) {
		struct resource *r;
		struct resource_list *list, *tmp;
		resource_size_t r_align;

		r = &dev->resource[i];

		if (r->flags & IORESOURCE_PCI_FIXED)
			continue;

		if (!(r->flags) || r->parent)
			continue;

		r_align = pci_resource_alignment(dev, r);
		if (!r_align) {
			dev_warn(&dev->dev, "BAR %d: %pR has bogus alignment\n",
				 i, r);
			continue;
		}
		for (list = head; ; list = list->next) {
			resource_size_t align = 0;
			struct resource_list *ln = list->next;

			if (ln)
				align = pci_resource_alignment(ln->dev, ln->res);

			if (r_align > align) {
				tmp = kmalloc(sizeof(*tmp), GFP_KERNEL);
				if (!tmp)
					panic("pdev_sort_resources(): "
					      "kmalloc() failed!\n");
				tmp->next = ln;
				tmp->res = r;
				tmp->dev = dev;
				list->next = tmp;
				break;
			}
		}
	}
}