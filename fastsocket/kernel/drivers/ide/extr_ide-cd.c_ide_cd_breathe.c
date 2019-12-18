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
struct request {int errors; } ;
struct cdrom_info {scalar_t__ write_timeout; } ;
struct TYPE_3__ {struct request_queue* queue; struct cdrom_info* driver_data; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 scalar_t__ ATAPI_WAIT_WRITE_BUSY ; 
 int /*<<< orphan*/  blk_plug_device (struct request_queue*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int ide_cd_breathe(ide_drive_t *drive, struct request *rq)
{

	struct cdrom_info *info = drive->driver_data;

	if (!rq->errors)
		info->write_timeout = jiffies +	ATAPI_WAIT_WRITE_BUSY;

	rq->errors = 1;

	if (time_after(jiffies, info->write_timeout))
		return 0;
	else {
		struct request_queue *q = drive->queue;
		unsigned long flags;

		/*
		 * take a breather relying on the unplug timer to kick us again
		 */

		spin_lock_irqsave(q->queue_lock, flags);
		blk_plug_device(q);
		spin_unlock_irqrestore(q->queue_lock, flags);

		return 1;
	}
}