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
struct irq_desc {int depth; int /*<<< orphan*/ * chip; scalar_t__ action; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int CO_APIC_LAST ; 
 int CO_IRQ_8259 ; 
 int CO_IRQ_APIC0 ; 
 int CO_IRQ_IDE0 ; 
 int CO_IRQ_IDE1 ; 
 int /*<<< orphan*/  IRQ_DISABLED ; 
 scalar_t__ IS_CO_APIC (int) ; 
 int /*<<< orphan*/  cascade_action ; 
 int /*<<< orphan*/  cobalt_irq_type ; 
 struct irq_desc* irq_to_desc (int) ; 
 int /*<<< orphan*/  master_action ; 
 int /*<<< orphan*/  piix4_master_irq_type ; 
 int /*<<< orphan*/  piix4_virtual_irq_type ; 
 int /*<<< orphan*/  setup_irq (int,int /*<<< orphan*/ *) ; 

void init_VISWS_APIC_irqs(void)
{
	int i;

	for (i = 0; i < CO_IRQ_APIC0 + CO_APIC_LAST + 1; i++) {
		struct irq_desc *desc = irq_to_desc(i);

		desc->status = IRQ_DISABLED;
		desc->action = 0;
		desc->depth = 1;

		if (i == 0) {
			desc->chip = &cobalt_irq_type;
		}
		else if (i == CO_IRQ_IDE0) {
			desc->chip = &cobalt_irq_type;
		}
		else if (i == CO_IRQ_IDE1) {
			desc->chip = &cobalt_irq_type;
		}
		else if (i == CO_IRQ_8259) {
			desc->chip = &piix4_master_irq_type;
		}
		else if (i < CO_IRQ_APIC0) {
			desc->chip = &piix4_virtual_irq_type;
		}
		else if (IS_CO_APIC(i)) {
			desc->chip = &cobalt_irq_type;
		}
	}

	setup_irq(CO_IRQ_8259, &master_action);
	setup_irq(2, &cascade_action);
}