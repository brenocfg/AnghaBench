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
struct ipw_hardware {scalar_t__ hw_version; int /*<<< orphan*/  irq; scalar_t__ base_port; } ;

/* Variables and functions */
 scalar_t__ HW_VERSION_1 ; 
 scalar_t__ IOIER ; 
 scalar_t__ IOIR ; 
 unsigned int IR_RXINTR ; 
 unsigned int IR_TXINTR ; 
 unsigned int inw (scalar_t__) ; 
 int /*<<< orphan*/  outw (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_close_hardware(struct ipw_hardware *hw)
{
	unsigned int irqn;

	if (hw->hw_version == HW_VERSION_1) {
		/* Disable TX and RX interrupts. */
		outw(0, hw->base_port + IOIER);

		/* Acknowledge any outstanding interrupt requests */
		irqn = inw(hw->base_port + IOIR);
		if (irqn & IR_TXINTR)
			outw(IR_TXINTR, hw->base_port + IOIR);
		if (irqn & IR_RXINTR)
			outw(IR_RXINTR, hw->base_port + IOIR);

		synchronize_irq(hw->irq);
	}
}