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
 int /*<<< orphan*/  JAZZ_IO_IRQ_ENABLE ; 
 unsigned int JAZZ_IRQ_START ; 
 int /*<<< orphan*/  r4030_lock ; 
 unsigned int r4030_read_reg16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r4030_write_reg16 (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void enable_r4030_irq(unsigned int irq)
{
	unsigned int mask = 1 << (irq - JAZZ_IRQ_START);
	unsigned long flags;

	spin_lock_irqsave(&r4030_lock, flags);
	mask |= r4030_read_reg16(JAZZ_IO_IRQ_ENABLE);
	r4030_write_reg16(JAZZ_IO_IRQ_ENABLE, mask);
	spin_unlock_irqrestore(&r4030_lock, flags);
}