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
typedef  int /*<<< orphan*/  u8 ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  pin; } ;
struct acpi_prt_entry {int index; scalar_t__ link; } ;

/* Variables and functions */
 struct acpi_prt_entry* acpi_pci_irq_lookup (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int acpi_pci_link_free_irq (scalar_t__) ; 
 int /*<<< orphan*/  acpi_unregister_gsi (int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pin_name (int /*<<< orphan*/ ) ; 

void acpi_pci_irq_disable(struct pci_dev *dev)
{
	struct acpi_prt_entry *entry;
	int gsi;
	u8 pin;

	pin = dev->pin;
	if (!pin)
		return;

	entry = acpi_pci_irq_lookup(dev, pin);
	if (!entry)
		return;

	if (entry->link)
		gsi = acpi_pci_link_free_irq(entry->link);
	else
		gsi = entry->index;

	/*
	 * TBD: It might be worth clearing dev->irq by magic constant
	 * (e.g. PCI_UNDEFINED_IRQ).
	 */

	dev_info(&dev->dev, "PCI INT %c disabled\n", pin_name(pin));
	acpi_unregister_gsi(gsi);
}