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
 int /*<<< orphan*/  set_gpio_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bfin_gpio_ack_irq(unsigned int irq)
{
	/* AFAIK ack_irq in case mask_ack is provided
	 * get's only called for edge sense irqs
	 */
	set_gpio_data(irq_to_gpio(irq), 0);
}