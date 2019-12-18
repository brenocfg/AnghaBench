#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {int result; int* cmnd; unsigned char* host_scribble; void (* scsi_done ) (struct scsi_cmnd*) ;int /*<<< orphan*/  request; TYPE_2__* device; } ;
struct lpfc_vport {struct lpfc_hba* phba; scalar_t__ cfg_max_scsicmpl_time; } ;
struct lpfc_scsi_buf {int /*<<< orphan*/  cur_iocbq; int /*<<< orphan*/  start_time; scalar_t__ timeout; struct lpfc_rport_data* rdata; struct scsi_cmnd* pCmd; } ;
struct lpfc_rport_data {struct lpfc_nodelist* pnode; } ;
struct lpfc_nodelist {scalar_t__ cmd_qdepth; int /*<<< orphan*/  cmd_pending; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ring; } ;
struct lpfc_hba {int sli3_options; int cfg_poll; TYPE_1__ sli; scalar_t__ cfg_enable_bg; } ;
struct fc_rport {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; scalar_t__ hostdata; } ;
struct TYPE_4__ {struct lpfc_rport_data* hostdata; struct Scsi_Host* host; } ;

/* Variables and functions */
 int DISABLE_FCP_RING_INT ; 
 int ENABLE_FCP_RING_POLLING ; 
 int /*<<< orphan*/  HA_R0RE_REQ ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_BG ; 
 int /*<<< orphan*/  LOG_FCP ; 
 int /*<<< orphan*/  LOG_SCSI_CMD ; 
 size_t LPFC_FCP_RING ; 
 int LPFC_SLI3_BG_ENABLED ; 
 int /*<<< orphan*/  NLP_CHK_NODE_ACT (struct lpfc_nodelist*) ; 
 int SCSI_MLQUEUE_HOST_BUSY ; 
 int SCSI_MLQUEUE_TARGET_BUSY ; 
 size_t SCSI_PROT_NORMAL ; 
 int /*<<< orphan*/  SLI_IOCB_RET_IOCB ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_rq_sectors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dif_op_str ; 
 int fc_remote_port_chkready (struct fc_rport*) ; 
 int /*<<< orphan*/  jiffies ; 
 int lpfc_bg_scsi_prep_dma_buf (struct lpfc_hba*,struct lpfc_scsi_buf*) ; 
 struct lpfc_scsi_buf* lpfc_get_scsi_buf (struct lpfc_hba*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_poll_rearm_timer (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  lpfc_rampdown_queue_depth (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_release_scsi_buf (struct lpfc_hba*,struct lpfc_scsi_buf*) ; 
 int /*<<< orphan*/  lpfc_scsi_prep_cmnd (struct lpfc_vport*,struct lpfc_scsi_buf*,struct lpfc_nodelist*) ; 
 int lpfc_scsi_prep_dma_buf (struct lpfc_hba*,struct lpfc_scsi_buf*) ; 
 int /*<<< orphan*/  lpfc_scsi_unprep_dma_buf (struct lpfc_hba*,struct lpfc_scsi_buf*) ; 
 int /*<<< orphan*/  lpfc_sli_handle_fast_ring_event (struct lpfc_hba*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int lpfc_sli_issue_iocb (struct lpfc_hba*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_get_lba (struct scsi_cmnd*) ; 
 size_t scsi_get_prot_op (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_target (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ ) ; 
 struct fc_rport* starget_to_rport (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpfc_queuecommand(struct scsi_cmnd *cmnd, void (*done) (struct scsi_cmnd *))
{
	struct Scsi_Host  *shost = cmnd->device->host;
	struct lpfc_vport *vport = (struct lpfc_vport *) shost->hostdata;
	struct lpfc_hba   *phba = vport->phba;
	struct lpfc_rport_data *rdata = cmnd->device->hostdata;
	struct lpfc_nodelist *ndlp;
	struct lpfc_scsi_buf *lpfc_cmd;
	struct fc_rport *rport = starget_to_rport(scsi_target(cmnd->device));
	int err;

	err = fc_remote_port_chkready(rport);
	if (err) {
		cmnd->result = err;
		goto out_fail_command;
	}
	ndlp = rdata->pnode;

	if ((scsi_get_prot_op(cmnd) != SCSI_PROT_NORMAL) &&
		(!(phba->sli3_options & LPFC_SLI3_BG_ENABLED))) {

		lpfc_printf_log(phba, KERN_ERR, LOG_BG,
				"9058 BLKGRD: ERROR: rcvd protected cmd:%02x"
				" op:%02x str=%s without registering for"
				" BlockGuard - Rejecting command\n",
				cmnd->cmnd[0], scsi_get_prot_op(cmnd),
				dif_op_str[scsi_get_prot_op(cmnd)]);
		goto out_fail_command;
	}

	/*
	 * Catch race where our node has transitioned, but the
	 * transport is still transitioning.
	 */
	if (!ndlp || !NLP_CHK_NODE_ACT(ndlp))
		goto out_tgt_busy;
	if (vport->cfg_max_scsicmpl_time &&
		(atomic_read(&ndlp->cmd_pending) >= ndlp->cmd_qdepth))
		goto out_tgt_busy;

	lpfc_cmd = lpfc_get_scsi_buf(phba, ndlp);
	if (lpfc_cmd == NULL) {
		lpfc_rampdown_queue_depth(phba);

		lpfc_printf_vlog(vport, KERN_INFO, LOG_FCP,
				 "0707 driver's buffer pool is empty, "
				 "IO busied\n");
		goto out_host_busy;
	}

	/*
	 * Store the midlayer's command structure for the completion phase
	 * and complete the command initialization.
	 */
	lpfc_cmd->pCmd  = cmnd;
	lpfc_cmd->rdata = rdata;
	lpfc_cmd->timeout = 0;
	lpfc_cmd->start_time = jiffies;
	cmnd->host_scribble = (unsigned char *)lpfc_cmd;
	cmnd->scsi_done = done;

	if (scsi_get_prot_op(cmnd) != SCSI_PROT_NORMAL) {
		if (vport->phba->cfg_enable_bg) {
			lpfc_printf_vlog(vport,
					 KERN_INFO, LOG_SCSI_CMD,
					 "9033 BLKGRD: rcvd %s cmd:x%x "
					 "sector x%llx cnt %u pt %x\n",
					 dif_op_str[scsi_get_prot_op(cmnd)],
					 cmnd->cmnd[0],
					 (unsigned long long)scsi_get_lba(cmnd),
					 blk_rq_sectors(cmnd->request),
					 (cmnd->cmnd[1]>>5));
		}
		err = lpfc_bg_scsi_prep_dma_buf(phba, lpfc_cmd);
	} else {
		if (vport->phba->cfg_enable_bg) {
			lpfc_printf_vlog(vport,
					 KERN_INFO, LOG_SCSI_CMD,
					 "9038 BLKGRD: rcvd PROT_NORMAL cmd: "
					 "x%x sector x%llx cnt %u pt %x\n",
					 cmnd->cmnd[0],
					 (unsigned long long)scsi_get_lba(cmnd),
					 blk_rq_sectors(cmnd->request),
					 (cmnd->cmnd[1]>>5));
		}
		err = lpfc_scsi_prep_dma_buf(phba, lpfc_cmd);
	}

	if (err)
		goto out_host_busy_free_buf;

	lpfc_scsi_prep_cmnd(vport, lpfc_cmd, ndlp);

	atomic_inc(&ndlp->cmd_pending);
	err = lpfc_sli_issue_iocb(phba, LPFC_FCP_RING,
				  &lpfc_cmd->cur_iocbq, SLI_IOCB_RET_IOCB);
	if (err) {
		atomic_dec(&ndlp->cmd_pending);
		goto out_host_busy_free_buf;
	}
	if (phba->cfg_poll & ENABLE_FCP_RING_POLLING) {
		spin_unlock(shost->host_lock);
		lpfc_sli_handle_fast_ring_event(phba,
			&phba->sli.ring[LPFC_FCP_RING], HA_R0RE_REQ);

		spin_lock(shost->host_lock);
		if (phba->cfg_poll & DISABLE_FCP_RING_INT)
			lpfc_poll_rearm_timer(phba);
	}

	return 0;

 out_host_busy_free_buf:
	lpfc_scsi_unprep_dma_buf(phba, lpfc_cmd);
	lpfc_release_scsi_buf(phba, lpfc_cmd);
 out_host_busy:
	return SCSI_MLQUEUE_HOST_BUSY;

 out_tgt_busy:
	return SCSI_MLQUEUE_TARGET_BUSY;

 out_fail_command:
	done(cmnd);
	return 0;
}