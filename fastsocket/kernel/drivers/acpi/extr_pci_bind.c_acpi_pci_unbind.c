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
struct pci_dev {int /*<<< orphan*/  subordinate; } ;
struct TYPE_2__ {int /*<<< orphan*/ * unbind; int /*<<< orphan*/ * bind; } ;
struct acpi_device {TYPE_1__ ops; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 struct pci_dev* acpi_get_pci_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_pci_irq_del_prt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 

__attribute__((used)) static int acpi_pci_unbind(struct acpi_device *device)
{
	struct pci_dev *dev;

	dev = acpi_get_pci_dev(device->handle);
	if (!dev || !dev->subordinate)
		goto out;

	acpi_pci_irq_del_prt(dev->subordinate);

	device->ops.bind = NULL;
	device->ops.unbind = NULL;

out:
	pci_dev_put(dev);
	return 0;
}