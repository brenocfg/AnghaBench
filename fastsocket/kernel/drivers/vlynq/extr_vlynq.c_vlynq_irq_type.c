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
typedef  int u32 ;
struct vlynq_device {unsigned int irq_start; TYPE_1__* remote; } ;
struct TYPE_2__ {int /*<<< orphan*/ * int_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
#define  IRQ_TYPE_EDGE_BOTH 132 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 unsigned int IRQ_TYPE_SENSE_MASK ; 
 int VINT_LEVEL_LOW ; 
 int VINT_OFFSET (int) ; 
 int VINT_TYPE_EDGE ; 
 struct vlynq_device* get_irq_chip_data (unsigned int) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlynq_irq_type(unsigned int irq, unsigned int flow_type)
{
	u32 val;
	struct vlynq_device *dev = get_irq_chip_data(irq);
	int virq;

	BUG_ON(!dev);
	virq = irq - dev->irq_start;
	val = readl(&dev->remote->int_device[virq >> 2]);
	switch (flow_type & IRQ_TYPE_SENSE_MASK) {
	case IRQ_TYPE_EDGE_RISING:
	case IRQ_TYPE_EDGE_FALLING:
	case IRQ_TYPE_EDGE_BOTH:
		val |= VINT_TYPE_EDGE << VINT_OFFSET(virq);
		val &= ~(VINT_LEVEL_LOW << VINT_OFFSET(virq));
		break;
	case IRQ_TYPE_LEVEL_HIGH:
		val &= ~(VINT_TYPE_EDGE << VINT_OFFSET(virq));
		val &= ~(VINT_LEVEL_LOW << VINT_OFFSET(virq));
		break;
	case IRQ_TYPE_LEVEL_LOW:
		val &= ~(VINT_TYPE_EDGE << VINT_OFFSET(virq));
		val |= VINT_LEVEL_LOW << VINT_OFFSET(virq);
		break;
	default:
		return -EINVAL;
	}
	writel(val, &dev->remote->int_device[virq >> 2]);
	return 0;
}