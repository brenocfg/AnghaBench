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
struct irq_desc {unsigned int status; int /*<<< orphan*/  threads_active; int /*<<< orphan*/  wait_for_threads; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned int IRQ_INPROGRESS ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 struct irq_desc* irq_to_desc (unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void synchronize_irq(unsigned int irq)
{
	struct irq_desc *desc = irq_to_desc(irq);
	unsigned int status;

	if (!desc)
		return;

	do {
		unsigned long flags;

		/*
		 * Wait until we're out of the critical section.  This might
		 * give the wrong answer due to the lack of memory barriers.
		 */
		while (desc->status & IRQ_INPROGRESS)
			cpu_relax();

		/* Ok, that indicated we're done: double-check carefully. */
		spin_lock_irqsave(&desc->lock, flags);
		status = desc->status;
		spin_unlock_irqrestore(&desc->lock, flags);

		/* Oops, that failed? */
	} while (status & IRQ_INPROGRESS);

	/*
	 * We made sure that no hardirq handler is running. Now verify
	 * that no threaded handlers are active.
	 */
	wait_event(desc->wait_for_threads, !atomic_read(&desc->threads_active));
}