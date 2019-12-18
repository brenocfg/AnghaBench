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
 int /*<<< orphan*/  S3C24XX_MISCCR ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

unsigned int s3c2410_modify_misccr(unsigned int clear, unsigned int change)
{
	unsigned long flags;
	unsigned long misccr;

	local_irq_save(flags);
	misccr = __raw_readl(S3C24XX_MISCCR);
	misccr &= ~clear;
	misccr ^= change;
	__raw_writel(misccr, S3C24XX_MISCCR);
	local_irq_restore(flags);

	return misccr;
}