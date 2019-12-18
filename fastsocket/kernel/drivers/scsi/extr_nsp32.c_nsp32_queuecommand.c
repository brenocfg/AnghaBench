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
struct TYPE_12__ {char* ptr; scalar_t__ buffers_residual; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  this_residual; scalar_t__ Message; int /*<<< orphan*/  Status; } ;
struct scsi_cmnd {int result; void (* scsi_done ) (struct scsi_cmnd*) ;TYPE_3__* device; TYPE_2__ SCp; int /*<<< orphan*/  cmd_len; int /*<<< orphan*/ * cmnd; } ;
struct TYPE_14__ {int sync_flag; int /*<<< orphan*/  ackwidth; int /*<<< orphan*/  syncreg; int /*<<< orphan*/  limit_entry; } ;
typedef  TYPE_4__ nsp32_target ;
struct TYPE_15__ {int msgin03; scalar_t__ save_datp; struct scsi_cmnd* SCpnt; } ;
typedef  TYPE_5__ nsp32_lunt ;
struct TYPE_16__ {size_t cur_id; size_t cur_lun; TYPE_4__* cur_target; TYPE_4__* target; TYPE_5__* cur_lunt; TYPE_5__** lunt; scalar_t__ msgin_len; scalar_t__ msgout_len; struct scsi_cmnd* CurrentSC; } ;
typedef  TYPE_6__ nsp32_hw_data ;
struct TYPE_13__ {size_t id; size_t lun; TYPE_1__* host; } ;
struct TYPE_11__ {size_t this_id; scalar_t__ hostdata; } ;

