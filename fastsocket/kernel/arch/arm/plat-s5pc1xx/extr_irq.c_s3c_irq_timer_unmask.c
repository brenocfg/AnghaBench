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
 unsigned int IRQ_TIMER0 ; 
 int /*<<< orphan*/  S3C64XX_TINT_CSTAT ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s3c_irq_timer_unmask(unsigned int irq)
{
	u32 reg = __raw_readl(S3C64XX_TINT_CSTAT);

	reg &= 0x1f;  /* mask out pending interrupts */
	reg |= 1 << (irq - IRQ_TIMER0);
	__raw_writel(reg, S3C64XX_TINT_CSTAT);
}