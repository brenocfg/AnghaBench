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
 int EINVAL ; 
 unsigned int GPIO_MAPPED_IRQ_BASE ; 
 int GPIO_MAPPED_IRQ_GROUP ; 
 int GROUP4_IRQ_BASE ; 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 int irq_to_group (unsigned int) ; 
 int /*<<< orphan*/  rb532_gpio_set_ilevel (int,int) ; 

__attribute__((used)) static int rb532_set_type(unsigned int irq_nr, unsigned type)
{
	int gpio = irq_nr - GPIO_MAPPED_IRQ_BASE;
	int group = irq_to_group(irq_nr);

	if (group != GPIO_MAPPED_IRQ_GROUP || irq_nr > (GROUP4_IRQ_BASE + 13))
		return (type == IRQ_TYPE_LEVEL_HIGH) ? 0 : -EINVAL;

	switch (type) {
	case IRQ_TYPE_LEVEL_HIGH:
		rb532_gpio_set_ilevel(1, gpio);
		break;
	case IRQ_TYPE_LEVEL_LOW:
		rb532_gpio_set_ilevel(0, gpio);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}