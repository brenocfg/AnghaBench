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
struct request {int dummy; } ;
struct cfq_queue {struct request* next_rq; int /*<<< orphan*/  sort_list; } ;
struct cfq_io_context {TYPE_1__* ioc; } ;
struct cfq_data {struct cfq_io_context* active_cic; int /*<<< orphan*/  queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 struct cfq_io_context* RQ_CIC (struct request*) ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 struct request* cfq_check_fifo (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_dispatch_insert (int /*<<< orphan*/ ,struct request*) ; 
 int /*<<< orphan*/  cfq_may_dispatch (struct cfq_data*,struct cfq_queue*) ; 

__attribute__((used)) static bool cfq_dispatch_request(struct cfq_data *cfqd, struct cfq_queue *cfqq)
{
	struct request *rq;

	BUG_ON(RB_EMPTY_ROOT(&cfqq->sort_list));

	if (!cfq_may_dispatch(cfqd, cfqq))
		return false;

	/*
	 * follow expired path, else get first next available
	 */
	rq = cfq_check_fifo(cfqq);
	if (!rq)
		rq = cfqq->next_rq;

	/*
	 * insert request into driver dispatch list
	 */
	cfq_dispatch_insert(cfqd->queue, rq);

	if (!cfqd->active_cic) {
		struct cfq_io_context *cic = RQ_CIC(rq);

		atomic_long_inc(&cic->ioc->refcount);
		cfqd->active_cic = cic;
	}

	return true;
}