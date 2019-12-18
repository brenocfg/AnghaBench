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
struct irq_desc {int dummy; } ;

/* Variables and functions */
 int GEDR ; 
 unsigned int IRQ_GPIO11 ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 

__attribute__((used)) static void
sa1100_high_gpio_handler(unsigned int irq, struct irq_desc *desc)
{
	unsigned int mask;

	mask = GEDR & 0xfffff800;
	do {
		/*
		 * clear down all currently active IRQ sources.
		 * We will be processing them all.
		 */
		GEDR = mask;

		irq = IRQ_GPIO11;
		mask >>= 11;
		do {
			if (mask & 1)
				generic_handle_irq(irq);
			mask >>= 1;
			irq++;
		} while (mask);

		mask = GEDR & 0xfffff800;
	} while (mask);
}