#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_14__ {int /*<<< orphan*/  lsRjtRsnCodeExp; int /*<<< orphan*/  lsRjtRsnCode; } ;
struct TYPE_15__ {int /*<<< orphan*/  lsRjtError; TYPE_4__ b; } ;
struct ls_rjt {TYPE_5__ un; } ;
struct lpfc_vport {int cfg_devloss_tmo; int load_flag; int fc_flag; int /*<<< orphan*/  fc_disctmo; } ;
struct lpfc_nodelist {scalar_t__ nlp_DID; int nlp_retry; int /*<<< orphan*/  nlp_state; int /*<<< orphan*/  nlp_prev_state; scalar_t__ nlp_last_elscmd; int /*<<< orphan*/  nlp_flag; int /*<<< orphan*/  nlp_delayfunc; } ;
struct TYPE_11__ {scalar_t__ remoteID; } ;
struct TYPE_18__ {int* ulpWord; TYPE_1__ elsreq64; } ;
struct TYPE_19__ {int ulpStatus; TYPE_8__ un; } ;
struct lpfc_iocbq {int retry; int /*<<< orphan*/  sli4_lxritag; scalar_t__ context2; scalar_t__ context1; TYPE_9__ iocb; struct lpfc_vport* vport; } ;
struct TYPE_17__ {int /*<<< orphan*/  elsDelayRetry; int /*<<< orphan*/  elsXmitRetry; int /*<<< orphan*/  elsRetryExceeded; } ;
struct TYPE_16__ {int fcf_flag; } ;
struct lpfc_hba {scalar_t__ fc_topology; int sli3_options; TYPE_7__ fc_stat; TYPE_6__ fcf; int /*<<< orphan*/ * alpa_map; TYPE_3__* pport; TYPE_2__* pcidev; int /*<<< orphan*/  sli_rev; } ;
struct lpfc_dmabuf {scalar_t__ virt; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
struct TYPE_13__ {int /*<<< orphan*/  fc_myDID; } ;
struct TYPE_12__ {int /*<<< orphan*/  device; } ;
typedef  TYPE_9__ IOCB_t ;

/* Variables and functions */
#define  ELS_CMD_ADISC 153 
#define  ELS_CMD_FDISC 152 
#define  ELS_CMD_FLOGI 151 
#define  ELS_CMD_LOGO 150 
#define  ELS_CMD_PLOGI 149 
#define  ELS_CMD_PRLI 148 
 int FCF_DISCOVERY ; 
 int FC_RSCN_MODE ; 
 int FC_UNLOADING ; 
 int /*<<< orphan*/  FC_VPORT_FABRIC_REJ_WWN ; 
 int /*<<< orphan*/  FC_VPORT_NO_FABRIC_RSCS ; 
 scalar_t__ FDMI_DID ; 
#define  IOERR_ILLEGAL_COMMAND 147 
#define  IOERR_ILLEGAL_FRAME 146 
#define  IOERR_INVALID_RPI 145 
#define  IOERR_LOOP_OPEN_FAILURE 144 
#define  IOERR_NO_RESOURCES 143 
 int IOERR_PARAM_MASK ; 
#define  IOERR_SEQUENCE_TIMEOUT 142 
#define  IOSTAT_BA_RJT 141 
#define  IOSTAT_FABRIC_BSY 140 
#define  IOSTAT_FABRIC_RJT 139 
#define  IOSTAT_FCP_RSP_ERROR 138 
#define  IOSTAT_INTERMED_RSP 137 
#define  IOSTAT_LOCAL_REJECT 136 
#define  IOSTAT_LS_RJT 135 
#define  IOSTAT_NPORT_BSY 134 
#define  IOSTAT_NPORT_RJT 133 
#define  IOSTAT_REMOTE_STOP 132 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_ELS ; 
 int /*<<< orphan*/  LPFC_DISC_TRC_ELS_CMD ; 
 int LPFC_SLI3_NPIV_ENABLED ; 
 int /*<<< orphan*/  LPFC_SLI_REV4 ; 
 scalar_t__ LPFC_TOPOLOGY_LOOP ; 
 int /*<<< orphan*/  LSEXP_CANT_GIVE_DATA ; 
 int /*<<< orphan*/  LSEXP_CMD_IN_PROGRESS ; 
 int /*<<< orphan*/  LSEXP_INVALID_NPORT_ID ; 
 int /*<<< orphan*/  LSEXP_INVALID_PNAME ; 
 int /*<<< orphan*/  LSEXP_OUT_OF_RESOURCE ; 
 int /*<<< orphan*/  LSEXP_PORT_LOGIN_REQ ; 
#define  LSRJT_LOGICAL_BSY 131 
#define  LSRJT_LOGICAL_ERR 130 
#define  LSRJT_PROTOCOL_ERR 129 
#define  LSRJT_UNABLE_TPC 128 
 scalar_t__ NLP_CHK_NODE_ACT (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  NLP_DELAY_TMO ; 
 int /*<<< orphan*/  NLP_STE_ADISC_ISSUE ; 
 int /*<<< orphan*/  NLP_STE_LOGO_ISSUE ; 
 int /*<<< orphan*/  NLP_STE_NPR_NODE ; 
 int /*<<< orphan*/  NLP_STE_PLOGI_ISSUE ; 
 int /*<<< orphan*/  NLP_STE_PRLI_ISSUE ; 
 scalar_t__ NameServer_DID ; 
 int /*<<< orphan*/  PCI_DEVICE_ID_HORNET ; 
 int RJT_UNAVAIL_TEMP ; 
 int /*<<< orphan*/  be32_to_cpu (int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  lpfc_debugfs_disc_trc (struct lpfc_vport*,int /*<<< orphan*/ ,char*,scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  lpfc_error_lost_link (TYPE_9__*) ; 
 struct lpfc_nodelist* lpfc_findnode_did (struct lpfc_vport*,scalar_t__) ; 
 int /*<<< orphan*/  lpfc_issue_els_adisc (struct lpfc_vport*,struct lpfc_nodelist*,int) ; 
 int /*<<< orphan*/  lpfc_issue_els_fdisc (struct lpfc_vport*,struct lpfc_nodelist*,int) ; 
 int /*<<< orphan*/  lpfc_issue_els_flogi (struct lpfc_vport*,struct lpfc_nodelist*,int) ; 
 int /*<<< orphan*/  lpfc_issue_els_logo (struct lpfc_vport*,struct lpfc_nodelist*,int) ; 
 int /*<<< orphan*/  lpfc_issue_els_plogi (struct lpfc_vport*,scalar_t__,int) ; 
 int /*<<< orphan*/  lpfc_issue_els_prli (struct lpfc_vport*,struct lpfc_nodelist*,int) ; 
 int lpfc_max_els_tries ; 
 int /*<<< orphan*/  lpfc_nlp_set_state (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  lpfc_set_disctmo (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_set_rrq_active (struct lpfc_hba*,struct lpfc_nodelist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_vport_set_state (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
lpfc_els_retry(struct lpfc_hba *phba, struct lpfc_iocbq *cmdiocb,
	       struct lpfc_iocbq *rspiocb)
{
	struct lpfc_vport *vport = cmdiocb->vport;
	struct Scsi_Host  *shost = lpfc_shost_from_vport(vport);
	IOCB_t *irsp = &rspiocb->iocb;
	struct lpfc_nodelist *ndlp = (struct lpfc_nodelist *) cmdiocb->context1;
	struct lpfc_dmabuf *pcmd = (struct lpfc_dmabuf *) cmdiocb->context2;
	uint32_t *elscmd;
	struct ls_rjt stat;
	int retry = 0, maxretry = lpfc_max_els_tries, delay = 0;
	int logerr = 0;
	uint32_t cmd = 0;
	uint32_t did;


	/* Note: context2 may be 0 for internal driver abort
	 * of delays ELS command.
	 */

	if (pcmd && pcmd->virt) {
		elscmd = (uint32_t *) (pcmd->virt);
		cmd = *elscmd++;
	}

	if (ndlp && NLP_CHK_NODE_ACT(ndlp))
		did = ndlp->nlp_DID;
	else {
		/* We should only hit this case for retrying PLOGI */
		did = irsp->un.elsreq64.remoteID;
		ndlp = lpfc_findnode_did(vport, did);
		if ((!ndlp || !NLP_CHK_NODE_ACT(ndlp))
		    && (cmd != ELS_CMD_PLOGI))
			return 1;
	}

	lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_CMD,
		"Retry ELS:       wd7:x%x wd4:x%x did:x%x",
		*(((uint32_t *) irsp) + 7), irsp->un.ulpWord[4], ndlp->nlp_DID);

	switch (irsp->ulpStatus) {
	case IOSTAT_FCP_RSP_ERROR:
		break;
	case IOSTAT_REMOTE_STOP:
		if (phba->sli_rev == LPFC_SLI_REV4) {
			/* This IO was aborted by the target, we don't
			 * know the rxid and because we did not send the
			 * ABTS we cannot generate and RRQ.
			 */
			lpfc_set_rrq_active(phba, ndlp,
					 cmdiocb->sli4_lxritag, 0, 0);
		}
		break;
	case IOSTAT_LOCAL_REJECT:
		switch ((irsp->un.ulpWord[4] & IOERR_PARAM_MASK)) {
		case IOERR_LOOP_OPEN_FAILURE:
			if (cmd == ELS_CMD_FLOGI) {
				if (PCI_DEVICE_ID_HORNET ==
					phba->pcidev->device) {
					phba->fc_topology = LPFC_TOPOLOGY_LOOP;
					phba->pport->fc_myDID = 0;
					phba->alpa_map[0] = 0;
					phba->alpa_map[1] = 0;
				}
			}
			if (cmd == ELS_CMD_PLOGI && cmdiocb->retry == 0)
				delay = 1000;
			retry = 1;
			break;

		case IOERR_ILLEGAL_COMMAND:
			lpfc_printf_vlog(vport, KERN_ERR, LOG_ELS,
					 "0124 Retry illegal cmd x%x "
					 "retry:x%x delay:x%x\n",
					 cmd, cmdiocb->retry, delay);
			retry = 1;
			/* All command's retry policy */
			maxretry = 8;
			if (cmdiocb->retry > 2)
				delay = 1000;
			break;

		case IOERR_NO_RESOURCES:
			logerr = 1; /* HBA out of resources */
			retry = 1;
			if (cmdiocb->retry > 100)
				delay = 100;
			maxretry = 250;
			break;

		case IOERR_ILLEGAL_FRAME:
			delay = 100;
			retry = 1;
			break;

		case IOERR_SEQUENCE_TIMEOUT:
		case IOERR_INVALID_RPI:
			if (cmd == ELS_CMD_PLOGI &&
			    did == NameServer_DID) {
				/* Continue forever if plogi to */
				/* the nameserver fails */
				maxretry = 0;
				delay = 100;
			}
			retry = 1;
			break;
		}
		break;

	case IOSTAT_NPORT_RJT:
	case IOSTAT_FABRIC_RJT:
		if (irsp->un.ulpWord[4] & RJT_UNAVAIL_TEMP) {
			retry = 1;
			break;
		}
		break;

	case IOSTAT_NPORT_BSY:
	case IOSTAT_FABRIC_BSY:
		logerr = 1; /* Fabric / Remote NPort out of resources */
		retry = 1;
		break;

	case IOSTAT_LS_RJT:
		stat.un.lsRjtError = be32_to_cpu(irsp->un.ulpWord[4]);
		/* Added for Vendor specifc support
		 * Just keep retrying for these Rsn / Exp codes
		 */
		switch (stat.un.b.lsRjtRsnCode) {
		case LSRJT_UNABLE_TPC:
			if (stat.un.b.lsRjtRsnCodeExp ==
			    LSEXP_CMD_IN_PROGRESS) {
				if (cmd == ELS_CMD_PLOGI) {
					delay = 1000;
					maxretry = 48;
				}
				retry = 1;
				break;
			}
			if (stat.un.b.lsRjtRsnCodeExp ==
			    LSEXP_CANT_GIVE_DATA) {
				if (cmd == ELS_CMD_PLOGI) {
					delay = 1000;
					maxretry = 48;
				}
				retry = 1;
				break;
			}
			if ((cmd == ELS_CMD_PLOGI) ||
			    (cmd == ELS_CMD_PRLI)) {
				delay = 1000;
				maxretry = lpfc_max_els_tries + 1;
				retry = 1;
				break;
			}
			if ((phba->sli3_options & LPFC_SLI3_NPIV_ENABLED) &&
			  (cmd == ELS_CMD_FDISC) &&
			  (stat.un.b.lsRjtRsnCodeExp == LSEXP_OUT_OF_RESOURCE)){
				lpfc_printf_vlog(vport, KERN_ERR, LOG_ELS,
						 "0125 FDISC Failed (x%x). "
						 "Fabric out of resources\n",
						 stat.un.lsRjtError);
				lpfc_vport_set_state(vport,
						     FC_VPORT_NO_FABRIC_RSCS);
			}
			break;

		case LSRJT_LOGICAL_BSY:
			if ((cmd == ELS_CMD_PLOGI) ||
			    (cmd == ELS_CMD_PRLI)) {
				delay = 1000;
				maxretry = 48;
			} else if (cmd == ELS_CMD_FDISC) {
				/* FDISC retry policy */
				maxretry = 48;
				if (cmdiocb->retry >= 32)
					delay = 1000;
			}
			retry = 1;
			break;

		case LSRJT_LOGICAL_ERR:
			/* There are some cases where switches return this
			 * error when they are not ready and should be returning
			 * Logical Busy. We should delay every time.
			 */
			if (cmd == ELS_CMD_FDISC &&
			    stat.un.b.lsRjtRsnCodeExp == LSEXP_PORT_LOGIN_REQ) {
				maxretry = 3;
				delay = 1000;
				retry = 1;
				break;
			}
		case LSRJT_PROTOCOL_ERR:
			if ((phba->sli3_options & LPFC_SLI3_NPIV_ENABLED) &&
			  (cmd == ELS_CMD_FDISC) &&
			  ((stat.un.b.lsRjtRsnCodeExp == LSEXP_INVALID_PNAME) ||
			  (stat.un.b.lsRjtRsnCodeExp == LSEXP_INVALID_NPORT_ID))
			  ) {
				lpfc_printf_vlog(vport, KERN_ERR, LOG_ELS,
						 "0122 FDISC Failed (x%x). "
						 "Fabric Detected Bad WWN\n",
						 stat.un.lsRjtError);
				lpfc_vport_set_state(vport,
						     FC_VPORT_FABRIC_REJ_WWN);
			}
			break;
		}
		break;

	case IOSTAT_INTERMED_RSP:
	case IOSTAT_BA_RJT:
		break;

	default:
		break;
	}

	if (did == FDMI_DID)
		retry = 1;

	if ((cmd == ELS_CMD_FLOGI) &&
	    (phba->fc_topology != LPFC_TOPOLOGY_LOOP) &&
	    !lpfc_error_lost_link(irsp)) {
		/* FLOGI retry policy */
		retry = 1;
		/* retry FLOGI forever */
		maxretry = 0;
		if (cmdiocb->retry >= 100)
			delay = 5000;
		else if (cmdiocb->retry >= 32)
			delay = 1000;
	} else if ((cmd == ELS_CMD_FDISC) && !lpfc_error_lost_link(irsp)) {
		/* retry FDISCs every second up to devloss */
		retry = 1;
		maxretry = vport->cfg_devloss_tmo;
		delay = 1000;
	}

	cmdiocb->retry++;
	if (maxretry && (cmdiocb->retry >= maxretry)) {
		phba->fc_stat.elsRetryExceeded++;
		retry = 0;
	}

	if ((vport->load_flag & FC_UNLOADING) != 0)
		retry = 0;

	if (retry) {
		if ((cmd == ELS_CMD_PLOGI) || (cmd == ELS_CMD_FDISC)) {
			/* Stop retrying PLOGI and FDISC if in FCF discovery */
			if (phba->fcf.fcf_flag & FCF_DISCOVERY) {
				lpfc_printf_vlog(vport, KERN_INFO, LOG_ELS,
						 "2849 Stop retry ELS command "
						 "x%x to remote NPORT x%x, "
						 "Data: x%x x%x\n", cmd, did,
						 cmdiocb->retry, delay);
				return 0;
			}
		}

		/* Retry ELS command <elsCmd> to remote NPORT <did> */
		lpfc_printf_vlog(vport, KERN_INFO, LOG_ELS,
				 "0107 Retry ELS command x%x to remote "
				 "NPORT x%x Data: x%x x%x\n",
				 cmd, did, cmdiocb->retry, delay);

		if (((cmd == ELS_CMD_PLOGI) || (cmd == ELS_CMD_ADISC)) &&
			((irsp->ulpStatus != IOSTAT_LOCAL_REJECT) ||
			((irsp->un.ulpWord[4] & IOERR_PARAM_MASK) !=
			IOERR_NO_RESOURCES))) {
			/* Don't reset timer for no resources */

			/* If discovery / RSCN timer is running, reset it */
			if (timer_pending(&vport->fc_disctmo) ||
			    (vport->fc_flag & FC_RSCN_MODE))
				lpfc_set_disctmo(vport);
		}

		phba->fc_stat.elsXmitRetry++;
		if (ndlp && NLP_CHK_NODE_ACT(ndlp) && delay) {
			phba->fc_stat.elsDelayRetry++;
			ndlp->nlp_retry = cmdiocb->retry;

			/* delay is specified in milliseconds */
			mod_timer(&ndlp->nlp_delayfunc,
				jiffies + msecs_to_jiffies(delay));
			spin_lock_irq(shost->host_lock);
			ndlp->nlp_flag |= NLP_DELAY_TMO;
			spin_unlock_irq(shost->host_lock);

			ndlp->nlp_prev_state = ndlp->nlp_state;
			if (cmd == ELS_CMD_PRLI)
				lpfc_nlp_set_state(vport, ndlp,
					NLP_STE_PRLI_ISSUE);
			else
				lpfc_nlp_set_state(vport, ndlp,
					NLP_STE_NPR_NODE);
			ndlp->nlp_last_elscmd = cmd;

			return 1;
		}
		switch (cmd) {
		case ELS_CMD_FLOGI:
			lpfc_issue_els_flogi(vport, ndlp, cmdiocb->retry);
			return 1;
		case ELS_CMD_FDISC:
			lpfc_issue_els_fdisc(vport, ndlp, cmdiocb->retry);
			return 1;
		case ELS_CMD_PLOGI:
			if (ndlp && NLP_CHK_NODE_ACT(ndlp)) {
				ndlp->nlp_prev_state = ndlp->nlp_state;
				lpfc_nlp_set_state(vport, ndlp,
						   NLP_STE_PLOGI_ISSUE);
			}
			lpfc_issue_els_plogi(vport, did, cmdiocb->retry);
			return 1;
		case ELS_CMD_ADISC:
			ndlp->nlp_prev_state = ndlp->nlp_state;
			lpfc_nlp_set_state(vport, ndlp, NLP_STE_ADISC_ISSUE);
			lpfc_issue_els_adisc(vport, ndlp, cmdiocb->retry);
			return 1;
		case ELS_CMD_PRLI:
			ndlp->nlp_prev_state = ndlp->nlp_state;
			lpfc_nlp_set_state(vport, ndlp, NLP_STE_PRLI_ISSUE);
			lpfc_issue_els_prli(vport, ndlp, cmdiocb->retry);
			return 1;
		case ELS_CMD_LOGO:
			ndlp->nlp_prev_state = ndlp->nlp_state;
			lpfc_nlp_set_state(vport, ndlp, NLP_STE_LOGO_ISSUE);
			lpfc_issue_els_logo(vport, ndlp, cmdiocb->retry);
			return 1;
		}
	}
	/* No retry ELS command <elsCmd> to remote NPORT <did> */
	if (logerr) {
		lpfc_printf_vlog(vport, KERN_ERR, LOG_ELS,
			 "0137 No retry ELS command x%x to remote "
			 "NPORT x%x: Out of Resources: Error:x%x/%x\n",
			 cmd, did, irsp->ulpStatus,
			 irsp->un.ulpWord[4]);
	}
	else {
		lpfc_printf_vlog(vport, KERN_INFO, LOG_ELS,
			 "0108 No retry ELS command x%x to remote "
			 "NPORT x%x Retried:%d Error:x%x/%x\n",
			 cmd, did, cmdiocb->retry, irsp->ulpStatus,
			 irsp->un.ulpWord[4]);
	}
	return 0;
}