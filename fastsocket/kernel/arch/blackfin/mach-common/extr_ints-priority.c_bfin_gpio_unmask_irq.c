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
 int /*<<< orphan*/  irq_to_gpio (unsigned int) ; 
 int /*<<< orphan*/  set_gpio_maska (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bfin_gpio_unmask_irq(unsigned int irq)
{
	set_gpio_maska(irq_to_gpio(irq), 1);
}