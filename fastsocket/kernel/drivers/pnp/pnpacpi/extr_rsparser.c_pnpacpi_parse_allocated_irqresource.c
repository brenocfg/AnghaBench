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
struct pnp_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ACPI_ACTIVE_HIGH ; 
 int ACPI_ACTIVE_LOW ; 
 int ACPI_EDGE_SENSITIVE ; 
 int ACPI_LEVEL_SENSITIVE ; 
 int IORESOURCE_DISABLED ; 
 int /*<<< orphan*/  acpi_get_override_irq (int,int*,int*) ; 
 int acpi_register_gsi (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,char*,char*) ; 
 int irq_flags (int,int,int) ; 
 int /*<<< orphan*/  pcibios_penalize_isa_irq (int,int) ; 
 int /*<<< orphan*/  pnp_add_irq_resource (struct pnp_dev*,int,int) ; 
 int /*<<< orphan*/  valid_IRQ (int) ; 

__attribute__((used)) static void pnpacpi_parse_allocated_irqresource(struct pnp_dev *dev,
						u32 gsi, int triggering,
						int polarity, int shareable)
{
	int irq, flags;
	int p, t;

	if (!valid_IRQ(gsi)) {
		pnp_add_irq_resource(dev, gsi, IORESOURCE_DISABLED);
		return;
	}

	/*
	 * in IO-APIC mode, use overrided attribute. Two reasons:
	 * 1. BIOS bug in DSDT
	 * 2. BIOS uses IO-APIC mode Interrupt Source Override
	 */
	if (!acpi_get_override_irq(gsi, &t, &p)) {
		t = t ? ACPI_LEVEL_SENSITIVE : ACPI_EDGE_SENSITIVE;
		p = p ? ACPI_ACTIVE_LOW : ACPI_ACTIVE_HIGH;

		if (triggering != t || polarity != p) {
			dev_warn(&dev->dev, "IRQ %d override to %s, %s\n",
				gsi, t ? "edge":"level", p ? "low":"high");
			triggering = t;
			polarity = p;
		}
	}

	flags = irq_flags(triggering, polarity, shareable);
	irq = acpi_register_gsi(&dev->dev, gsi, triggering, polarity);
	if (irq >= 0)
		pcibios_penalize_isa_irq(irq, 1);
	else
		flags |= IORESOURCE_DISABLED;

	pnp_add_irq_resource(dev, irq, flags);
}