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

/* Variables and functions */
 int /*<<< orphan*/  CPLD_INT_RESET_REG ; 
 int MXC_IRQ_TO_EXPIO (int) ; 
 int /*<<< orphan*/  __raw_writew (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expio_mask_irq (int) ; 

__attribute__((used)) static void expio_ack_irq(uint32_t irq)
{
	uint32_t expio = MXC_IRQ_TO_EXPIO(irq);

	/* clear the interrupt status */
	__raw_writew(1 << expio, CPLD_INT_RESET_REG);
	__raw_writew(0, CPLD_INT_RESET_REG);
	/* mask the interrupt */
	expio_mask_irq(irq);
}