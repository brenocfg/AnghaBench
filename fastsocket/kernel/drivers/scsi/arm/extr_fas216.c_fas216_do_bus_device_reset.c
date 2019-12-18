#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_3__* device; int /*<<< orphan*/  SCp; } ;
struct message {int fifo; } ;
struct TYPE_15__ {int /*<<< orphan*/  msgs; int /*<<< orphan*/  SCp; int /*<<< orphan*/  phase; } ;
struct TYPE_13__ {int /*<<< orphan*/  select_timeout; } ;
struct TYPE_12__ {int /*<<< orphan*/  transfer_type; } ;
struct TYPE_16__ {TYPE_4__ scsi; TYPE_2__ ifcfg; TYPE_1__ dma; struct scsi_cmnd* SCpnt; } ;
struct TYPE_14__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_5__ FAS216_Info ;

/* Variables and functions */
 int /*<<< orphan*/  BUSID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUS_DEVICE_RESET ; 
 int CMD_FLUSHFIFO ; 
 int CMD_NOP ; 
 int CMD_SELECTATNSTOP ; 
 int CMD_WITHDMA ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  PHASE_SELECTION ; 
 int /*<<< orphan*/  REG_FF ; 
 int /*<<< orphan*/  REG_SDID ; 
 int /*<<< orphan*/  REG_STIM ; 
 int /*<<< orphan*/  fas216_cmd (TYPE_5__*,int) ; 
 int /*<<< orphan*/  fas216_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fas216_set_stc (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fas216_set_sync (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fas216_writeb (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fasdma_none ; 
 int /*<<< orphan*/  msgqueue_addmsg (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msgqueue_flush (int /*<<< orphan*/ *) ; 
 struct message* msgqueue_getmsg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fas216_do_bus_device_reset(FAS216_Info *info,
				       struct scsi_cmnd *SCpnt)
{
	struct message *msg;

	/*
	 * claim host busy
	 */
	info->scsi.phase = PHASE_SELECTION;
	info->scsi.SCp = SCpnt->SCp;
	info->SCpnt = SCpnt;
	info->dma.transfer_type = fasdma_none;

	fas216_log(info, LOG_ERROR, "sending bus device reset");

	msgqueue_flush(&info->scsi.msgs);
	msgqueue_addmsg(&info->scsi.msgs, 1, BUS_DEVICE_RESET);

	/* following what the ESP driver says */
	fas216_set_stc(info, 0);
	fas216_cmd(info, CMD_NOP | CMD_WITHDMA);

	/* flush FIFO */
	fas216_cmd(info, CMD_FLUSHFIFO);

	/* load bus-id and timeout */
	fas216_writeb(info, REG_SDID, BUSID(SCpnt->device->id));
	fas216_writeb(info, REG_STIM, info->ifcfg.select_timeout);

	/* synchronous transfers */
	fas216_set_sync(info, SCpnt->device->id);

	msg = msgqueue_getmsg(&info->scsi.msgs, 0);

	fas216_writeb(info, REG_FF, BUS_DEVICE_RESET);
	msg->fifo = 1;

	fas216_cmd(info, CMD_SELECTATNSTOP);
}