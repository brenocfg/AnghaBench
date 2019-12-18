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
typedef  int u32 ;

/* Variables and functions */
 scalar_t__ GEF_PIC_INTR_MASK (int /*<<< orphan*/ ) ; 
 unsigned int gef_irq_to_hw (unsigned int) ; 
 scalar_t__ gef_pic_irq_reg_base ; 
 int /*<<< orphan*/  gef_pic_lock ; 
 int in_be32 (scalar_t__) ; 
 int /*<<< orphan*/  out_be32 (scalar_t__,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void gef_pic_mask(unsigned int virq)
{
	unsigned long flags;
	unsigned int hwirq;
	u32 mask;

	hwirq = gef_irq_to_hw(virq);

	spin_lock_irqsave(&gef_pic_lock, flags);
	mask = in_be32(gef_pic_irq_reg_base + GEF_PIC_INTR_MASK(0));
	mask &= ~(1 << hwirq);
	out_be32(gef_pic_irq_reg_base + GEF_PIC_INTR_MASK(0), mask);
	spin_unlock_irqrestore(&gef_pic_lock, flags);
}