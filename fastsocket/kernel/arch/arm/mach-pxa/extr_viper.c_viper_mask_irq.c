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
 int /*<<< orphan*/  viper_irq_enabled_mask ; 
 int /*<<< orphan*/  viper_irq_to_bitmask (unsigned int) ; 

__attribute__((used)) static void viper_mask_irq(unsigned int irq)
{
	viper_irq_enabled_mask &= ~(viper_irq_to_bitmask(irq));
}