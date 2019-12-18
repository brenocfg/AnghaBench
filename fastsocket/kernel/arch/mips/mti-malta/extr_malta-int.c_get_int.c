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
 int /*<<< orphan*/  mips_irq_lock ; 
 int mips_pcibios_iack () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline int get_int(void)
{
	unsigned long flags;
	int irq;
	spin_lock_irqsave(&mips_irq_lock, flags);

	irq = mips_pcibios_iack();

	/*
	 * The only way we can decide if an interrupt is spurious
	 * is by checking the 8259 registers.  This needs a spinlock
	 * on an SMP system,  so leave it up to the generic code...
	 */

	spin_unlock_irqrestore(&mips_irq_lock, flags);

	return irq;
}