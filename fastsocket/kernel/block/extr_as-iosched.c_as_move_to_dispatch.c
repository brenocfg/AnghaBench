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
struct request {int /*<<< orphan*/  rb_node; } ;
struct io_context {TYPE_1__* aic; } ;
struct as_data {scalar_t__ current_write_count; int /*<<< orphan*/  nr_dispatched; int /*<<< orphan*/  q; int /*<<< orphan*/ * next_rq; scalar_t__ ioc_finished; int /*<<< orphan*/ * io_context; scalar_t__* last_sector; int /*<<< orphan*/  antic_status; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr_dispatched; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANTIC_OFF ; 
 int /*<<< orphan*/  AS_RQ_DISPATCHED ; 
 scalar_t__ AS_RQ_QUEUED ; 
 int const BLK_RW_SYNC ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 
 struct io_context* RQ_IOC (struct request*) ; 
 int /*<<< orphan*/  RQ_SET_STATE (struct request*,int /*<<< orphan*/ ) ; 
 scalar_t__ RQ_STATE (struct request*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  as_antic_stop (struct as_data*) ; 
 int /*<<< orphan*/  as_find_next_rq (struct as_data*,struct request*) ; 
 int /*<<< orphan*/  as_remove_queued_request (int /*<<< orphan*/ ,struct request*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ blk_rq_pos (struct request*) ; 
 scalar_t__ blk_rq_sectors (struct request*) ; 
 int /*<<< orphan*/  copy_io_context (int /*<<< orphan*/ **,struct io_context**) ; 
 int /*<<< orphan*/  elv_dispatch_sort (int /*<<< orphan*/ ,struct request*) ; 
 int /*<<< orphan*/  put_io_context (int /*<<< orphan*/ *) ; 
 int rq_is_sync (struct request*) ; 

__attribute__((used)) static void as_move_to_dispatch(struct as_data *ad, struct request *rq)
{
	const int data_dir = rq_is_sync(rq);

	BUG_ON(RB_EMPTY_NODE(&rq->rb_node));

	as_antic_stop(ad);
	ad->antic_status = ANTIC_OFF;

	/*
	 * This has to be set in order to be correctly updated by
	 * as_find_next_rq
	 */
	ad->last_sector[data_dir] = blk_rq_pos(rq) + blk_rq_sectors(rq);

	if (data_dir == BLK_RW_SYNC) {
		struct io_context *ioc = RQ_IOC(rq);
		/* In case we have to anticipate after this */
		copy_io_context(&ad->io_context, &ioc);
	} else {
		if (ad->io_context) {
			put_io_context(ad->io_context);
			ad->io_context = NULL;
		}

		if (ad->current_write_count != 0)
			ad->current_write_count--;
	}
	ad->ioc_finished = 0;

	ad->next_rq[data_dir] = as_find_next_rq(ad, rq);

	/*
	 * take it off the sort and fifo list, add to dispatch queue
	 */
	as_remove_queued_request(ad->q, rq);
	WARN_ON(RQ_STATE(rq) != AS_RQ_QUEUED);

	elv_dispatch_sort(ad->q, rq);

	RQ_SET_STATE(rq, AS_RQ_DISPATCHED);
	if (RQ_IOC(rq) && RQ_IOC(rq)->aic)
		atomic_inc(&RQ_IOC(rq)->aic->nr_dispatched);
	ad->nr_dispatched++;
}