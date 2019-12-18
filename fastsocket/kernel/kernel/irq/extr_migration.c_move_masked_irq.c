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
struct irq_desc {int status; int /*<<< orphan*/  pending_mask; int /*<<< orphan*/  affinity; TYPE_1__* chip; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_affinity ) (int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ CHECK_IRQ_PER_CPU (int) ; 
 int IRQ_MOVE_PENDING ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 scalar_t__ cpumask_any_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_thread_affinity (struct irq_desc*) ; 
 struct irq_desc* irq_to_desc (int) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ nr_cpu_ids ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void move_masked_irq(int irq)
{
	struct irq_desc *desc = irq_to_desc(irq);

	if (likely(!(desc->status & IRQ_MOVE_PENDING)))
		return;

	/*
	 * Paranoia: cpu-local interrupts shouldn't be calling in here anyway.
	 */
	if (CHECK_IRQ_PER_CPU(desc->status)) {
		WARN_ON(1);
		return;
	}

	desc->status &= ~IRQ_MOVE_PENDING;

	if (unlikely(cpumask_empty(desc->pending_mask)))
		return;

	if (!desc->chip->set_affinity)
		return;

	assert_spin_locked(&desc->lock);

	/*
	 * If there was a valid mask to work with, please
	 * do the disable, re-program, enable sequence.
	 * This is *not* particularly important for level triggered
	 * but in a edge trigger case, we might be setting rte
	 * when an active trigger is comming in. This could
	 * cause some ioapics to mal-function.
	 * Being paranoid i guess!
	 *
	 * For correct operation this depends on the caller
	 * masking the irqs.
	 */
	if (likely(cpumask_any_and(desc->pending_mask, cpu_online_mask)
		   < nr_cpu_ids))
		if (!desc->chip->set_affinity(irq, desc->pending_mask)) {
			cpumask_copy(desc->affinity, desc->pending_mask);
			irq_set_thread_affinity(desc);
		}

	cpumask_clear(desc->pending_mask);
}