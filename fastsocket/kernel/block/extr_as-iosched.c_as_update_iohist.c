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
struct request {int dummy; } ;
struct as_io_context {unsigned long last_end_request; scalar_t__ last_request_pos; int /*<<< orphan*/  lock; int /*<<< orphan*/  state; int /*<<< orphan*/  nr_dispatched; int /*<<< orphan*/  nr_queued; } ;
struct as_data {int dummy; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  AS_TASK_IORUNNING ; 
 int /*<<< orphan*/  AS_TASK_IOSTARTED ; 
 int BLK_RW_SYNC ; 
 scalar_t__ MAX_THINKTIME ; 
 int /*<<< orphan*/  as_update_seekdist (struct as_data*,struct as_io_context*,scalar_t__) ; 
 int /*<<< orphan*/  as_update_thinktime (struct as_data*,struct as_io_context*,unsigned long) ; 
 unsigned long atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ blk_rq_pos (struct request*) ; 
 scalar_t__ blk_rq_sectors (struct request*) ; 
 unsigned long jiffies ; 
 unsigned long min (unsigned long,scalar_t__) ; 
 int rq_is_sync (struct request*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void as_update_iohist(struct as_data *ad, struct as_io_context *aic,
				struct request *rq)
{
	int data_dir = rq_is_sync(rq);
	unsigned long thinktime = 0;
	sector_t seek_dist;

	if (aic == NULL)
		return;

	if (data_dir == BLK_RW_SYNC) {
		unsigned long in_flight = atomic_read(&aic->nr_queued)
					+ atomic_read(&aic->nr_dispatched);
		spin_lock(&aic->lock);
		if (test_bit(AS_TASK_IORUNNING, &aic->state) ||
			test_bit(AS_TASK_IOSTARTED, &aic->state)) {
			/* Calculate read -> read thinktime */
			if (test_bit(AS_TASK_IORUNNING, &aic->state)
							&& in_flight == 0) {
				thinktime = jiffies - aic->last_end_request;
				thinktime = min(thinktime, MAX_THINKTIME-1);
			}
			as_update_thinktime(ad, aic, thinktime);

			/* Calculate read -> read seek distance */
			if (aic->last_request_pos < blk_rq_pos(rq))
				seek_dist = blk_rq_pos(rq) -
					    aic->last_request_pos;
			else
				seek_dist = aic->last_request_pos -
					    blk_rq_pos(rq);
			as_update_seekdist(ad, aic, seek_dist);
		}
		aic->last_request_pos = blk_rq_pos(rq) + blk_rq_sectors(rq);
		set_bit(AS_TASK_IOSTARTED, &aic->state);
		spin_unlock(&aic->lock);
	}
}