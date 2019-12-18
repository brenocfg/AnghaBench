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
 int NR_IRQS ; 
 unsigned char SUN4C_INT_E1 ; 
 unsigned char SUN4C_INT_E10 ; 
 unsigned char SUN4C_INT_E14 ; 
 unsigned char SUN4C_INT_E8 ; 
 int /*<<< orphan*/  interrupt_enable ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 unsigned char sbus_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbus_writeb (unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sun4c_enable_irq(unsigned int irq_nr)
{
	unsigned long flags;
	unsigned char current_mask, new_mask;
    
	local_irq_save(flags);
	irq_nr &= (NR_IRQS - 1);
	current_mask = sbus_readb(interrupt_enable);
	switch(irq_nr) {
	case 1:
		new_mask = ((current_mask) | SUN4C_INT_E1);
		break;
	case 8:
		new_mask = ((current_mask) | SUN4C_INT_E8);
		break;
	case 10:
		new_mask = ((current_mask) | SUN4C_INT_E10);
		break;
	case 14:
		new_mask = ((current_mask) | SUN4C_INT_E14);
		break;
	default:
		local_irq_restore(flags);
		return;
	}
	sbus_writeb(new_mask, interrupt_enable);
	local_irq_restore(flags);
}