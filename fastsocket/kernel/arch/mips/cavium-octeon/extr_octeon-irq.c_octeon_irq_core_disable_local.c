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
 int /*<<< orphan*/  clear_c0_status (int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static void octeon_irq_core_disable_local(unsigned int irq)
{
	unsigned long flags;
	unsigned int bit = irq - OCTEON_IRQ_SW0;
	/*
	 * We need to disable interrupts to make sure our updates are
	 * atomic.
	 */
	local_irq_save(flags);
	clear_c0_status(0x100 << bit);
	local_irq_restore(flags);
}