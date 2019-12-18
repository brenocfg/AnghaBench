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
 unsigned int OCTEON_IRQ_SW0 ; 
 int /*<<< orphan*/  clear_c0_cause (int) ; 
 int /*<<< orphan*/  clear_c0_status (int) ; 

__attribute__((used)) static void octeon_irq_core_ack(unsigned int irq)
{
	unsigned int bit = irq - OCTEON_IRQ_SW0;
	/*
	 * We don't need to disable IRQs to make these atomic since
	 * they are already disabled earlier in the low level
	 * interrupt code.
	 */
	clear_c0_status(0x100 << bit);
	/* The two user interrupts must be cleared manually. */
	if (bit < 2)
		clear_c0_cause(0x100 << bit);
}