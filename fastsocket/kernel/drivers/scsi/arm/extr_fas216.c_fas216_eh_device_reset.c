#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct scsi_cmnd {int /*<<< orphan*/ * host_scribble; TYPE_4__* device; } ;
struct TYPE_24__ {TYPE_8__* device; } ;
struct TYPE_23__ {int id; } ;
struct TYPE_22__ {TYPE_6__* device; } ;
struct TYPE_21__ {int id; } ;
struct TYPE_20__ {int /*<<< orphan*/  disconnected; int /*<<< orphan*/  issue; } ;
struct TYPE_19__ {int id; TYPE_1__* host; } ;
struct TYPE_18__ {TYPE_2__* device; } ;
struct TYPE_17__ {scalar_t__ id; } ;
struct TYPE_16__ {scalar_t__ hostdata; } ;
struct TYPE_14__ {scalar_t__ phase; int /*<<< orphan*/  disconnectable; } ;
struct TYPE_15__ {int rst_dev_status; int /*<<< orphan*/  host_lock; struct scsi_cmnd* rstSCpnt; int /*<<< orphan*/  eh_timer; int /*<<< orphan*/  eh_wait; TYPE_10__ scsi; int /*<<< orphan*/  busyluns; TYPE_9__* reqSCpnt; TYPE_7__* origSCpnt; TYPE_5__ queues; TYPE_3__* SCpnt; } ;
typedef  TYPE_11__ FAS216_Info ;

/* Variables and functions */
 int FAILED ; 
 int HZ ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 scalar_t__ PHASE_IDLE ; 
 int SUCCESS ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ fas216_devicereset_done ; 
 int /*<<< orphan*/  fas216_kick (TYPE_11__*) ; 
 int /*<<< orphan*/  fas216_log (TYPE_11__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  queue_remove_all_target (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

int fas216_eh_device_reset(struct scsi_cmnd *SCpnt)
{
	FAS216_Info *info = (FAS216_Info *)SCpnt->device->host->hostdata;
	unsigned long flags;
	int i, res = FAILED, target = SCpnt->device->id;

	fas216_log(info, LOG_ERROR, "device reset for target %d", target);

	spin_lock_irqsave(&info->host_lock, flags);

	do {
		/*
		 * If we are currently connected to a device, and
		 * it is the device we want to reset, there is
		 * nothing we can do here.  Chances are it is stuck,
		 * and we need a bus reset.
		 */
		if (info->SCpnt && !info->scsi.disconnectable &&
		    info->SCpnt->device->id == SCpnt->device->id)
			break;

		/*
		 * We're going to be resetting this device.  Remove
		 * all pending commands from the driver.  By doing
		 * so, we guarantee that we won't touch the command
		 * structures except to process the reset request.
		 */
		queue_remove_all_target(&info->queues.issue, target);
		queue_remove_all_target(&info->queues.disconnected, target);
		if (info->origSCpnt && info->origSCpnt->device->id == target)
			info->origSCpnt = NULL;
		if (info->reqSCpnt && info->reqSCpnt->device->id == target)
			info->reqSCpnt = NULL;
		for (i = 0; i < 8; i++)
			clear_bit(target * 8 + i, info->busyluns);

		/*
		 * Hijack this SCSI command structure to send
		 * a bus device reset message to this device.
		 */
		SCpnt->host_scribble = (void *)fas216_devicereset_done;

		info->rst_dev_status = 0;
		info->rstSCpnt = SCpnt;

		if (info->scsi.phase == PHASE_IDLE)
			fas216_kick(info);

		mod_timer(&info->eh_timer, 30 * HZ);
		spin_unlock_irqrestore(&info->host_lock, flags);

		/*
		 * Wait up to 30 seconds for the reset to complete.
		 */
		wait_event(info->eh_wait, info->rst_dev_status);

		del_timer_sync(&info->eh_timer);
		spin_lock_irqsave(&info->host_lock, flags);
		info->rstSCpnt = NULL;

		if (info->rst_dev_status == 1)
			res = SUCCESS;
	} while (0);

	SCpnt->host_scribble = NULL;
	spin_unlock_irqrestore(&info->host_lock, flags);

	fas216_log(info, LOG_ERROR, "device reset complete: %s\n",
		   res == SUCCESS ? "success" : "failed");

	return res;
}