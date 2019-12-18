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
struct irte {int present; int vector; unsigned int dest; int mask; int trigger; int polarity; int /*<<< orphan*/  dest_mode; int /*<<< orphan*/  delivery_mode; int /*<<< orphan*/  dest_id; int /*<<< orphan*/  dlvry_mode; scalar_t__ trigger_mode; int /*<<< orphan*/  dst_mode; } ;
struct intel_iommu {int dummy; } ;
struct IR_IO_APIC_route_entry {int index2; int format; int index; int vector; scalar_t__ zero; } ;
struct IO_APIC_route_entry {int present; int vector; unsigned int dest; int mask; int trigger; int polarity; int /*<<< orphan*/  dest_mode; int /*<<< orphan*/  delivery_mode; int /*<<< orphan*/  dest_id; int /*<<< orphan*/  dlvry_mode; scalar_t__ trigger_mode; int /*<<< orphan*/  dst_mode; } ;
typedef  int /*<<< orphan*/  irte ;
struct TYPE_2__ {int /*<<< orphan*/  irq_dest_mode; int /*<<< orphan*/  irq_delivery_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRTE_DEST (unsigned int) ; 
 int alloc_irte (struct intel_iommu*,int,int) ; 
 TYPE_1__* apic ; 
 scalar_t__ intr_remapping_enabled ; 
 struct intel_iommu* map_ioapic_to_ir (int) ; 
 int /*<<< orphan*/  memset (struct irte*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  modify_irte (int,struct irte*) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  set_ioapic_sid (struct irte*,int) ; 

int setup_ioapic_entry(int apic_id, int irq,
		       struct IO_APIC_route_entry *entry,
		       unsigned int destination, int trigger,
		       int polarity, int vector, int pin)
{
	/*
	 * add it to the IO-APIC irq-routing table:
	 */
	memset(entry,0,sizeof(*entry));

	if (intr_remapping_enabled) {
		struct intel_iommu *iommu = map_ioapic_to_ir(apic_id);
		struct irte irte;
		struct IR_IO_APIC_route_entry *ir_entry =
			(struct IR_IO_APIC_route_entry *) entry;
		int index;

		if (!iommu)
			panic("No mapping iommu for ioapic %d\n", apic_id);

		index = alloc_irte(iommu, irq, 1);
		if (index < 0)
			panic("Failed to allocate IRTE for ioapic %d\n", apic_id);

		memset(&irte, 0, sizeof(irte));

		irte.present = 1;
		irte.dst_mode = apic->irq_dest_mode;
		/*
		 * Trigger mode in the IRTE will always be edge, and the
		 * actual level or edge trigger will be setup in the IO-APIC
		 * RTE. This will help simplify level triggered irq migration.
		 * For more details, see the comments above explainig IO-APIC
		 * irq migration in the presence of interrupt-remapping.
		 */
		irte.trigger_mode = 0;
		irte.dlvry_mode = apic->irq_delivery_mode;
		irte.vector = vector;
		irte.dest_id = IRTE_DEST(destination);

		/* Set source-id of interrupt request */
		set_ioapic_sid(&irte, apic_id);

		modify_irte(irq, &irte);

		ir_entry->index2 = (index >> 15) & 0x1;
		ir_entry->zero = 0;
		ir_entry->format = 1;
		ir_entry->index = (index & 0x7fff);
		/*
		 * IO-APIC RTE will be configured with virtual vector.
		 * irq handler will do the explicit EOI to the io-apic.
		 */
		ir_entry->vector = pin;
	} else {
		entry->delivery_mode = apic->irq_delivery_mode;
		entry->dest_mode = apic->irq_dest_mode;
		entry->dest = destination;
		entry->vector = vector;
	}

	entry->mask = 0;				/* enable IRQ */
	entry->trigger = trigger;
	entry->polarity = polarity;

	/* Mask level triggered irqs.
	 * Use IRQ_DELAYED_DISABLE for edge triggered irqs.
	 */
	if (trigger)
		entry->mask = 1;
	return 0;
}