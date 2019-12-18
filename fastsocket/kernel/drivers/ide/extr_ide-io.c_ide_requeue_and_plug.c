#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int /*<<< orphan*/  queue_lock; } ;
struct request {int dummy; } ;
struct TYPE_3__ {struct request_queue* queue; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  blk_plug_device (struct request_queue*) ; 
 int /*<<< orphan*/  blk_requeue_request (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  elv_queue_empty (struct request_queue*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void ide_requeue_and_plug(ide_drive_t *drive, struct request *rq)
{
	struct request_queue *q = drive->queue;
	unsigned long flags;

	spin_lock_irqsave(q->queue_lock, flags);

	if (rq)
		blk_requeue_request(q, rq);
	if (!elv_queue_empty(q))
		blk_plug_device(q);

	spin_unlock_irqrestore(q->queue_lock, flags);
}