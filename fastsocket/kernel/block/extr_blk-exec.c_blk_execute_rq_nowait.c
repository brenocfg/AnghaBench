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
struct request_queue {int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  (* request_fn ) (struct request_queue*) ;} ;
struct request {scalar_t__ cmd_type; int /*<<< orphan*/  errors; int /*<<< orphan*/  cmd_flags; int /*<<< orphan*/ * end_io; struct gendisk* rq_disk; } ;
struct gendisk {int dummy; } ;
typedef  int /*<<< orphan*/  rq_end_io_fn ;

/* Variables and functions */
 int ELEVATOR_INSERT_BACK ; 
 int ELEVATOR_INSERT_FRONT ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  REQ_QUIET ; 
 scalar_t__ REQ_TYPE_PM_RESUME ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __blk_end_request_all (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __elv_add_request (struct request_queue*,struct request*,int,int) ; 
 int /*<<< orphan*/  __generic_unplug_device (struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_dead (struct request_queue*) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct request_queue*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void blk_execute_rq_nowait(struct request_queue *q, struct gendisk *bd_disk,
			   struct request *rq, int at_head,
			   rq_end_io_fn *done)
{
	int where = at_head ? ELEVATOR_INSERT_FRONT : ELEVATOR_INSERT_BACK;

	WARN_ON(irqs_disabled());

	rq->rq_disk = bd_disk;
	rq->end_io = done;

	spin_lock_irq(q->queue_lock);

	if (unlikely(blk_queue_dead(q))) {
		rq->cmd_flags |= REQ_QUIET; 
		rq->errors = -ENXIO;
		__blk_end_request_all(rq, rq->errors);
		spin_unlock_irq(q->queue_lock);
		return;
	}

	__elv_add_request(q, rq, where, 1);
	__generic_unplug_device(q);
	/* the queue is stopped so it won't be plugged+unplugged */
	if (rq->cmd_type == REQ_TYPE_PM_RESUME)
		q->request_fn(q);
	spin_unlock_irq(q->queue_lock);
}