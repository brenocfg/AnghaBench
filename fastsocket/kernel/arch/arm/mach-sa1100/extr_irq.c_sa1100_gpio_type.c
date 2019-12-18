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

/* Variables and functions */
 unsigned int GFER ; 
 unsigned int GPIO11_27_MASK (unsigned int) ; 
 unsigned int GPIO_IRQ_falling_edge ; 
 unsigned int GPIO_IRQ_mask ; 
 unsigned int GPIO_IRQ_rising_edge ; 
 unsigned int GRER ; 
 unsigned int IRQ_TYPE_EDGE_FALLING ; 
 unsigned int IRQ_TYPE_EDGE_RISING ; 
 unsigned int IRQ_TYPE_PROBE ; 

__attribute__((used)) static int sa1100_gpio_type(unsigned int irq, unsigned int type)
{
	unsigned int mask;

	if (irq <= 10)
		mask = 1 << irq;
	else
		mask = GPIO11_27_MASK(irq);

	if (type == IRQ_TYPE_PROBE) {
		if ((GPIO_IRQ_rising_edge | GPIO_IRQ_falling_edge) & mask)
			return 0;
		type = IRQ_TYPE_EDGE_RISING | IRQ_TYPE_EDGE_FALLING;
	}

	if (type & IRQ_TYPE_EDGE_RISING) {
		GPIO_IRQ_rising_edge |= mask;
	} else
		GPIO_IRQ_rising_edge &= ~mask;
	if (type & IRQ_TYPE_EDGE_FALLING) {
		GPIO_IRQ_falling_edge |= mask;
	} else
		GPIO_IRQ_falling_edge &= ~mask;

	GRER = GPIO_IRQ_rising_edge & GPIO_IRQ_mask;
	GFER = GPIO_IRQ_falling_edge & GPIO_IRQ_mask;

	return 0;
}