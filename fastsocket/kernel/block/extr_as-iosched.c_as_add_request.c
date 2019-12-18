#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int /*<<< orphan*/  node; TYPE_1__* elevator; } ;
struct request {int /*<<< orphan*/  queuelist; int /*<<< orphan*/ * elevator_private; } ;
struct as_data {int /*<<< orphan*/ * fifo_list; scalar_t__* fifo_expire; } ;
struct TYPE_6__ {TYPE_2__* aic; } ;
struct TYPE_5__ {int /*<<< orphan*/  nr_queued; } ;
struct TYPE_4__ {struct as_data* elevator_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS_RQ_NEW ; 
 int /*<<< orphan*/  AS_RQ_QUEUED ; 
 TYPE_3__* RQ_IOC (struct request*) ; 
 int /*<<< orphan*/  RQ_RB_ROOT (struct as_data*,struct request*) ; 
 int /*<<< orphan*/  RQ_SET_STATE (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  as_get_io_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  as_update_iohist (struct as_data*,TYPE_2__*,struct request*) ; 
 int /*<<< orphan*/  as_update_rq (struct as_data*,struct request*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elv_rb_add (int /*<<< orphan*/ ,struct request*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int rq_is_sync (struct request*) ; 
 int /*<<< orphan*/  rq_set_fifo_time (struct request*,scalar_t__) ; 

__attribute__((used)) static void as_add_request(struct request_queue *q, struct request *rq)
{
	struct as_data *ad = q->elevator->elevator_data;
	int data_dir;

	RQ_SET_STATE(rq, AS_RQ_NEW);

	data_dir = rq_is_sync(rq);

	rq->elevator_private[0] = as_get_io_context(q->node);

	if (RQ_IOC(rq)) {
		as_update_iohist(ad, RQ_IOC(rq)->aic, rq);
		atomic_inc(&RQ_IOC(rq)->aic->nr_queued);
	}

	elv_rb_add(RQ_RB_ROOT(ad, rq), rq);

	/*
	 * set expire time and add to fifo list
	 */
	rq_set_fifo_time(rq, jiffies + ad->fifo_expire[data_dir]);
	list_add_tail(&rq->queuelist, &ad->fifo_list[data_dir]);

	as_update_rq(ad, rq); /* keep state machine up to date */
	RQ_SET_STATE(rq, AS_RQ_QUEUED);
}