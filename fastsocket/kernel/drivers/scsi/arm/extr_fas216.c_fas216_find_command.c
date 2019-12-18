#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_3__* device; } ;
typedef  enum res_find { ____Placeholder_res_find } res_find ;
struct TYPE_7__ {int phase; int /*<<< orphan*/  disconnectable; } ;
struct TYPE_6__ {int /*<<< orphan*/  disconnected; int /*<<< orphan*/  issue; } ;
struct TYPE_9__ {int /*<<< orphan*/  busyluns; struct scsi_cmnd* origSCpnt; struct scsi_cmnd* SCpnt; TYPE_2__ scsi; TYPE_1__ queues; } ;
struct TYPE_8__ {int id; scalar_t__ lun; } ;
typedef  TYPE_4__ FAS216_Info ;

/* Variables and functions */
#define  PHASE_IDLE 128 
 int /*<<< orphan*/  clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 
 scalar_t__ queue_remove_cmd (int /*<<< orphan*/ *,struct scsi_cmnd*) ; 
 int res_failed ; 
 int res_hw_abort ; 
 int res_success ; 

__attribute__((used)) static enum res_find fas216_find_command(FAS216_Info *info,
					 struct scsi_cmnd *SCpnt)
{
	enum res_find res = res_failed;

	if (queue_remove_cmd(&info->queues.issue, SCpnt)) {
		/*
		 * The command was on the issue queue, and has not been
		 * issued yet.  We can remove the command from the queue,
		 * and acknowledge the abort.  Neither the device nor the
		 * interface know about the command.
		 */
		printk("on issue queue ");

		res = res_success;
	} else if (queue_remove_cmd(&info->queues.disconnected, SCpnt)) {
		/*
		 * The command was on the disconnected queue.  We must
		 * reconnect with the device if possible, and send it
		 * an abort message.
		 */
		printk("on disconnected queue ");

		res = res_hw_abort;
	} else if (info->SCpnt == SCpnt) {
		printk("executing ");

		switch (info->scsi.phase) {
		/*
		 * If the interface is idle, and the command is 'disconnectable',
		 * then it is the same as on the disconnected queue.
		 */
		case PHASE_IDLE:
			if (info->scsi.disconnectable) {
				info->scsi.disconnectable = 0;
				info->SCpnt = NULL;
				res = res_hw_abort;
			}
			break;

		default:
			break;
		}
	} else if (info->origSCpnt == SCpnt) {
		/*
		 * The command will be executed next, but a command
		 * is currently using the interface.  This is similar to
		 * being on the issue queue, except the busylun bit has
		 * been set.
		 */
		info->origSCpnt = NULL;
		clear_bit(SCpnt->device->id * 8 + SCpnt->device->lun, info->busyluns);
		printk("waiting for execution ");
		res = res_success;
	} else
		printk("unknown ");

	return res;
}