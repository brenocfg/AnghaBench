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
 unsigned long* IXP23XX_INTR_EN1 ; 

__attribute__((used)) static void ixp23xx_irq_edge_unmask(unsigned int irq)
{
	volatile unsigned long *intr_reg;

	if (irq >= 56)
		irq += 8;

	intr_reg = IXP23XX_INTR_EN1 + (irq / 32);
	*intr_reg |= (1 << (irq % 32));
}