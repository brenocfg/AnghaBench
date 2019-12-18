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
 scalar_t__ MCFINTC0_CIMR ; 
 scalar_t__ MCFINTC1_CIMR ; 
 unsigned int MCFINT_VECBASE ; 
 int /*<<< orphan*/  __raw_writeb (unsigned int,scalar_t__) ; 

__attribute__((used)) static void intc_irq_unmask(unsigned int irq)
{
	if (irq >= MCFINT_VECBASE) {
		if (irq < MCFINT_VECBASE + 64)
			__raw_writeb(irq - MCFINT_VECBASE, MCFINTC0_CIMR);
		else if ((irq < MCFINT_VECBASE + 128) && MCFINTC1_CIMR)
			__raw_writeb(irq - MCFINT_VECBASE - 64, MCFINTC1_CIMR);
	}
}