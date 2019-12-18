#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sched_param {int sched_priority; } ;
struct irqaction {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev_id; int /*<<< orphan*/  (* thread_fn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct irq_desc {int status; int /*<<< orphan*/  wait_for_threads; int /*<<< orphan*/  threads_active; int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {struct irqaction* irqaction; } ;

/* Variables and functions */
 int IRQ_DISABLED ; 
 int IRQ_ONESHOT ; 
 int IRQ_PENDING ; 
 int MAX_USER_RT_PRIO ; 
 int /*<<< orphan*/  SCHED_FIFO ; 
 int atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  irq_finalize_oneshot (int /*<<< orphan*/ ,struct irq_desc*) ; 
 int /*<<< orphan*/  irq_thread_check_affinity (struct irq_desc*,struct irqaction*) ; 
 struct irq_desc* irq_to_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_wait_for_interrupt (struct irqaction*) ; 
 int /*<<< orphan*/  sched_setscheduler (TYPE_1__*,int /*<<< orphan*/ ,struct sched_param*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int irq_thread(void *data)
{
	struct sched_param param = { .sched_priority = MAX_USER_RT_PRIO/2, };
	struct irqaction *action = data;
	struct irq_desc *desc = irq_to_desc(action->irq);
	int wake, oneshot = desc->status & IRQ_ONESHOT;

	sched_setscheduler(current, SCHED_FIFO, &param);
	current->irqaction = action;

	while (!irq_wait_for_interrupt(action)) {

		irq_thread_check_affinity(desc, action);

		atomic_inc(&desc->threads_active);

		spin_lock_irq(&desc->lock);
		if (unlikely(desc->status & IRQ_DISABLED)) {
			/*
			 * CHECKME: We might need a dedicated
			 * IRQ_THREAD_PENDING flag here, which
			 * retriggers the thread in check_irq_resend()
			 * but AFAICT IRQ_PENDING should be fine as it
			 * retriggers the interrupt itself --- tglx
			 */
			desc->status |= IRQ_PENDING;
			spin_unlock_irq(&desc->lock);
		} else {
			spin_unlock_irq(&desc->lock);

			action->thread_fn(action->irq, action->dev_id);

			if (oneshot)
				irq_finalize_oneshot(action->irq, desc);
		}

		wake = atomic_dec_and_test(&desc->threads_active);

		if (wake && waitqueue_active(&desc->wait_for_threads))
			wake_up(&desc->wait_for_threads);
	}

	/*
	 * Clear irqaction. Otherwise exit_irq_thread() would make
	 * fuzz about an active irq thread going into nirvana.
	 */
	current->irqaction = NULL;
	return 0;
}