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

/* Variables and functions */
 int GPIO_GPIOFEOI ; 
 int IRQ_TO_GPIO (int) ; 
 int VIC2_INTENCLR ; 

__attribute__((used)) static void lh7a404_vic2_ack_gpio_irq (u32 irq)
{
	GPIO_GPIOFEOI = (1 << IRQ_TO_GPIO (irq));
	VIC2_INTENCLR = (1 << irq);
}