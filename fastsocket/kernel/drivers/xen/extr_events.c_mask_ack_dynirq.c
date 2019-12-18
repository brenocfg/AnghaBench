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
 scalar_t__ VALID_EVTCHN (int) ; 
 int /*<<< orphan*/  clear_evtchn (int) ; 
 int /*<<< orphan*/  disable_dynirq (unsigned int) ; 
 int evtchn_from_irq (unsigned int) ; 
 int /*<<< orphan*/  move_masked_irq (unsigned int) ; 

__attribute__((used)) static void mask_ack_dynirq(unsigned int irq)
{
	/*
	 * Upstream has irq_move_irq and uses it in ack_dynirq; we do not.
	 * However, we know that in ack_dynirq the interrupt will never be
	 * masked (see mask_ack_irq and handle_edge_irq in kernel/irq/chip.c).
	 * So, use the same code twice except with move_native_irq there and
	 * move_masked_irq here.
	 */

	int evtchn = evtchn_from_irq(irq);

	disable_dynirq(irq);

	move_masked_irq(irq);

	if (VALID_EVTCHN(evtchn))
		clear_evtchn(evtchn);
}