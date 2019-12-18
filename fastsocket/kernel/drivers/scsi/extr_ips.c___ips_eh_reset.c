#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_9__ ;
typedef  struct TYPE_37__   TYPE_8__ ;
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;
typedef  struct TYPE_29__   TYPE_17__ ;
typedef  struct TYPE_28__   TYPE_10__ ;

/* Type definitions */
struct timeval {int /*<<< orphan*/  tv_sec; } ;
struct scsi_cmnd {int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;TYPE_2__* device; } ;
struct TYPE_32__ {scalar_t__ reserved4; scalar_t__ reserved3; scalar_t__ reserved2; scalar_t__ reserved; int /*<<< orphan*/  state; int /*<<< orphan*/  command_id; void* op_code; } ;
struct TYPE_33__ {TYPE_3__ flush_cache; } ;
struct TYPE_36__ {TYPE_10__* scsi_cmd; TYPE_4__ cmd; void** cdb; int /*<<< orphan*/  timeout; } ;
typedef  TYPE_7__ ips_scb_t ;
struct TYPE_34__ {int (* reset ) (TYPE_8__*) ;} ;
struct TYPE_29__ {TYPE_9__* head; } ;
struct TYPE_37__ {scalar_t__ ioctl_reset; int max_cmds; int nbus; scalar_t__ num_ioctl; scalar_t__* dcdb_active; int /*<<< orphan*/  scb_activelist; int /*<<< orphan*/  host_num; int /*<<< orphan*/  reset_count; int /*<<< orphan*/  last_ffdc; TYPE_6__* subsys; void* active; int /*<<< orphan*/  scb_waitlist; int /*<<< orphan*/  pcidev; TYPE_5__ func; TYPE_7__* scbs; TYPE_17__ copp_waitlist; } ;
typedef  TYPE_8__ ips_ha_t ;
struct TYPE_38__ {struct TYPE_38__* next; struct scsi_cmnd* scsi_cmd; } ;
typedef  TYPE_9__ ips_copp_wait_item_t ;
struct TYPE_35__ {int /*<<< orphan*/ * param; } ;
struct TYPE_31__ {TYPE_1__* host; } ;
struct TYPE_30__ {scalar_t__ hostdata; } ;
struct TYPE_28__ {int result; int /*<<< orphan*/  (* scsi_done ) (TYPE_10__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int,char*) ; 
 int /*<<< orphan*/  DEBUG_VAR (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DID_ERROR ; 
 int DID_RESET ; 
 int FAILED ; 
 void* FALSE ; 
 void* IPS_CMD_FLUSH ; 
 int /*<<< orphan*/  IPS_COMMAND_ID (TYPE_8__*,TYPE_7__*) ; 
 int /*<<< orphan*/  IPS_INTR_IORL ; 
 int /*<<< orphan*/  IPS_NORM_STATE ; 
 int /*<<< orphan*/  IPS_PRINTK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int IPS_SUCCESS ; 
 int /*<<< orphan*/  KERN_NOTICE ; 
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  do_gettimeofday (struct timeval*) ; 
 int /*<<< orphan*/  ips_clear_adapter (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ips_cmd_timeout ; 
 int /*<<< orphan*/  ips_ffdc_reset (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ips_freescb (TYPE_8__*,TYPE_7__*) ; 
 int /*<<< orphan*/  ips_init_scb (TYPE_8__*,TYPE_7__*) ; 
 int /*<<< orphan*/  ips_name ; 
 int /*<<< orphan*/  ips_next (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ips_removeq_copp (TYPE_17__*,TYPE_9__*) ; 
 TYPE_7__* ips_removeq_scb_head (int /*<<< orphan*/ *) ; 
 scalar_t__ ips_removeq_wait (int /*<<< orphan*/ *,struct scsi_cmnd*) ; 
 struct scsi_cmnd* ips_removeq_wait_head (int /*<<< orphan*/ *) ; 
 int ips_send_wait (TYPE_8__*,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_8__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_10__*) ; 
 int /*<<< orphan*/  stub3 (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  stub4 (TYPE_10__*) ; 
 int /*<<< orphan*/  stub5 (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  stub6 (TYPE_10__*) ; 

__attribute__((used)) static int __ips_eh_reset(struct scsi_cmnd *SC)
{
	int ret;
	int i;
	ips_ha_t *ha;
	ips_scb_t *scb;
	ips_copp_wait_item_t *item;

	METHOD_TRACE("ips_eh_reset", 1);

#ifdef NO_IPS_RESET
	return (FAILED);
#else

	if (!SC) {
		DEBUG(1, "Reset called with NULL scsi command");

		return (FAILED);
	}

	ha = (ips_ha_t *) SC->device->host->hostdata;

	if (!ha) {
		DEBUG(1, "Reset called with NULL ha struct");

		return (FAILED);
	}

	if (!ha->active)
		return (FAILED);

	/* See if the command is on the copp queue */
	item = ha->copp_waitlist.head;
	while ((item) && (item->scsi_cmd != SC))
		item = item->next;

	if (item) {
		/* Found it */
		ips_removeq_copp(&ha->copp_waitlist, item);
		return (SUCCESS);
	}

	/* See if the command is on the wait queue */
	if (ips_removeq_wait(&ha->scb_waitlist, SC)) {
		/* command not sent yet */
		return (SUCCESS);
	}

	/* An explanation for the casual observer:                              */
	/* Part of the function of a RAID controller is automatic error         */
	/* detection and recovery.  As such, the only problem that physically   */
	/* resetting an adapter will ever fix is when, for some reason,         */
	/* the driver is not successfully communicating with the adapter.       */
	/* Therefore, we will attempt to flush this adapter.  If that succeeds, */
	/* then there's no real purpose in a physical reset. This will complete */
	/* much faster and avoids any problems that might be caused by a        */
	/* physical reset ( such as having to fail all the outstanding I/O's ). */

	if (ha->ioctl_reset == 0) {	/* IF Not an IOCTL Requested Reset */
		scb = &ha->scbs[ha->max_cmds - 1];

		ips_init_scb(ha, scb);

		scb->timeout = ips_cmd_timeout;
		scb->cdb[0] = IPS_CMD_FLUSH;

		scb->cmd.flush_cache.op_code = IPS_CMD_FLUSH;
		scb->cmd.flush_cache.command_id = IPS_COMMAND_ID(ha, scb);
		scb->cmd.flush_cache.state = IPS_NORM_STATE;
		scb->cmd.flush_cache.reserved = 0;
		scb->cmd.flush_cache.reserved2 = 0;
		scb->cmd.flush_cache.reserved3 = 0;
		scb->cmd.flush_cache.reserved4 = 0;

		/* Attempt the flush command */
		ret = ips_send_wait(ha, scb, ips_cmd_timeout, IPS_INTR_IORL);
		if (ret == IPS_SUCCESS) {
			IPS_PRINTK(KERN_NOTICE, ha->pcidev,
				   "Reset Request - Flushed Cache\n");
			return (SUCCESS);
		}
	}

	/* Either we can't communicate with the adapter or it's an IOCTL request */
	/* from a utility.  A physical reset is needed at this point.            */

	ha->ioctl_reset = 0;	/* Reset the IOCTL Requested Reset Flag */

	/*
	 * command must have already been sent
	 * reset the controller
	 */
	IPS_PRINTK(KERN_NOTICE, ha->pcidev, "Resetting controller.\n");
	ret = (*ha->func.reset) (ha);

	if (!ret) {
		struct scsi_cmnd *scsi_cmd;

		IPS_PRINTK(KERN_NOTICE, ha->pcidev,
			   "Controller reset failed - controller now offline.\n");

		/* Now fail all of the active commands */
		DEBUG_VAR(1, "(%s%d) Failing active commands",
			  ips_name, ha->host_num);

		while ((scb = ips_removeq_scb_head(&ha->scb_activelist))) {
			scb->scsi_cmd->result = DID_ERROR << 16;
			scb->scsi_cmd->scsi_done(scb->scsi_cmd);
			ips_freescb(ha, scb);
		}

		/* Now fail all of the pending commands */
		DEBUG_VAR(1, "(%s%d) Failing pending commands",
			  ips_name, ha->host_num);

		while ((scsi_cmd = ips_removeq_wait_head(&ha->scb_waitlist))) {
			scsi_cmd->result = DID_ERROR;
			scsi_cmd->scsi_done(scsi_cmd);
		}

		ha->active = FALSE;
		return (FAILED);
	}

	if (!ips_clear_adapter(ha, IPS_INTR_IORL)) {
		struct scsi_cmnd *scsi_cmd;

		IPS_PRINTK(KERN_NOTICE, ha->pcidev,
			   "Controller reset failed - controller now offline.\n");

		/* Now fail all of the active commands */
		DEBUG_VAR(1, "(%s%d) Failing active commands",
			  ips_name, ha->host_num);

		while ((scb = ips_removeq_scb_head(&ha->scb_activelist))) {
			scb->scsi_cmd->result = DID_ERROR << 16;
			scb->scsi_cmd->scsi_done(scb->scsi_cmd);
			ips_freescb(ha, scb);
		}

		/* Now fail all of the pending commands */
		DEBUG_VAR(1, "(%s%d) Failing pending commands",
			  ips_name, ha->host_num);

		while ((scsi_cmd = ips_removeq_wait_head(&ha->scb_waitlist))) {
			scsi_cmd->result = DID_ERROR << 16;
			scsi_cmd->scsi_done(scsi_cmd);
		}

		ha->active = FALSE;
		return (FAILED);
	}

	/* FFDC */
	if (le32_to_cpu(ha->subsys->param[3]) & 0x300000) {
		struct timeval tv;

		do_gettimeofday(&tv);
		ha->last_ffdc = tv.tv_sec;
		ha->reset_count++;
		ips_ffdc_reset(ha, IPS_INTR_IORL);
	}

	/* Now fail all of the active commands */
	DEBUG_VAR(1, "(%s%d) Failing active commands", ips_name, ha->host_num);

	while ((scb = ips_removeq_scb_head(&ha->scb_activelist))) {
		scb->scsi_cmd->result = DID_RESET << 16;
		scb->scsi_cmd->scsi_done(scb->scsi_cmd);
		ips_freescb(ha, scb);
	}

	/* Reset DCDB active command bits */
	for (i = 1; i < ha->nbus; i++)
		ha->dcdb_active[i - 1] = 0;

	/* Reset the number of active IOCTLs */
	ha->num_ioctl = 0;

	ips_next(ha, IPS_INTR_IORL);

	return (SUCCESS);
#endif				/* NO_IPS_RESET */

}