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
typedef  int uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPLD_INT_MASK_REG ; 
 int MXC_IRQ_TO_EXPIO (int) ; 
 int __raw_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writew (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void expio_mask_irq(uint32_t irq)
{
	uint16_t reg;
	uint32_t expio = MXC_IRQ_TO_EXPIO(irq);

	/* mask the interrupt */
	reg = __raw_readw(CPLD_INT_MASK_REG);
	reg |= 1 << expio;
	__raw_writew(reg, CPLD_INT_MASK_REG);
}