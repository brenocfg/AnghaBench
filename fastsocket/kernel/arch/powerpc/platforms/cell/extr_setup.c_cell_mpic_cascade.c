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
struct mpic {int dummy; } ;
struct irq_desc {TYPE_1__* chip; struct mpic* handler_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* eoi ) (unsigned int) ;} ;

/* Variables and functions */
 unsigned int NO_IRQ ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 unsigned int mpic_get_one_irq (struct mpic*) ; 
 int /*<<< orphan*/  stub1 (unsigned int) ; 

__attribute__((used)) static void cell_mpic_cascade(unsigned int irq, struct irq_desc *desc)
{
	struct mpic *mpic = desc->handler_data;
	unsigned int virq;

	virq = mpic_get_one_irq(mpic);
	if (virq != NO_IRQ)
		generic_handle_irq(virq);
	desc->chip->eoi(irq);
}