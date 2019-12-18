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
 scalar_t__ HW_ICOLL_LEVELACK ; 
 scalar_t__ HW_ICOLL_PRIORITYn ; 
 scalar_t__ HW_ICOLL_STAT ; 
 scalar_t__ REGS_ICOLL_BASE ; 
 int /*<<< orphan*/  __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  stmp3xxx_clearl (int,scalar_t__) ; 

__attribute__((used)) static void stmp37xx_ack_irq(unsigned int irq)
{
	/* Disable IRQ */
	stmp3xxx_clearl(0x04 << ((irq % 4) * 8),
		REGS_ICOLL_BASE + HW_ICOLL_PRIORITYn + irq / 4 * 0x10);

	/* ACK current interrupt */
	__raw_writel(1, REGS_ICOLL_BASE + HW_ICOLL_LEVELACK);

	/* Barrier */
	(void)__raw_readl(REGS_ICOLL_BASE + HW_ICOLL_STAT);
}