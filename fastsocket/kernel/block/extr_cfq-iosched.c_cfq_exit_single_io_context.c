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
struct request_queue {int /*<<< orphan*/  queue_lock; } ;
struct io_context {int dummy; } ;
struct cfq_io_context {struct cfq_data* key; } ;
struct cfq_data {struct request_queue* queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cfq_exit_single_io_context (struct cfq_data*,struct cfq_io_context*) ; 
 int /*<<< orphan*/  smp_read_barrier_depends () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void cfq_exit_single_io_context(struct io_context *ioc,
				       struct cfq_io_context *cic)
{
	struct cfq_data *cfqd = cic->key;

	if (cfqd) {
		struct request_queue *q = cfqd->queue;
		unsigned long flags;

		spin_lock_irqsave(q->queue_lock, flags);

		/*
		 * Ensure we get a fresh copy of the ->key to prevent
		 * race between exiting task and queue
		 */
		smp_read_barrier_depends();
		if (cic->key)
			__cfq_exit_single_io_context(cfqd, cic);

		spin_unlock_irqrestore(q->queue_lock, flags);
	}
}