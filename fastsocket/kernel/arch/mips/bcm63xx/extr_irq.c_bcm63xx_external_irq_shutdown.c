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
 unsigned int IRQ_MIPS_BASE ; 
 int /*<<< orphan*/  bcm63xx_external_irq_mask (unsigned int) ; 
 int /*<<< orphan*/  clear_c0_status (int) ; 
 int /*<<< orphan*/  irq_disable_hazard () ; 

__attribute__((used)) static void bcm63xx_external_irq_shutdown(unsigned int irq)
{
	bcm63xx_external_irq_mask(irq);
	clear_c0_status(0x100 << (irq - IRQ_MIPS_BASE));
	irq_disable_hazard();
}