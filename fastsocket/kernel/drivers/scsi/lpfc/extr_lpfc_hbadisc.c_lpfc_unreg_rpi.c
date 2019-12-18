#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct lpfc_vport {int /*<<< orphan*/  vpi; struct lpfc_hba* phba; } ;
struct lpfc_nodelist {int nlp_flag; size_t nlp_rpi; } ;
struct TYPE_7__ {size_t* rpi_ids; } ;
struct lpfc_hba {scalar_t__ sli_rev; int /*<<< orphan*/  mbox_mem_pool; TYPE_1__ sli4_hba; } ;
struct TYPE_8__ {int /*<<< orphan*/  mbox_cmpl; struct lpfc_nodelist* context1; struct lpfc_vport* vport; } ;
typedef  TYPE_2__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int MBX_NOT_FINISHED ; 
 int /*<<< orphan*/  MBX_NOWAIT ; 
 int NLP_ISSUE_LOGO ; 
 int NLP_NPR_ADISC ; 
 int NLP_RPI_REGISTERED ; 
 int /*<<< orphan*/  lpfc_nlp_logo_unreg ; 
 int /*<<< orphan*/  lpfc_no_rpi (struct lpfc_hba*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_sli_def_mbox_cmpl ; 
 int lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_unreg_login (struct lpfc_hba*,int /*<<< orphan*/ ,size_t,TYPE_2__*) ; 
 TYPE_2__* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_2__*,int /*<<< orphan*/ ) ; 

int
lpfc_unreg_rpi(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp)
{
	struct lpfc_hba *phba = vport->phba;
	LPFC_MBOXQ_t    *mbox;
	int rc;
	uint16_t rpi;

	if (ndlp->nlp_flag & NLP_RPI_REGISTERED) {
		mbox = mempool_alloc(phba->mbox_mem_pool, GFP_KERNEL);
		if (mbox) {
			/* SLI4 ports require the physical rpi value. */
			rpi = ndlp->nlp_rpi;
			if (phba->sli_rev == LPFC_SLI_REV4)
				rpi = phba->sli4_hba.rpi_ids[ndlp->nlp_rpi];

			lpfc_unreg_login(phba, vport->vpi, rpi, mbox);
			mbox->vport = vport;
			if (ndlp->nlp_flag & NLP_ISSUE_LOGO) {
				mbox->context1 = ndlp;
				mbox->mbox_cmpl = lpfc_nlp_logo_unreg;
			} else {
				mbox->mbox_cmpl = lpfc_sli_def_mbox_cmpl;
			}

			rc = lpfc_sli_issue_mbox(phba, mbox, MBX_NOWAIT);
			if (rc == MBX_NOT_FINISHED)
				mempool_free(mbox, phba->mbox_mem_pool);
		}
		lpfc_no_rpi(phba, ndlp);

		if (phba->sli_rev != LPFC_SLI_REV4)
			ndlp->nlp_rpi = 0;
		ndlp->nlp_flag &= ~NLP_RPI_REGISTERED;
		ndlp->nlp_flag &= ~NLP_NPR_ADISC;
		return 1;
	}
	return 0;
}