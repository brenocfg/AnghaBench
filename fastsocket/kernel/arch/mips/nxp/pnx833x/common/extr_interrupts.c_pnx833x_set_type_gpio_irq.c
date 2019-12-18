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
 int GPIO_INT_EDGE_BOTH ; 
 int GPIO_INT_EDGE_FALLING ; 
 int GPIO_INT_EDGE_RISING ; 
 int GPIO_INT_LEVEL_HIGH ; 
 int GPIO_INT_LEVEL_LOW ; 
 int GPIO_INT_NONE ; 
#define  IRQ_TYPE_EDGE_BOTH 132 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 unsigned int PNX833X_GPIO_IRQ_BASE ; 
 int /*<<< orphan*/  pnx833x_gpio_setup_irq (int,int) ; 

__attribute__((used)) static int pnx833x_set_type_gpio_irq(unsigned int irq, unsigned int flow_type)
{
	int pin = irq - PNX833X_GPIO_IRQ_BASE;
	int gpio_mode;

	switch (flow_type) {
	case IRQ_TYPE_EDGE_RISING:
		gpio_mode = GPIO_INT_EDGE_RISING;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		gpio_mode = GPIO_INT_EDGE_FALLING;
		break;
	case IRQ_TYPE_EDGE_BOTH:
		gpio_mode = GPIO_INT_EDGE_BOTH;
		break;
	case IRQ_TYPE_LEVEL_HIGH:
		gpio_mode = GPIO_INT_LEVEL_HIGH;
		break;
	case IRQ_TYPE_LEVEL_LOW:
		gpio_mode = GPIO_INT_LEVEL_LOW;
		break;
	default:
		gpio_mode = GPIO_INT_NONE;
		break;
	}

	pnx833x_gpio_setup_irq(gpio_mode, pin);

	return 0;
}