#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request_queue {TYPE_1__* elevator; } ;
struct request {int dummy; } ;
struct deadline_data {scalar_t__ batching; scalar_t__ fifo_batch; scalar_t__ writes_starved; struct request** next_rq; TYPE_2__* fifo_list; scalar_t__ starved; int /*<<< orphan*/ * sort_list; } ;
struct TYPE_4__ {int /*<<< orphan*/  next; } ;
struct TYPE_3__ {struct deadline_data* elevator_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 size_t READ ; 
 size_t WRITE ; 
 scalar_t__ deadline_check_fifo (struct deadline_data*,int) ; 
 int /*<<< orphan*/  deadline_move_request (struct deadline_data*,struct request*) ; 
 int /*<<< orphan*/  list_empty (TYPE_2__*) ; 
 struct request* rq_entry_fifo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int deadline_dispatch_requests(struct request_queue *q, int force)
{
	struct deadline_data *dd = q->elevator->elevator_data;
	const int reads = !list_empty(&dd->fifo_list[READ]);
	const int writes = !list_empty(&dd->fifo_list[WRITE]);
	struct request *rq;
	int data_dir;

	/*
	 * batches are currently reads XOR writes
	 */
	if (dd->next_rq[WRITE])
		rq = dd->next_rq[WRITE];
	else
		rq = dd->next_rq[READ];

	if (rq && dd->batching < dd->fifo_batch)
		/* we have a next request are still entitled to batch */
		goto dispatch_request;

	/*
	 * at this point we are not running a batch. select the appropriate
	 * data direction (read / write)
	 */

	if (reads) {
		BUG_ON(RB_EMPTY_ROOT(&dd->sort_list[READ]));

		if (writes && (dd->starved++ >= dd->writes_starved))
			goto dispatch_writes;

		data_dir = READ;

		goto dispatch_find_request;
	}

	/*
	 * there are either no reads or writes have been starved
	 */

	if (writes) {
dispatch_writes:
		BUG_ON(RB_EMPTY_ROOT(&dd->sort_list[WRITE]));

		dd->starved = 0;

		data_dir = WRITE;

		goto dispatch_find_request;
	}

	return 0;

dispatch_find_request:
	/*
	 * we are not running a batch, find best request for selected data_dir
	 */
	if (deadline_check_fifo(dd, data_dir) || !dd->next_rq[data_dir]) {
		/*
		 * A deadline has expired, the last request was in the other
		 * direction, or we have run out of higher-sectored requests.
		 * Start again from the request with the earliest expiry time.
		 */
		rq = rq_entry_fifo(dd->fifo_list[data_dir].next);
	} else {
		/*
		 * The last req was the same dir and we have a next request in
		 * sort order. No expired requests so continue on from here.
		 */
		rq = dd->next_rq[data_dir];
	}

	dd->batching = 0;

dispatch_request:
	/*
	 * rq is the selected appropriate request.
	 */
	dd->batching++;
	deadline_move_request(dd, rq);

	return 1;
}