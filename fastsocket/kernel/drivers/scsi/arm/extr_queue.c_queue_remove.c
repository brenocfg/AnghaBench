#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  next; } ;
struct TYPE_5__ {int /*<<< orphan*/  queue_lock; TYPE_3__ head; } ;
typedef  TYPE_1__ Queue_t ;

/* Variables and functions */
 struct scsi_cmnd* __queue_remove (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (TYPE_3__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct scsi_cmnd *queue_remove(Queue_t *queue)
{
	unsigned long flags;
	struct scsi_cmnd *SCpnt = NULL;

	spin_lock_irqsave(&queue->queue_lock, flags);
	if (!list_empty(&queue->head))
		SCpnt = __queue_remove(queue, queue->head.next);
	spin_unlock_irqrestore(&queue->queue_lock, flags);

	return SCpnt;
}