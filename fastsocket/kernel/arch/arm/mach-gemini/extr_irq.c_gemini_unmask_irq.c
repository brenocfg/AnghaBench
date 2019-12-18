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
 int /*<<< orphan*/  GEMINI_INTERRUPT_BASE ; 
 int /*<<< orphan*/  IO_ADDRESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_MASK (int /*<<< orphan*/ ) ; 
 unsigned int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gemini_unmask_irq(unsigned int irq)
{
	unsigned int mask;

	mask = __raw_readl(IRQ_MASK(IO_ADDRESS(GEMINI_INTERRUPT_BASE)));
	mask |= (1 << irq);
	__raw_writel(mask, IRQ_MASK(IO_ADDRESS(GEMINI_INTERRUPT_BASE)));
}