#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {scalar_t__* cmnd; TYPE_3__* device; scalar_t__ tag; int /*<<< orphan*/  SCp; } ;
struct TYPE_15__ {int clockrate; int /*<<< orphan*/  sync_max_depth; } ;
struct TYPE_14__ {int* cfg; int /*<<< orphan*/  msgs; int /*<<< orphan*/  SCp; int /*<<< orphan*/  phase; } ;
struct TYPE_11__ {int /*<<< orphan*/  transfer_type; } ;
struct TYPE_16__ {TYPE_5__ ifcfg; TYPE_4__ scsi; TYPE_2__* device; TYPE_1__ dma; struct scsi_cmnd* SCpnt; } ;
struct TYPE_13__ {size_t id; int /*<<< orphan*/  lun; } ;
struct TYPE_12__ {scalar_t__ sync_state; int /*<<< orphan*/  disconnect_ok; } ;
typedef  TYPE_6__ FAS216_Info ;

/* Variables and functions */
 int CNTL1_PTE ; 
 int /*<<< orphan*/  EXTENDED_MESSAGE ; 
 int /*<<< orphan*/  EXTENDED_SDTR ; 
 int /*<<< orphan*/  IDENTIFY (int,int /*<<< orphan*/ ) ; 
 scalar_t__ INQUIRY ; 
 int /*<<< orphan*/  PHASE_SELECTION ; 
 int /*<<< orphan*/  REG_CNTL1 ; 
 scalar_t__ REQUEST_SENSE ; 
 int /*<<< orphan*/  SIMPLE_QUEUE_TAG ; 
 int /*<<< orphan*/  __fas216_start_command (TYPE_6__*,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  fas216_writeb (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fasdma_none ; 
 int /*<<< orphan*/  msgqueue_addmsg (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  msgqueue_flush (int /*<<< orphan*/ *) ; 
 scalar_t__ neg_complete ; 
 scalar_t__ neg_inprogress ; 
 scalar_t__ neg_wait ; 
 scalar_t__ parity_test (TYPE_6__*,size_t) ; 

__attribute__((used)) static void fas216_start_command(FAS216_Info *info, struct scsi_cmnd *SCpnt)
{
	int disconnect_ok;

	/*
	 * claim host busy
	 */
	info->scsi.phase = PHASE_SELECTION;
	info->scsi.SCp = SCpnt->SCp;
	info->SCpnt = SCpnt;
	info->dma.transfer_type = fasdma_none;

	if (parity_test(info, SCpnt->device->id))
		fas216_writeb(info, REG_CNTL1, info->scsi.cfg[0] | CNTL1_PTE);
	else
		fas216_writeb(info, REG_CNTL1, info->scsi.cfg[0]);

	/*
	 * Don't allow request sense commands to disconnect.
	 */
	disconnect_ok = SCpnt->cmnd[0] != REQUEST_SENSE &&
			info->device[SCpnt->device->id].disconnect_ok;

	/*
	 * build outgoing message bytes
	 */
	msgqueue_flush(&info->scsi.msgs);
	msgqueue_addmsg(&info->scsi.msgs, 1, IDENTIFY(disconnect_ok, SCpnt->device->lun));

	/*
	 * add tag message if required
	 */
	if (SCpnt->tag)
		msgqueue_addmsg(&info->scsi.msgs, 2, SIMPLE_QUEUE_TAG, SCpnt->tag);

	do {
#ifdef SCSI2_SYNC
		if ((info->device[SCpnt->device->id].sync_state == neg_wait ||
		     info->device[SCpnt->device->id].sync_state == neg_complete) &&
		    (SCpnt->cmnd[0] == REQUEST_SENSE ||
		     SCpnt->cmnd[0] == INQUIRY)) {
			info->device[SCpnt->device->id].sync_state = neg_inprogress;
			msgqueue_addmsg(&info->scsi.msgs, 5,
					EXTENDED_MESSAGE, 3, EXTENDED_SDTR,
					1000 / info->ifcfg.clockrate,
					info->ifcfg.sync_max_depth);
			break;
		}
#endif
	} while (0);

	__fas216_start_command(info, SCpnt);
}