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
struct scsi_cmnd {int /*<<< orphan*/  request; TYPE_1__* device; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* function ) (int /*<<< orphan*/ ) ;} ;
struct sas_task_slow {TYPE_2__ timer; } ;
struct sas_task {int /*<<< orphan*/  dev; struct sas_task_slow* slow_task; struct scsi_cmnd* uldd_task; } ;
struct request_queue {int /*<<< orphan*/  queue_lock; } ;
struct TYPE_3__ {struct request_queue* request_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_abort_request (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer (TYPE_2__*) ; 
 scalar_t__ dev_is_sata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_ata_task_abort (struct sas_task*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void sas_task_abort(struct sas_task *task)
{
	struct scsi_cmnd *sc = task->uldd_task;

	/* Escape for libsas internal commands */
	if (!sc) {
		struct sas_task_slow *slow = task->slow_task;

		if (!slow)
			return;
		if (!del_timer(&slow->timer))
			return;
		slow->timer.function(slow->timer.data);
		return;
	}

	if (dev_is_sata(task->dev)) {
		sas_ata_task_abort(task);
	} else {
		struct request_queue *q = sc->device->request_queue;
		unsigned long flags;

		spin_lock_irqsave(q->queue_lock, flags);
		blk_abort_request(sc->request);
		spin_unlock_irqrestore(q->queue_lock, flags);
	}
}