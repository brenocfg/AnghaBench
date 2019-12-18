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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_gpio_irq_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_gpio_mask_irq (unsigned int) ; 
 int /*<<< orphan*/  gpio_enabled ; 
 int /*<<< orphan*/  irq_to_gpio (unsigned int) ; 

__attribute__((used)) static void bfin_gpio_irq_shutdown(unsigned int irq)
{
	u32 gpionr = irq_to_gpio(irq);

	bfin_gpio_mask_irq(irq);
	__clear_bit(gpionr, gpio_enabled);
	bfin_gpio_irq_free(gpionr);
}