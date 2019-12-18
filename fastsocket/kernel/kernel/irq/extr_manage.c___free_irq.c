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
struct irqaction {void* dev_id; int flags; scalar_t__ thread; int /*<<< orphan*/  thread_flags; int /*<<< orphan*/  (* handler ) (unsigned int,void*) ;struct irqaction* next; } ;
struct irq_desc {int /*<<< orphan*/  lock; int /*<<< orphan*/ * affinity_hint; TYPE_1__* chip; int /*<<< orphan*/  status; struct irqaction* action; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable ) (unsigned int) ;int /*<<< orphan*/  (* shutdown ) (unsigned int) ;int /*<<< orphan*/  (* release ) (unsigned int,void*) ;} ;

/* Variables and functions */
 int IRQF_SHARED ; 
 int /*<<< orphan*/  IRQTF_DIED ; 
 int /*<<< orphan*/  IRQ_DISABLED ; 
 int /*<<< orphan*/  WARN (int,char*,unsigned int) ; 
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ *) ; 
 int in_interrupt () ; 
 struct irq_desc* irq_to_desc (unsigned int) ; 
 int /*<<< orphan*/  kthread_stop (scalar_t__) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  put_task_struct (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (unsigned int,void*) ; 
 int /*<<< orphan*/  stub2 (unsigned int) ; 
 int /*<<< orphan*/  stub3 (unsigned int) ; 
 int /*<<< orphan*/  stub4 (unsigned int,void*) ; 
 int /*<<< orphan*/  synchronize_irq (unsigned int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_handler_proc (unsigned int,struct irqaction*) ; 

__attribute__((used)) static struct irqaction *__free_irq(unsigned int irq, void *dev_id)
{
	struct irq_desc *desc = irq_to_desc(irq);
	struct irqaction *action, **action_ptr;
	unsigned long flags;

	WARN(in_interrupt(), "Trying to free IRQ %d from IRQ context!\n", irq);

	if (!desc)
		return NULL;

	spin_lock_irqsave(&desc->lock, flags);

	/*
	 * There can be multiple actions per IRQ descriptor, find the right
	 * one based on the dev_id:
	 */
	action_ptr = &desc->action;
	for (;;) {
		action = *action_ptr;

		if (!action) {
			WARN(1, "Trying to free already-free IRQ %d\n", irq);
			spin_unlock_irqrestore(&desc->lock, flags);

			return NULL;
		}

		if (action->dev_id == dev_id)
			break;
		action_ptr = &action->next;
	}

	/* Found it - now remove it from the list of entries: */
	*action_ptr = action->next;

	/* Currently used only by UML, might disappear one day: */
#ifdef CONFIG_IRQ_RELEASE_METHOD
	if (desc->chip->release)
		desc->chip->release(irq, dev_id);
#endif

	/* If this was the last handler, shut down the IRQ line: */
	if (!desc->action) {
		desc->status |= IRQ_DISABLED;
		if (desc->chip->shutdown)
			desc->chip->shutdown(irq);
		else
			desc->chip->disable(irq);
	}

#ifdef CONFIG_SMP
	/* make sure affinity_hint is cleaned up */
	if (WARN_ON_ONCE(desc->affinity_hint))
		desc->affinity_hint = NULL;
#endif

	spin_unlock_irqrestore(&desc->lock, flags);

	unregister_handler_proc(irq, action);

	/* Make sure it's not being used on another CPU: */
	synchronize_irq(irq);

#ifdef CONFIG_DEBUG_SHIRQ
	/*
	 * It's a shared IRQ -- the driver ought to be prepared for an IRQ
	 * event to happen even now it's being freed, so let's make sure that
	 * is so by doing an extra call to the handler ....
	 *
	 * ( We do this after actually deregistering it, to make sure that a
	 *   'real' IRQ doesn't run in * parallel with our fake. )
	 */
	if (action->flags & IRQF_SHARED) {
		local_irq_save(flags);
		action->handler(irq, dev_id);
		local_irq_restore(flags);
	}
#endif

	if (action->thread) {
		if (!test_bit(IRQTF_DIED, &action->thread_flags))
			kthread_stop(action->thread);
		put_task_struct(action->thread);
	}

	return action;
}