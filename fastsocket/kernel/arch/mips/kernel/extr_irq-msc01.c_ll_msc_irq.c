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
 int /*<<< orphan*/  MSC01_IC_VEC ; 
 int /*<<< orphan*/  MSCIC_READ (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  do_IRQ (scalar_t__) ; 
 scalar_t__ irq_base ; 

void ll_msc_irq(void)
{
 	unsigned int irq;

	/* read the interrupt vector register */
	MSCIC_READ(MSC01_IC_VEC, irq);
	if (irq < 64)
		do_IRQ(irq + irq_base);
	else {
		/* Ignore spurious interrupt */
	}
}