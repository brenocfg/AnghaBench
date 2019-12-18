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
typedef  size_t u32 ;
struct TYPE_2__ {int status; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_EDGE_CAUSE (int) ; 
 int IRQ_TYPE_EDGE_FALLING ; 
 int IRQ_TYPE_EDGE_RISING ; 
 int IRQ_TYPE_SENSE_MASK ; 
 TYPE_1__* irq_desc ; 
 int irq_to_gpio (size_t) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gpio_irq_ack(u32 irq)
{
	int type = irq_desc[irq].status & IRQ_TYPE_SENSE_MASK;
	if (type & (IRQ_TYPE_EDGE_RISING | IRQ_TYPE_EDGE_FALLING)) {
		int pin = irq_to_gpio(irq);
		writel(~(1 << (pin & 31)), GPIO_EDGE_CAUSE(pin));
	}
}