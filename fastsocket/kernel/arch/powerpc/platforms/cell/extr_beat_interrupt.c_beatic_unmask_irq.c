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
 unsigned long* beatic_irq_mask_enable ; 
 int /*<<< orphan*/  beatic_irq_mask_lock ; 
 int /*<<< orphan*/  beatic_update_irq_mask (unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void beatic_unmask_irq(unsigned int irq_plug)
{
	unsigned long flags;

	spin_lock_irqsave(&beatic_irq_mask_lock, flags);
	beatic_irq_mask_enable[irq_plug/64] |= 1UL << (63 - (irq_plug%64));
	beatic_update_irq_mask(irq_plug);
	spin_unlock_irqrestore(&beatic_irq_mask_lock, flags);
}