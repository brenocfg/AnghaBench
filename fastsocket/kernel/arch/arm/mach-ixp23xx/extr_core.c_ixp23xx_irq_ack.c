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
 unsigned int IRQ_IXP23XX_GPIO6 ; 
 int* IXP23XX_GPIO_GPISR ; 

__attribute__((used)) static void ixp23xx_irq_ack(unsigned int irq)
{
	int line = irq - IRQ_IXP23XX_GPIO6 + 6;

	if ((line < 6) || (line > 15))
		return;

	*IXP23XX_GPIO_GPISR = (1 << line);
}