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
struct irq_desc {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 unsigned long IOAPIC_AUTO ; 
 unsigned long IOAPIC_LEVEL ; 
 scalar_t__ IO_APIC_irq_trigger (int) ; 
 int /*<<< orphan*/  IRQ_LEVEL ; 
 int /*<<< orphan*/  IRQ_MOVE_PCNTXT ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_fasteoi_irq ; 
 int /*<<< orphan*/  ioapic_chip ; 
 int /*<<< orphan*/  ir_ioapic_chip ; 
 scalar_t__ irq_remapped (int) ; 
 int /*<<< orphan*/  set_irq_chip_and_handler_name (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void ioapic_register_intr(int irq, struct irq_desc *desc, unsigned long trigger)
{

	if ((trigger == IOAPIC_AUTO && IO_APIC_irq_trigger(irq)) ||
	    trigger == IOAPIC_LEVEL)
		desc->status |= IRQ_LEVEL;
	else
		desc->status &= ~IRQ_LEVEL;

	if (irq_remapped(irq)) {
		desc->status |= IRQ_MOVE_PCNTXT;
		if (trigger)
			set_irq_chip_and_handler_name(irq, &ir_ioapic_chip,
						      handle_fasteoi_irq,
						     "fasteoi");
		else
			set_irq_chip_and_handler_name(irq, &ir_ioapic_chip,
						      handle_edge_irq, "edge");
		return;
	}

	if ((trigger == IOAPIC_AUTO && IO_APIC_irq_trigger(irq)) ||
	    trigger == IOAPIC_LEVEL)
		set_irq_chip_and_handler_name(irq, &ioapic_chip,
					      handle_fasteoi_irq,
					      "fasteoi");
	else
		set_irq_chip_and_handler_name(irq, &ioapic_chip,
					      handle_edge_irq, "edge");
}