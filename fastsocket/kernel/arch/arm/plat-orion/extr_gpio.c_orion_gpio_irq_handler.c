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
struct irq_desc {int status; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_DATA_IN (int) ; 
 int /*<<< orphan*/  GPIO_EDGE_CAUSE (int) ; 
 int /*<<< orphan*/  GPIO_EDGE_MASK (int) ; 
 int /*<<< orphan*/  GPIO_IN_POL (int) ; 
 int /*<<< orphan*/  GPIO_LEVEL_MASK (int) ; 
 int IRQ_TYPE_EDGE_BOTH ; 
 int IRQ_TYPE_SENSE_MASK ; 
 int /*<<< orphan*/  desc_handle_irq (int,struct irq_desc*) ; 
 int gpio_to_irq (int) ; 
 struct irq_desc* irq_desc ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

void orion_gpio_irq_handler(int pinoff)
{
	u32 cause;
	int pin;

	cause = readl(GPIO_DATA_IN(pinoff)) & readl(GPIO_LEVEL_MASK(pinoff));
	cause |= readl(GPIO_EDGE_CAUSE(pinoff)) & readl(GPIO_EDGE_MASK(pinoff));

	for (pin = pinoff; pin < pinoff + 8; pin++) {
		int irq = gpio_to_irq(pin);
		struct irq_desc *desc = irq_desc + irq;

		if (!(cause & (1 << (pin & 31))))
			continue;

		if ((desc->status & IRQ_TYPE_SENSE_MASK) == IRQ_TYPE_EDGE_BOTH) {
			/* Swap polarity (race with GPIO line) */
			u32 polarity;

			polarity = readl(GPIO_IN_POL(pin));
			polarity ^= 1 << (pin & 31);
			writel(polarity, GPIO_IN_POL(pin));
		}
		desc_handle_irq(irq, desc);
	}
}