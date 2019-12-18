#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * prev; int /*<<< orphan*/  next; } ;
struct pci_dev {TYPE_1__ bus_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_bus_sem ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_free_resources (struct pci_dev*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pci_destroy_dev(struct pci_dev *dev)
{
	/* Remove the device from the device lists, and prevent any further
	 * list accesses from this device */
	down_write(&pci_bus_sem);
	list_del(&dev->bus_list);
	dev->bus_list.next = dev->bus_list.prev = NULL;
	up_write(&pci_bus_sem);

	pci_free_resources(dev);
	pci_dev_put(dev);
}