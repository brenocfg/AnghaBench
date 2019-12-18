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
struct irqaction {int flags; int (* handler ) (unsigned int,int /*<<< orphan*/ ) ;struct irqaction* next; int /*<<< orphan*/  thread; int /*<<< orphan*/  thread_flags; int /*<<< orphan*/  thread_fn; int /*<<< orphan*/  dev_id; } ;
typedef  int irqreturn_t ;

/* Variables and functions */
 int IRQF_DISABLED ; 
 unsigned int IRQF_SAMPLE_RANDOM ; 
 int /*<<< orphan*/  IRQTF_DIED ; 
 int /*<<< orphan*/  IRQTF_RUNTHREAD ; 
#define  IRQ_HANDLED 129 
 int IRQ_NONE ; 
#define  IRQ_WAKE_THREAD 128 
 int /*<<< orphan*/  add_interrupt_randomness (unsigned int) ; 
 int /*<<< orphan*/  likely (int) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable_in_hardirq () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_irq_handler_entry (unsigned int,struct irqaction*) ; 
 int /*<<< orphan*/  trace_irq_handler_exit (unsigned int,struct irqaction*,int) ; 
 int /*<<< orphan*/  unlikely (int) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn_no_thread (unsigned int,struct irqaction*) ; 

irqreturn_t handle_IRQ_event(unsigned int irq, struct irqaction *action)
{
	irqreturn_t ret, retval = IRQ_NONE;
	unsigned int status = 0;

	if (!(action->flags & IRQF_DISABLED))
		local_irq_enable_in_hardirq();

	do {
		trace_irq_handler_entry(irq, action);
		ret = action->handler(irq, action->dev_id);
		trace_irq_handler_exit(irq, action, ret);

		switch (ret) {
		case IRQ_WAKE_THREAD:
			/*
			 * Set result to handled so the spurious check
			 * does not trigger.
			 */
			ret = IRQ_HANDLED;

			/*
			 * Catch drivers which return WAKE_THREAD but
			 * did not set up a thread function
			 */
			if (unlikely(!action->thread_fn)) {
				warn_no_thread(irq, action);
				break;
			}

			/*
			 * Wake up the handler thread for this
			 * action. In case the thread crashed and was
			 * killed we just pretend that we handled the
			 * interrupt. The hardirq handler above has
			 * disabled the device interrupt, so no irq
			 * storm is lurking.
			 */
			if (likely(!test_bit(IRQTF_DIED,
					     &action->thread_flags))) {
				set_bit(IRQTF_RUNTHREAD, &action->thread_flags);
				wake_up_process(action->thread);
			}

			/* Fall through to add to randomness */
		case IRQ_HANDLED:
			status |= action->flags;
			break;

		default:
			break;
		}

		retval |= ret;
		action = action->next;
	} while (action);

	if (status & IRQF_SAMPLE_RANDOM)
		add_interrupt_randomness(irq);
	local_irq_disable();

	return retval;
}