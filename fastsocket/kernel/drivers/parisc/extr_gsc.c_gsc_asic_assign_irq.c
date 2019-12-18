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
struct gsc_asic {int* global_irq; } ;

/* Variables and functions */
 int NO_IRQ ; 
 int /*<<< orphan*/  gsc_asic_interrupt_type ; 
 int gsc_assign_irq (int /*<<< orphan*/ *,struct gsc_asic*) ; 

void gsc_asic_assign_irq(struct gsc_asic *asic, int local_irq, int *irqp)
{
	int irq = asic->global_irq[local_irq];
	
	if (irq <= 0) {
		irq = gsc_assign_irq(&gsc_asic_interrupt_type, asic);
		if (irq == NO_IRQ)
			return;

		asic->global_irq[local_irq] = irq;
	}
	*irqp = irq;
}