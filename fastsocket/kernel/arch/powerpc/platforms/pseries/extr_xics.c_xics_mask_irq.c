#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ hwirq; } ;

/* Variables and functions */
 unsigned int XICS_IPI ; 
 unsigned int XICS_IRQ_SPURIOUS ; 
 TYPE_1__* irq_map ; 
 int /*<<< orphan*/  pr_devel (char*,unsigned int) ; 
 int /*<<< orphan*/  xics_mask_real_irq (unsigned int) ; 

__attribute__((used)) static void xics_mask_irq(unsigned int virq)
{
	unsigned int irq;

	pr_devel("xics: mask virq %d\n", virq);

	irq = (unsigned int)irq_map[virq].hwirq;
	if (irq == XICS_IPI || irq == XICS_IRQ_SPURIOUS)
		return;
	xics_mask_real_irq(irq);
}