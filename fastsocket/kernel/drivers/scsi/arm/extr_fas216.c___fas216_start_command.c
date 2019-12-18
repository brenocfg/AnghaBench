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
struct scsi_cmnd {int cmd_len; int /*<<< orphan*/ * cmnd; TYPE_3__* device; } ;
struct message {int length; int fifo; int /*<<< orphan*/ * msg; } ;
struct TYPE_15__ {int /*<<< orphan*/  msgs; int /*<<< orphan*/  phase; } ;
struct TYPE_12__ {int /*<<< orphan*/  select_timeout; } ;
struct TYPE_16__ {TYPE_4__ scsi; TYPE_2__* host; TYPE_1__ ifcfg; } ;
struct TYPE_14__ {scalar_t__ id; } ;
struct TYPE_13__ {int /*<<< orphan*/  host_no; } ;
typedef  TYPE_5__ FAS216_Info ;

/* Variables and functions */
 int /*<<< orphan*/  BUSID (scalar_t__) ; 
 int CFIS_CF ; 
 int CMD_FLUSHFIFO ; 
 int CMD_NOP ; 
 int CMD_SELECTATN ; 
 int CMD_SELECTATN3 ; 
 int CMD_SELECTATNSTOP ; 
 int CMD_WITHDMA ; 
 int /*<<< orphan*/  PHASE_SELSTEPS ; 
 int /*<<< orphan*/  REG_CFIS ; 
 int /*<<< orphan*/  REG_FF ; 
 int /*<<< orphan*/  REG_SDID ; 
 int /*<<< orphan*/  REG_STIM ; 
 int /*<<< orphan*/  fas216_cmd (TYPE_5__*,int) ; 
 int fas216_readb (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fas216_set_stc (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fas216_set_sync (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  fas216_writeb (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct message* msgqueue_getmsg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int msgqueue_msglength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void __fas216_start_command(FAS216_Info *info, struct scsi_cmnd *SCpnt)
{
	int tot_msglen;

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

	tot_msglen = msgqueue_msglength(&info->scsi.msgs);

#ifdef DEBUG_MESSAGES
	{
		struct message *msg;
		int msgnr = 0, i;

		printk("scsi%d.%c: message out: ",
			info->host->host_no, '0' + SCpnt->device->id);
		while ((msg = msgqueue_getmsg(&info->scsi.msgs, msgnr++)) != NULL) {
			printk("{ ");
			for (i = 0; i < msg->length; i++)
				printk("%02x ", msg->msg[i]);
			printk("} ");
		}
		printk("\n");
	}
#endif

	if (tot_msglen == 1 || tot_msglen == 3) {
		/*
		 * We have an easy message length to send...
		 */
		struct message *msg;
		int msgnr = 0, i;

		info->scsi.phase = PHASE_SELSTEPS;

		/* load message bytes */
		while ((msg = msgqueue_getmsg(&info->scsi.msgs, msgnr++)) != NULL) {
			for (i = 0; i < msg->length; i++)
				fas216_writeb(info, REG_FF, msg->msg[i]);
			msg->fifo = tot_msglen - (fas216_readb(info, REG_CFIS) & CFIS_CF);
		}

		/* load command */
		for (i = 0; i < SCpnt->cmd_len; i++)
			fas216_writeb(info, REG_FF, SCpnt->cmnd[i]);

		if (tot_msglen == 1)
			fas216_cmd(info, CMD_SELECTATN);
		else
			fas216_cmd(info, CMD_SELECTATN3);
	} else {
		/*
		 * We have an unusual number of message bytes to send.
		 *  Load first byte into fifo, and issue SELECT with ATN and
		 *  stop steps.
		 */
		struct message *msg = msgqueue_getmsg(&info->scsi.msgs, 0);

		fas216_writeb(info, REG_FF, msg->msg[0]);
		msg->fifo = 1;

		fas216_cmd(info, CMD_SELECTATNSTOP);
	}
}