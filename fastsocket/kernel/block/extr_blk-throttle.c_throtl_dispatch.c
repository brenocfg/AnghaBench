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
struct throtl_data {int /*<<< orphan*/ * nr_queued; } ;
struct request_queue {int /*<<< orphan*/  queue_lock; struct throtl_data* td; } ;
struct bio_list {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 size_t READ ; 
 size_t WRITE ; 
 int /*<<< orphan*/  bio_list_init (struct bio_list*) ; 
 struct bio* bio_list_pop (struct bio_list*) ; 
 int /*<<< orphan*/  blk_unplug (struct request_queue*) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  throtl_log (struct throtl_data*,char*,unsigned int,...) ; 
 int /*<<< orphan*/  throtl_process_limit_change (struct throtl_data*) ; 
 int /*<<< orphan*/  throtl_schedule_next_dispatch (struct throtl_data*) ; 
 unsigned int throtl_select_dispatch (struct throtl_data*,struct bio_list*) ; 
 int /*<<< orphan*/  total_nr_queued (struct throtl_data*) ; 

__attribute__((used)) static int throtl_dispatch(struct request_queue *q)
{
	struct throtl_data *td = q->td;
	unsigned int nr_disp = 0;
	struct bio_list bio_list_on_stack;
	struct bio *bio;

	spin_lock_irq(q->queue_lock);

	throtl_process_limit_change(td);

	if (!total_nr_queued(td))
		goto out;

	bio_list_init(&bio_list_on_stack);

	throtl_log(td, "dispatch nr_queued=%lu read=%u write=%u",
			total_nr_queued(td), td->nr_queued[READ],
			td->nr_queued[WRITE]);

	nr_disp = throtl_select_dispatch(td, &bio_list_on_stack);

	if (nr_disp)
		throtl_log(td, "bios disp=%u", nr_disp);

	throtl_schedule_next_dispatch(td);
out:
	spin_unlock_irq(q->queue_lock);

	/*
	 * If we dispatched some requests, unplug the queue to make sure
	 * immediate dispatch
	 */
	if (nr_disp) {
		while((bio = bio_list_pop(&bio_list_on_stack)))
			generic_make_request(bio);
		blk_unplug(q);
	}
	return nr_disp;
}