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
 int /*<<< orphan*/  _set_gpio_irqenable (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int irq_to_gpio (int) ; 
 int /*<<< orphan*/ * mxc_gpio_ports ; 

__attribute__((used)) static void gpio_mask_irq(u32 irq)
{
	u32 gpio = irq_to_gpio(irq);
	_set_gpio_irqenable(&mxc_gpio_ports[gpio / 32], gpio & 0x1f, 0);
}