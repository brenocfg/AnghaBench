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
struct irq_desc {int dummy; } ;

/* Variables and functions */
 int IRQ_EINT4 ; 
 int /*<<< orphan*/  S3C24XX_EINTMASK ; 
 int /*<<< orphan*/  S3C24XX_EINTPEND ; 
 unsigned int __ffs (unsigned long) ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 

__attribute__((used)) static void
s3c_irq_demux_extint4t7(unsigned int irq,
			struct irq_desc *desc)
{
	unsigned long eintpnd = __raw_readl(S3C24XX_EINTPEND);
	unsigned long eintmsk = __raw_readl(S3C24XX_EINTMASK);

	eintpnd &= ~eintmsk;
	eintpnd &= 0xff;	/* only lower irqs */

	/* we may as well handle all the pending IRQs here */

	while (eintpnd) {
		irq = __ffs(eintpnd);
		eintpnd &= ~(1<<irq);

		irq += (IRQ_EINT4 - 4);

		generic_handle_irq(irq);
	}
}