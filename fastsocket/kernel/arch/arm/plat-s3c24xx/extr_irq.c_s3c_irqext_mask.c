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
 scalar_t__ EXTINT_OFF ; 
 int /*<<< orphan*/  S3C24XX_EINTMASK ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
s3c_irqext_mask(unsigned int irqno)
{
	unsigned long mask;

	irqno -= EXTINT_OFF;

	mask = __raw_readl(S3C24XX_EINTMASK);
	mask |= ( 1UL << irqno);
	__raw_writel(mask, S3C24XX_EINTMASK);
}