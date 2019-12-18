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
struct resource_list_x {struct resource_list_x* next; int /*<<< orphan*/  add_size; int /*<<< orphan*/  flags; int /*<<< orphan*/  end; int /*<<< orphan*/  start; struct pci_dev* dev; struct resource* res; } ;
struct resource {int /*<<< orphan*/  flags; int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct pci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct resource_list_x* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 

__attribute__((used)) static void add_to_list(struct resource_list_x *head,
		 struct pci_dev *dev, struct resource *res,
		 resource_size_t add_size)
{
	struct resource_list_x *list = head;
	struct resource_list_x *ln = list->next;
	struct resource_list_x *tmp;

	tmp = kmalloc(sizeof(*tmp), GFP_KERNEL);
	if (!tmp) {
		pr_warning("add_to_list: kmalloc() failed!\n");
		return;
	}

	tmp->next = ln;
	tmp->res = res;
	tmp->dev = dev;
	tmp->start = res->start;
	tmp->end = res->end;
	tmp->flags = res->flags;
	tmp->add_size = add_size;
	list->next = tmp;
}