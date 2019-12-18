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
 unsigned int IRQ_EINT0 ; 
 int /*<<< orphan*/  S3C2410_INTMSK ; 
 int /*<<< orphan*/  S3C2412_EINTMASK ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
s3c2412_irq_unmask(unsigned int irqno)
{
	unsigned long bitval = 1UL << (irqno - IRQ_EINT0);
	unsigned long mask;

	mask = __raw_readl(S3C2412_EINTMASK);
	__raw_writel(mask & ~bitval, S3C2412_EINTMASK);

	mask = __raw_readl(S3C2410_INTMSK);
	__raw_writel(mask & ~bitval, S3C2410_INTMSK);
}