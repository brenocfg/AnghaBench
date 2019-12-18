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
typedef  int u8 ;
struct pci_dev {int class; int pin; int /*<<< orphan*/  dev; TYPE_1__* bus; } ;
struct acpi_prt_entry {int dummy; } ;
struct TYPE_2__ {struct pci_dev* self; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int PCI_CLASS_BRIDGE_CARDBUS ; 
 struct acpi_prt_entry* acpi_pci_irq_find_prt_entry (struct pci_dev*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int pci_swizzle_interrupt_pin (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pin_name (int) ; 

__attribute__((used)) static struct acpi_prt_entry *acpi_pci_irq_lookup(struct pci_dev *dev, int pin)
{
	struct acpi_prt_entry *entry;
	struct pci_dev *bridge;
	u8 bridge_pin, orig_pin = pin;

	entry = acpi_pci_irq_find_prt_entry(dev, pin);
	if (entry) {
		ACPI_DEBUG_PRINT((ACPI_DB_INFO, "Found %s[%c] _PRT entry\n",
				  pci_name(dev), pin_name(pin)));
		return entry;
	}

	/* 
	 * Attempt to derive an IRQ for this device from a parent bridge's
	 * PCI interrupt routing entry (eg. yenta bridge and add-in card bridge).
	 */
	bridge = dev->bus->self;
	while (bridge) {
		pin = pci_swizzle_interrupt_pin(dev, pin);

		if ((bridge->class >> 8) == PCI_CLASS_BRIDGE_CARDBUS) {
			/* PC card has the same IRQ as its cardbridge */
			bridge_pin = bridge->pin;
			if (!bridge_pin) {
				ACPI_DEBUG_PRINT((ACPI_DB_INFO,
						  "No interrupt pin configured for device %s\n",
						  pci_name(bridge)));
				return NULL;
			}
			pin = bridge_pin;
		}

		entry = acpi_pci_irq_find_prt_entry(bridge, pin);
		if (entry) {
			ACPI_DEBUG_PRINT((ACPI_DB_INFO,
					 "Derived GSI for %s INT %c from %s\n",
					 pci_name(dev), pin_name(orig_pin),
					 pci_name(bridge)));
			return entry;
		}

		dev = bridge;
		bridge = dev->bus->self;
	}

	dev_warn(&dev->dev, "can't derive routing for PCI INT %c\n",
		 pin_name(orig_pin));
	return NULL;
}