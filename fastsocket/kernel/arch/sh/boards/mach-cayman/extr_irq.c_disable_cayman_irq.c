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
 unsigned int EPLD_MASK_BASE ; 
 scalar_t__ START_EXT_IRQS ; 
 unsigned long ctrl_inl (unsigned int) ; 
 int /*<<< orphan*/  ctrl_outl (unsigned long,unsigned int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

void disable_cayman_irq(unsigned int irq)
{
	unsigned long flags;
	unsigned long mask;
	unsigned int reg;
	unsigned char bit;

	irq -= START_EXT_IRQS;
	reg = EPLD_MASK_BASE + ((irq / 8) << 2);
	bit = 1<<(irq % 8);
	local_irq_save(flags);
	mask = ctrl_inl(reg);
	mask &= ~bit;
	ctrl_outl(mask, reg);
	local_irq_restore(flags);
}