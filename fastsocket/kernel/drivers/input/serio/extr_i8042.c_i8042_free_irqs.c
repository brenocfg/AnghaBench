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
 int /*<<< orphan*/  I8042_AUX_IRQ ; 
 int /*<<< orphan*/  I8042_KBD_IRQ ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i8042_aux_irq_registered ; 
 int i8042_kbd_irq_registered ; 
 int /*<<< orphan*/  i8042_platform_device ; 

__attribute__((used)) static void i8042_free_irqs(void)
{
	if (i8042_aux_irq_registered)
		free_irq(I8042_AUX_IRQ, i8042_platform_device);
	if (i8042_kbd_irq_registered)
		free_irq(I8042_KBD_IRQ, i8042_platform_device);

	i8042_aux_irq_registered = i8042_kbd_irq_registered = false;
}