/* Variables and functions */
 scalar_t__ ASYNC_MODE ; 
 int /*<<< orphan*/  CHECK_CONDITION ; 
 int DID_BAD_TARGET ; 
 int DID_ERROR ; 
 int DID_NO_CONNECT ; 
 int FALSE ; 
 int /*<<< orphan*/  KERN_ERR ; 
 size_t MAX_LUN ; 
 int /*<<< orphan*/  NSP32_DEBUG_QUEUECOMMAND ; 
 int /*<<< orphan*/  NSP32_DEBUG_TARGETFLAG ; 
 int SDTR_DONE ; 
 int SDTR_INITIATOR ; 
 int SDTR_TARGET ; 
 int TRUE ; 
 scalar_t__ auto_param ; 
 int /*<<< orphan*/  nsp32_build_identify (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  nsp32_build_sdtr (struct scsi_cmnd*,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  nsp32_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  nsp32_msg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nsp32_scsi_done (struct scsi_cmnd*) ; 
 int nsp32_selection_autopara (struct scsi_cmnd*) ; 
 int nsp32_selection_autoscsi (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  nsp32_set_async (TYPE_6__*,TYPE_4__*) ; 
 int /*<<< orphan*/  nsp32_set_max_sync (TYPE_6__*,TYPE_4__*,unsigned char*,unsigned char*) ; 
 int nsp32_setup_sg_table (struct scsi_cmnd*) ; 
 size_t scmd_id (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_sg_count (struct scsi_cmnd*) ; 
 scalar_t__ scsi_sglist (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  show_command (struct scsi_cmnd*) ; 
 scalar_t__ trans_mode ; 

__attribute__((used)) static int nsp32_queuecommand(struct scsi_cmnd *SCpnt, void (*done)(struct scsi_cmnd *))
{
	nsp32_hw_data *data = (nsp32_hw_data *)SCpnt->device->host->hostdata;
	nsp32_target *target;
	nsp32_lunt   *cur_lunt;
	int ret;

	nsp32_dbg(NSP32_DEBUG_QUEUECOMMAND,
		  "enter. target: 0x%x LUN: 0x%x cmnd: 0x%x cmndlen: 0x%x "
		  "use_sg: 0x%x reqbuf: 0x%lx reqlen: 0x%x",
		  SCpnt->device->id, SCpnt->device->lun, SCpnt->cmnd[0], SCpnt->cmd_len,
		  scsi_sg_count(SCpnt), scsi_sglist(SCpnt), scsi_bufflen(SCpnt));

	if (data->CurrentSC != NULL) {
		nsp32_msg(KERN_ERR, "Currentsc != NULL. Cancel this command request");
		data->CurrentSC = NULL;
		SCpnt->result   = DID_NO_CONNECT << 16;
		done(SCpnt);
		return 0;
	}

	/* check target ID is not same as this initiator ID */
	if (scmd_id(SCpnt) == SCpnt->device->host->this_id) {
		nsp32_dbg(NSP32_DEBUG_QUEUECOMMAND, "terget==host???");
		SCpnt->result = DID_BAD_TARGET << 16;
		done(SCpnt);
		return 0;
	}

	/* check target LUN is allowable value */
	if (SCpnt->device->lun >= MAX_LUN) {
		nsp32_dbg(NSP32_DEBUG_QUEUECOMMAND, "no more lun");
		SCpnt->result = DID_BAD_TARGET << 16;
		done(SCpnt);
		return 0;
	}

	show_command(SCpnt);

	SCpnt->scsi_done     = done;
	data->CurrentSC      = SCpnt;
	SCpnt->SCp.Status    = CHECK_CONDITION;
	SCpnt->SCp.Message   = 0;
	scsi_set_resid(SCpnt, scsi_bufflen(SCpnt));

	SCpnt->SCp.ptr		    = (char *)scsi_sglist(SCpnt);
	SCpnt->SCp.this_residual    = scsi_bufflen(SCpnt);
	SCpnt->SCp.buffer	    = NULL;
	SCpnt->SCp.buffers_residual = 0;

	/* initialize data */
	data->msgout_len	= 0;
	data->msgin_len		= 0;
	cur_lunt		= &(data->lunt[SCpnt->device->id][SCpnt->device->lun]);
	cur_lunt->SCpnt		= SCpnt;
	cur_lunt->save_datp	= 0;
	cur_lunt->msgin03	= FALSE;
	data->cur_lunt		= cur_lunt;
	data->cur_id		= SCpnt->device->id;
	data->cur_lun		= SCpnt->device->lun;

	ret = nsp32_setup_sg_table(SCpnt);
	if (ret == FALSE) {
		nsp32_msg(KERN_ERR, "SGT fail");
		SCpnt->result = DID_ERROR << 16;
		nsp32_scsi_done(SCpnt);
		return 0;
	}

	/* Build IDENTIFY */
	nsp32_build_identify(SCpnt);

	/* 
	 * If target is the first time to transfer after the reset
	 * (target don't have SDTR_DONE and SDTR_INITIATOR), sync
	 * message SDTR is needed to do synchronous transfer.
	 */
	target = &data->target[scmd_id(SCpnt)];
	data->cur_target = target;

	if (!(target->sync_flag & (SDTR_DONE | SDTR_INITIATOR | SDTR_TARGET))) {
		unsigned char period, offset;

		if (trans_mode != ASYNC_MODE) {
			nsp32_set_max_sync(data, target, &period, &offset);
			nsp32_build_sdtr(SCpnt, period, offset);
			target->sync_flag |= SDTR_INITIATOR;
		} else {
			nsp32_set_async(data, target);
			target->sync_flag |= SDTR_DONE;
		}

		nsp32_dbg(NSP32_DEBUG_QUEUECOMMAND,
			  "SDTR: entry: %d start_period: 0x%x offset: 0x%x\n",
			  target->limit_entry, period, offset);
	} else if (target->sync_flag & SDTR_INITIATOR) {
		/*
		 * It was negotiating SDTR with target, sending from the
		 * initiator, but there are no chance to remove this flag.
		 * Set async because we don't get proper negotiation.
		 */
		nsp32_set_async(data, target);
		target->sync_flag &= ~SDTR_INITIATOR;
		target->sync_flag |= SDTR_DONE;

		nsp32_dbg(NSP32_DEBUG_QUEUECOMMAND,
			  "SDTR_INITIATOR: fall back to async");
	} else if (target->sync_flag & SDTR_TARGET) {
		/*
		 * It was negotiating SDTR with target, sending from target,
		 * but there are no chance to remove this flag.  Set async
		 * because we don't get proper negotiation.
		 */
		nsp32_set_async(data, target);
		target->sync_flag &= ~SDTR_TARGET;
		target->sync_flag |= SDTR_DONE;

		nsp32_dbg(NSP32_DEBUG_QUEUECOMMAND,
			  "Unknown SDTR from target is reached, fall back to async.");
	}

	nsp32_dbg(NSP32_DEBUG_TARGETFLAG,
		  "target: %d sync_flag: 0x%x syncreg: 0x%x ackwidth: 0x%x",
		  SCpnt->device->id, target->sync_flag, target->syncreg,
		  target->ackwidth);

	/* Selection */
	if (auto_param == 0) {
		ret = nsp32_selection_autopara(SCpnt);
	} else {
		ret = nsp32_selection_autoscsi(SCpnt);
	}

	if (ret != TRUE) {
		nsp32_dbg(NSP32_DEBUG_QUEUECOMMAND, "selection fail");
		nsp32_scsi_done(SCpnt);
	}

	return 0;
}