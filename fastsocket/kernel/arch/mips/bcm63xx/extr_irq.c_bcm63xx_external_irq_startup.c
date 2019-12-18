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
 int /*<<< orphan*/  bcm63xx_external_irq_unmask (unsigned int) ; 
 int /*<<< orphan*/  irq_enable_hazard () ; 
 int /*<<< orphan*/  set_c0_status (int) ; 

__attribute__((used)) static unsigned int bcm63xx_external_irq_startup(unsigned int irq)
{
	set_c0_status(0x100 << (irq - IRQ_MIPS_BASE));
	irq_enable_hazard();
	bcm63xx_external_irq_unmask(irq);
	return 0;
}