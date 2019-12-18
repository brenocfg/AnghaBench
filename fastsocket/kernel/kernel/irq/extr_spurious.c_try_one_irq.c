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
struct irqaction {int flags; scalar_t__ (* handler ) (int,int /*<<< orphan*/ ) ;struct irqaction* next; int /*<<< orphan*/  dev_id; } ;
struct irq_desc {int status; int /*<<< orphan*/  lock; TYPE_1__* chip; struct irqaction* action; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* end ) (int) ;} ;

/* Variables and functions */
 int IRQF_SHARED ; 
 scalar_t__ IRQ_HANDLED ; 
 int IRQ_INPROGRESS ; 
 int IRQ_PENDING ; 
 int /*<<< orphan*/  handle_IRQ_event (int,struct irqaction*) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int) ; 

__attribute__((used)) static int try_one_irq(int irq, struct irq_desc *desc)
{
	struct irqaction *action;
	int ok = 0, work = 0;

	spin_lock(&desc->lock);
	/* Already running on another processor */
	if (desc->status & IRQ_INPROGRESS) {
		/*
		 * Already running: If it is shared get the other
		 * CPU to go looking for our mystery interrupt too
		 */
		if (desc->action && (desc->action->flags & IRQF_SHARED))
			desc->status |= IRQ_PENDING;
		spin_unlock(&desc->lock);
		return ok;
	}
	/* Honour the normal IRQ locking */
	desc->status |= IRQ_INPROGRESS;
	action = desc->action;
	spin_unlock(&desc->lock);

	while (action) {
		/* Only shared IRQ handlers are safe to call */
		if (action->flags & IRQF_SHARED) {
			if (action->handler(irq, action->dev_id) ==
				IRQ_HANDLED)
				ok = 1;
		}
		action = action->next;
	}
	local_irq_disable();
	/* Now clean up the flags */
	spin_lock(&desc->lock);
	action = desc->action;

	/*
	 * While we were looking for a fixup someone queued a real
	 * IRQ clashing with our walk:
	 */
	while ((desc->status & IRQ_PENDING) && action) {
		/*
		 * Perform real IRQ processing for the IRQ we deferred
		 */
		work = 1;
		spin_unlock(&desc->lock);
		handle_IRQ_event(irq, action);
		spin_lock(&desc->lock);
		desc->status &= ~IRQ_PENDING;
	}
	desc->status &= ~IRQ_INPROGRESS;
	/*
	 * If we did actual work for the real IRQ line we must let the
	 * IRQ controller clean up too
	 */
	if (work && desc->chip && desc->chip->end)
		desc->chip->end(irq);
	spin_unlock(&desc->lock);

	return ok;
}