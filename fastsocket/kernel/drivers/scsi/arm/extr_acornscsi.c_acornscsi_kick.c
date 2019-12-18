#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {int tag; int /*<<< orphan*/ * cmnd; TYPE_5__* device; int /*<<< orphan*/  SCp; } ;
typedef  int /*<<< orphan*/  intr_ret_t ;
struct TYPE_17__ {int removes; int writes; int reads; int miscs; } ;
struct TYPE_14__ {scalar_t__ xfer_done; scalar_t__ xfer_required; scalar_t__ xfer_setup; } ;
struct TYPE_13__ {int /*<<< orphan*/  SCp; int /*<<< orphan*/  phase; scalar_t__ disconnectable; } ;
struct TYPE_12__ {int /*<<< orphan*/  disconnected; int /*<<< orphan*/  issue; } ;
struct TYPE_18__ {TYPE_6__ stats; int /*<<< orphan*/  busyluns; TYPE_4__* host; TYPE_3__ dma; TYPE_2__ scsi; struct scsi_cmnd* SCpnt; TYPE_1__ queues; struct scsi_cmnd* origSCpnt; } ;
struct TYPE_16__ {int id; int current_tag; scalar_t__ lun; scalar_t__ simple_tags; } ;
struct TYPE_15__ {int /*<<< orphan*/  host_no; } ;
typedef  TYPE_7__ AS_Host ;

/* Variables and functions */
 int ASR_BSY ; 
 int ASR_CIP ; 
 int ASR_INT ; 
#define  CMD_MISC 130 
#define  CMD_READ 129 
#define  CMD_WRITE 128 
 int CMND_SELWITHATN ; 
 int /*<<< orphan*/  DBG (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTR_IDLE ; 
 int /*<<< orphan*/  INTR_PROCESSING ; 
 int /*<<< orphan*/  PHASE_CONNECTING ; 
 int /*<<< orphan*/  SBIC_ASR ; 
 int /*<<< orphan*/  SBIC_CMND ; 
 int /*<<< orphan*/  SBIC_DESTID ; 
 int acornscsi_cmdtype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acornscsi_target (TYPE_7__*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  queue_add_cmd_tail (int /*<<< orphan*/ *,struct scsi_cmnd*) ; 
 struct scsi_cmnd* queue_remove_exclude (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sbic_arm_read (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbic_arm_write (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
intr_ret_t acornscsi_kick(AS_Host *host)
{
    int from_queue = 0;
    struct scsi_cmnd *SCpnt;

    /* first check to see if a command is waiting to be executed */
    SCpnt = host->origSCpnt;
    host->origSCpnt = NULL;

    /* retrieve next command */
    if (!SCpnt) {
	SCpnt = queue_remove_exclude(&host->queues.issue, host->busyluns);
	if (!SCpnt)
	    return INTR_IDLE;

	from_queue = 1;
    }

    if (host->scsi.disconnectable && host->SCpnt) {
	queue_add_cmd_tail(&host->queues.disconnected, host->SCpnt);
	host->scsi.disconnectable = 0;
#if (DEBUG & (DEBUG_QUEUES|DEBUG_DISCON))
	DBG(host->SCpnt, printk("scsi%d.%c: moved command to disconnected queue\n",
		host->host->host_no, acornscsi_target(host)));
#endif
	host->SCpnt = NULL;
    }

    /*
     * If we have an interrupt pending, then we may have been reselected.
     * In this case, we don't want to write to the registers
     */
    if (!(sbic_arm_read(host, SBIC_ASR) & (ASR_INT|ASR_BSY|ASR_CIP))) {
	sbic_arm_write(host, SBIC_DESTID, SCpnt->device->id);
	sbic_arm_write(host, SBIC_CMND, CMND_SELWITHATN);
    }

    /*
     * claim host busy - all of these must happen atomically wrt
     * our interrupt routine.  Failure means command loss.
     */
    host->scsi.phase = PHASE_CONNECTING;
    host->SCpnt = SCpnt;
    host->scsi.SCp = SCpnt->SCp;
    host->dma.xfer_setup = 0;
    host->dma.xfer_required = 0;
    host->dma.xfer_done = 0;

#if (DEBUG & (DEBUG_ABORT|DEBUG_CONNECT))
    DBG(SCpnt,printk("scsi%d.%c: starting cmd %02X\n",
	    host->host->host_no, '0' + SCpnt->device->id,
	    SCpnt->cmnd[0]));
#endif

    if (from_queue) {
#ifdef CONFIG_SCSI_ACORNSCSI_TAGGED_QUEUE
	/*
	 * tagged queueing - allocate a new tag to this command
	 */
	if (SCpnt->device->simple_tags) {
	    SCpnt->device->current_tag += 1;
	    if (SCpnt->device->current_tag == 0)
		SCpnt->device->current_tag = 1;
	    SCpnt->tag = SCpnt->device->current_tag;
	} else
#endif
	    set_bit(SCpnt->device->id * 8 + SCpnt->device->lun, host->busyluns);

	host->stats.removes += 1;

	switch (acornscsi_cmdtype(SCpnt->cmnd[0])) {
	case CMD_WRITE:
	    host->stats.writes += 1;
	    break;
	case CMD_READ:
	    host->stats.reads += 1;
	    break;
	case CMD_MISC:
	    host->stats.miscs += 1;
	    break;
	}
    }

    return INTR_PROCESSING;
}