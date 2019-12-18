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
struct qdio_q {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  qdio_inbound_q_done (struct qdio_q*) ; 
 int /*<<< orphan*/  qdio_inbound_q_moved (struct qdio_q*) ; 
 int /*<<< orphan*/  qdio_kick_handler (struct qdio_q*) ; 
 int /*<<< orphan*/  qdio_stop_polling (struct qdio_q*) ; 
 int /*<<< orphan*/  qperf_inc (struct qdio_q*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_inbound ; 
 int /*<<< orphan*/  tasklet_inbound_resched ; 
 int /*<<< orphan*/  tasklet_inbound_resched2 ; 

__attribute__((used)) static void __qdio_inbound_processing(struct qdio_q *q)
{
	qperf_inc(q, tasklet_inbound);
again:
	if (!qdio_inbound_q_moved(q))
		return;

	qdio_kick_handler(q);

	if (!qdio_inbound_q_done(q)) {
		/* means poll time is not yet over */
		qperf_inc(q, tasklet_inbound_resched);
		goto again;
	}

	qdio_stop_polling(q);
	/*
	 * We need to check again to not lose initiative after
	 * resetting the ACK state.
	 */
	if (!qdio_inbound_q_done(q)) {
		qperf_inc(q, tasklet_inbound_resched2);
		goto again;
	}
}