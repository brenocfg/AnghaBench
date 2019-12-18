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
struct pio_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDR ; 
 unsigned int irq_to_gpio (unsigned int) ; 
 struct pio_device* pio_dev ; 
 int /*<<< orphan*/  pio_writel (struct pio_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void gpio_irq_mask(unsigned irq)
{
	unsigned		gpio = irq_to_gpio(irq);
	struct pio_device	*pio = &pio_dev[gpio >> 5];

	pio_writel(pio, IDR, 1 << (gpio & 0x1f));
}