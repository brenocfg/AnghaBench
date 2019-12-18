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
struct irq_desc {TYPE_1__* chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* eoi ) (unsigned int) ;} ;

/* Variables and functions */
 unsigned int NO_IRQ ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 unsigned int socrates_fpga_pic_get_irq (unsigned int) ; 
 int /*<<< orphan*/  stub1 (unsigned int) ; 

void socrates_fpga_pic_cascade(unsigned int irq, struct irq_desc *desc)
{
	unsigned int cascade_irq;

	/*
	 * See if we actually have an interrupt, call generic handling code if
	 * we do.
	 */
	cascade_irq = socrates_fpga_pic_get_irq(irq);

	if (cascade_irq != NO_IRQ)
		generic_handle_irq(cascade_irq);
	desc->chip->eoi(irq);

}