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
typedef  unsigned int u32 ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ ACPI_IRQ_MODEL_IOAPIC ; 
 scalar_t__ ACPI_IRQ_MODEL_PIC ; 
 int ACPI_LEVEL_SENSITIVE ; 
 scalar_t__ acpi_irq_model ; 
 int /*<<< orphan*/  eisa_set_level_irq (unsigned int) ; 
 unsigned int mp_register_gsi (struct device*,unsigned int,int,int) ; 

int acpi_register_gsi(struct device *dev, u32 gsi, int trigger, int polarity)
{
	unsigned int irq;
	unsigned int plat_gsi = gsi;

#ifdef CONFIG_PCI
	/*
	 * Make sure all (legacy) PCI IRQs are set as level-triggered.
	 */
	if (acpi_irq_model == ACPI_IRQ_MODEL_PIC) {
		if (trigger == ACPI_LEVEL_SENSITIVE)
			eisa_set_level_irq(gsi);
	}
#endif

#ifdef CONFIG_X86_IO_APIC
	if (acpi_irq_model == ACPI_IRQ_MODEL_IOAPIC) {
		plat_gsi = mp_register_gsi(dev, gsi, trigger, polarity);
	}
#endif
	irq = plat_gsi;

	return irq;
}