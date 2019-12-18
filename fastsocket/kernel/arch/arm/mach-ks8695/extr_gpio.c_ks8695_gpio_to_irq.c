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
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int KS8695_GPIO_3 ; 
 int* gpio_irq ; 

__attribute__((used)) static int ks8695_gpio_to_irq(struct gpio_chip *gc, unsigned int pin)
{
	if (pin > KS8695_GPIO_3)	/* only GPIO 0..3 can generate IRQ */
		return -EINVAL;

	return gpio_irq[pin];
}