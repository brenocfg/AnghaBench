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
 unsigned int EXTINT_OFF ; 
 int /*<<< orphan*/  IRQ_EINT4t7 ; 
 unsigned int IRQ_EINT7 ; 
 int /*<<< orphan*/  IRQ_EINT8t23 ; 
 int /*<<< orphan*/  S3C24XX_EINTMASK ; 
 int /*<<< orphan*/  S3C24XX_EINTPEND ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c_irq_ack (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
s3c_irqext_ack(unsigned int irqno)
{
	unsigned long req;
	unsigned long bit;
	unsigned long mask;

	bit = 1UL << (irqno - EXTINT_OFF);

	mask = __raw_readl(S3C24XX_EINTMASK);

	__raw_writel(bit, S3C24XX_EINTPEND);

	req = __raw_readl(S3C24XX_EINTPEND);
	req &= ~mask;

	/* not sure if we should be acking the parent irq... */

	if (irqno <= IRQ_EINT7 ) {
		if ((req & 0xf0) == 0)
			s3c_irq_ack(IRQ_EINT4t7);
	} else {
		if ((req >> 8) == 0)
			s3c_irq_ack(IRQ_EINT8t23);
	}
}