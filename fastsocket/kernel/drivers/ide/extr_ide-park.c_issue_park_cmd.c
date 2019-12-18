#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int dummy; } ;
struct request {int cmd_len; unsigned long* special; void* cmd_type; int /*<<< orphan*/ * cmd; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  timer; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_5__ {int dev_flags; unsigned long sleep; struct request_queue* queue; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  ELEVATOR_INSERT_FRONT ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int IDE_DFLAG_PARKED ; 
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  REQ_PARK_HEADS ; 
 void* REQ_TYPE_SPECIAL ; 
 int /*<<< orphan*/  REQ_UNPARK_HEADS ; 
 int /*<<< orphan*/  __GFP_WAIT ; 
 int blk_execute_rq (struct request_queue*,int /*<<< orphan*/ *,struct request*,int) ; 
 struct request* blk_get_request (struct request_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_put_request (struct request*) ; 
 int /*<<< orphan*/  blk_run_queue (struct request_queue*) ; 
 scalar_t__ del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elv_add_request (struct request_queue*,struct request*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ide_park_wq ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int time_before (unsigned long,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void issue_park_cmd(ide_drive_t *drive, unsigned long timeout)
{
	ide_hwif_t *hwif = drive->hwif;
	struct request_queue *q = drive->queue;
	struct request *rq;
	int rc;

	timeout += jiffies;
	spin_lock_irq(&hwif->lock);
	if (drive->dev_flags & IDE_DFLAG_PARKED) {
		int reset_timer = time_before(timeout, drive->sleep);
		int start_queue = 0;

		drive->sleep = timeout;
		wake_up_all(&ide_park_wq);
		if (reset_timer && del_timer(&hwif->timer))
			start_queue = 1;
		spin_unlock_irq(&hwif->lock);

		if (start_queue)
			blk_run_queue(q);
		return;
	}
	spin_unlock_irq(&hwif->lock);

	rq = blk_get_request(q, READ, __GFP_WAIT);
	rq->cmd[0] = REQ_PARK_HEADS;
	rq->cmd_len = 1;
	rq->cmd_type = REQ_TYPE_SPECIAL;
	rq->special = &timeout;
	rc = blk_execute_rq(q, NULL, rq, 1);
	blk_put_request(rq);
	if (rc)
		goto out;

	/*
	 * Make sure that *some* command is sent to the drive after the
	 * timeout has expired, so power management will be reenabled.
	 */
	rq = blk_get_request(q, READ, GFP_NOWAIT);
	if (unlikely(!rq))
		goto out;

	rq->cmd[0] = REQ_UNPARK_HEADS;
	rq->cmd_len = 1;
	rq->cmd_type = REQ_TYPE_SPECIAL;
	elv_add_request(q, rq, ELEVATOR_INSERT_FRONT, 1);

out:
	return;
}