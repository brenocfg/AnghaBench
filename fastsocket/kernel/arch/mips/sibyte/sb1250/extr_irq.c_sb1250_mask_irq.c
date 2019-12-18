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
typedef  int u64 ;

/* Variables and functions */
 scalar_t__ A_IMR_MAPPER (int) ; 
 int /*<<< orphan*/  IOADDR (scalar_t__) ; 
 scalar_t__ R_IMR_INTERRUPT_MASK ; 
 int ____raw_readq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ____raw_writeq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb1250_imr_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void sb1250_mask_irq(int cpu, int irq)
{
	unsigned long flags;
	u64 cur_ints;

	spin_lock_irqsave(&sb1250_imr_lock, flags);
	cur_ints = ____raw_readq(IOADDR(A_IMR_MAPPER(cpu) +
					R_IMR_INTERRUPT_MASK));
	cur_ints |= (((u64) 1) << irq);
	____raw_writeq(cur_ints, IOADDR(A_IMR_MAPPER(cpu) +
					R_IMR_INTERRUPT_MASK));
	spin_unlock_irqrestore(&sb1250_imr_lock, flags);
}