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
struct smtc_ipi_q {scalar_t__ resched_flag; int /*<<< orphan*/  lock; int /*<<< orphan*/ * head; } ;
struct smtc_ipi {scalar_t__ type; scalar_t__ arg; } ;

/* Variables and functions */
 struct smtc_ipi_q* IPIQ ; 
 scalar_t__ LINUX_SMP_IPI ; 
 int SMP_RESCHEDULE_YOURSELF ; 
 int /*<<< orphan*/  __raw_local_irq_restore (unsigned long) ; 
 struct smtc_ipi* __smtc_ipi_dq (struct smtc_ipi_q*) ; 
 int /*<<< orphan*/  ipi_decode (struct smtc_ipi*) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void deferred_smtc_ipi(void)
{
	int cpu = smp_processor_id();

	/*
	 * Test is not atomic, but much faster than a dequeue,
	 * and the vast majority of invocations will have a null queue.
	 * If irq_disabled when this was called, then any IPIs queued
	 * after we test last will be taken on the next irq_enable/restore.
	 * If interrupts were enabled, then any IPIs added after the
	 * last test will be taken directly.
	 */

	while (IPIQ[cpu].head != NULL) {
		struct smtc_ipi_q *q = &IPIQ[cpu];
		struct smtc_ipi *pipi;
		unsigned long flags;

		/*
		 * It may be possible we'll come in with interrupts
		 * already enabled.
		 */
		local_irq_save(flags);
		spin_lock(&q->lock);
		pipi = __smtc_ipi_dq(q);
		spin_unlock(&q->lock);
		if (pipi != NULL) {
			if (pipi->type == LINUX_SMP_IPI &&
			    (int)pipi->arg == SMP_RESCHEDULE_YOURSELF)
				IPIQ[cpu].resched_flag = 0;
			ipi_decode(pipi);
		}
		/*
		 * The use of the __raw_local restore isn't
		 * as obviously necessary here as in smtc_ipi_replay(),
		 * but it's more efficient, given that we're already
		 * running down the IPI queue.
		 */
		__raw_local_irq_restore(flags);
	}
}