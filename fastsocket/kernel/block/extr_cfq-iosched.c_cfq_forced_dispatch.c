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
struct cfq_queue {int dummy; } ;
struct cfq_data {int /*<<< orphan*/  busy_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ __cfq_forced_dispatch_cfqq (struct cfq_queue*) ; 
 int /*<<< orphan*/  __cfq_set_active_queue (struct cfq_data*,struct cfq_queue*) ; 
 struct cfq_queue* cfq_get_next_queue_forced (struct cfq_data*) ; 
 int /*<<< orphan*/  cfq_log (struct cfq_data*,char*,int) ; 
 int /*<<< orphan*/  cfq_slice_expired (struct cfq_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cfq_forced_dispatch(struct cfq_data *cfqd)
{
	struct cfq_queue *cfqq;
	int dispatched = 0;

	/* Expire the timeslice of the current active queue first */
	cfq_slice_expired(cfqd, 0);
	while ((cfqq = cfq_get_next_queue_forced(cfqd)) != NULL) {
		__cfq_set_active_queue(cfqd, cfqq);
		dispatched += __cfq_forced_dispatch_cfqq(cfqq);
	}

	BUG_ON(cfqd->busy_queues);

	cfq_log(cfqd, "forced_dispatch=%d", dispatched);
	return dispatched;
}