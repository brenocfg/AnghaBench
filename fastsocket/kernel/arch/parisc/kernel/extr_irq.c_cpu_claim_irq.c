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
struct irq_chip {int /*<<< orphan*/  (* enable ) (unsigned int) ;} ;
struct TYPE_2__ {void* chip_data; struct irq_chip* chip; scalar_t__ action; } ;

/* Variables and functions */
 int EBUSY ; 
 struct irq_chip cpu_interrupt_type ; 
 TYPE_1__* irq_desc ; 
 int /*<<< orphan*/  stub1 (unsigned int) ; 

int cpu_claim_irq(unsigned int irq, struct irq_chip *type, void *data)
{
	if (irq_desc[irq].action)
		return -EBUSY;
	if (irq_desc[irq].chip != &cpu_interrupt_type)
		return -EBUSY;

	if (type) {
		irq_desc[irq].chip = type;
		irq_desc[irq].chip_data = data;
		cpu_interrupt_type.enable(irq);
	}
	return 0;
}