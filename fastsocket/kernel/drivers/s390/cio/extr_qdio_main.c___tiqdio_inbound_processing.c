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
struct qdio_q {int /*<<< orphan*/  tasklet; TYPE_1__* irq_ptr; } ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ QDIO_IRQ_STATE_STOPPED ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  qdio_check_outbound_after_thinint (struct qdio_q*) ; 
 int /*<<< orphan*/  qdio_inbound_q_done (struct qdio_q*) ; 
 int /*<<< orphan*/  qdio_inbound_q_moved (struct qdio_q*) ; 
 int /*<<< orphan*/  qdio_kick_handler (struct qdio_q*) ; 
 int /*<<< orphan*/  qdio_stop_polling (struct qdio_q*) ; 
 int /*<<< orphan*/  qdio_sync_after_thinint (struct qdio_q*) ; 
 int /*<<< orphan*/  qperf_inc (struct qdio_q*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_inbound ; 
 int /*<<< orphan*/  tasklet_inbound_resched ; 
 int /*<<< orphan*/  tasklet_inbound_resched2 ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __tiqdio_inbound_processing(struct qdio_q *q)
{
	qperf_inc(q, tasklet_inbound);
	qdio_sync_after_thinint(q);

	/*
	 * The interrupt could be caused by a PCI request. Check the
	 * PCI capable outbound queues.
	 */
	qdio_check_outbound_after_thinint(q);

	if (!qdio_inbound_q_moved(q))
		return;

	qdio_kick_handler(q);

	if (!qdio_inbound_q_done(q)) {
		qperf_inc(q, tasklet_inbound_resched);
		if (likely(q->irq_ptr->state != QDIO_IRQ_STATE_STOPPED)) {
			tasklet_schedule(&q->tasklet);
			return;
		}
	}

	qdio_stop_polling(q);
	/*
	 * We need to check again to not lose initiative after
	 * resetting the ACK state.
	 */
	if (!qdio_inbound_q_done(q)) {
		qperf_inc(q, tasklet_inbound_resched2);
		if (likely(q->irq_ptr->state != QDIO_IRQ_STATE_STOPPED))
			tasklet_schedule(&q->tasklet);
	}
}