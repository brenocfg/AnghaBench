#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct lpfc_vport {int fc_flag; struct lpfc_hba* phba; } ;
struct TYPE_9__ {int sli_flag; } ;
struct lpfc_hba {int fc_ratov; int /*<<< orphan*/  mbox_mem_pool; int /*<<< orphan*/  cfg_link_speed; int /*<<< orphan*/  cfg_topology; TYPE_1__ sli; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
struct TYPE_10__ {scalar_t__ mbxStatus; int /*<<< orphan*/  mbxOwner; int /*<<< orphan*/  mbxCommand; } ;
struct TYPE_11__ {TYPE_2__ mb; } ;
struct TYPE_12__ {TYPE_3__ u; } ;
typedef  TYPE_4__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int EPERM ; 
 int FC_OFFLINE_MODE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int LOG_MBOX ; 
 int LOG_SLI ; 
 int LPFC_BLOCK_MGMT_IO ; 
 int LPFC_MBOX_TMO ; 
 int MBXERR_ERROR ; 
 scalar_t__ MBXERR_LINK_DOWN ; 
 scalar_t__ MBXERR_SEC_NO_PERMISSION ; 
 int /*<<< orphan*/  MBX_DOWN_LINK ; 
 int MBX_SUCCESS ; 
 int MBX_TIMEOUT ; 
 int /*<<< orphan*/  OWN_HOST ; 
 int /*<<< orphan*/  lpfc_init_link (struct lpfc_hba*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  lpfc_set_loopback_flag (struct lpfc_hba*) ; 
 int lpfc_sli_issue_mbox_wait (struct lpfc_hba*,TYPE_4__*,int) ; 
 TYPE_4__* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
lpfc_issue_lip(struct Scsi_Host *shost)
{
	struct lpfc_vport *vport = (struct lpfc_vport *) shost->hostdata;
	struct lpfc_hba   *phba = vport->phba;
	LPFC_MBOXQ_t *pmboxq;
	int mbxstatus = MBXERR_ERROR;

	if ((vport->fc_flag & FC_OFFLINE_MODE) ||
	    (phba->sli.sli_flag & LPFC_BLOCK_MGMT_IO))
		return -EPERM;

	pmboxq = mempool_alloc(phba->mbox_mem_pool,GFP_KERNEL);

	if (!pmboxq)
		return -ENOMEM;

	memset((void *)pmboxq, 0, sizeof (LPFC_MBOXQ_t));
	pmboxq->u.mb.mbxCommand = MBX_DOWN_LINK;
	pmboxq->u.mb.mbxOwner = OWN_HOST;

	mbxstatus = lpfc_sli_issue_mbox_wait(phba, pmboxq, LPFC_MBOX_TMO * 2);

	if ((mbxstatus == MBX_SUCCESS) &&
	    (pmboxq->u.mb.mbxStatus == 0 ||
	     pmboxq->u.mb.mbxStatus == MBXERR_LINK_DOWN)) {
		memset((void *)pmboxq, 0, sizeof (LPFC_MBOXQ_t));
		lpfc_init_link(phba, pmboxq, phba->cfg_topology,
			       phba->cfg_link_speed);
		mbxstatus = lpfc_sli_issue_mbox_wait(phba, pmboxq,
						     phba->fc_ratov * 2);
		if ((mbxstatus == MBX_SUCCESS) &&
		    (pmboxq->u.mb.mbxStatus == MBXERR_SEC_NO_PERMISSION))
			lpfc_printf_log(phba, KERN_ERR, LOG_MBOX | LOG_SLI,
					"2859 SLI authentication is required "
					"for INIT_LINK but has not done yet\n");
	}

	lpfc_set_loopback_flag(phba);
	if (mbxstatus != MBX_TIMEOUT)
		mempool_free(pmboxq, phba->mbox_mem_pool);

	if (mbxstatus == MBXERR_ERROR)
		return -EIO;

	return 0;
}