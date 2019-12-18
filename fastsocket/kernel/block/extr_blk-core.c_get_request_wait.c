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
struct request_list {int /*<<< orphan*/ * wait; } ;
struct request_queue {int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  node; struct request_list rq; } ;
struct request {int dummy; } ;
struct io_context {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __generic_unplug_device (struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_dead (struct request_queue*) ; 
 struct io_context* current_io_context (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct request* get_request (struct request_queue*,int,struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_schedule () ; 
 int /*<<< orphan*/  ioc_set_batching (struct request_queue*,struct io_context*) ; 
 int /*<<< orphan*/  prepare_to_wait_exclusive (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ rw_is_sync (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_block_sleeprq (struct request_queue*,struct bio*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static struct request *get_request_wait(struct request_queue *q, int rw_flags,
					struct bio *bio)
{
	const bool is_sync = rw_is_sync(rw_flags) != 0;
	struct request *rq;

	rq = get_request(q, rw_flags, bio, GFP_NOIO);
	while (!rq) {
		DEFINE_WAIT(wait);
		struct io_context *ioc;
		struct request_list *rl = &q->rq;

		if (unlikely(blk_queue_dead(q)))
			return NULL;

		prepare_to_wait_exclusive(&rl->wait[is_sync], &wait,
				TASK_UNINTERRUPTIBLE);

		trace_block_sleeprq(q, bio, rw_flags & 1);

		__generic_unplug_device(q);
		spin_unlock_irq(q->queue_lock);
		io_schedule();

		/*
		 * After sleeping, we become a "batching" process and
		 * will be able to allocate at least one request, and
		 * up to a big batch of them for a small period time.
		 * See ioc_batching, ioc_set_batching
		 */
		ioc = current_io_context(GFP_NOIO, q->node);
		ioc_set_batching(q, ioc);

		spin_lock_irq(q->queue_lock);
		finish_wait(&rl->wait[is_sync], &wait);

		rq = get_request(q, rw_flags, bio, GFP_NOIO);
	};

	return rq;
}