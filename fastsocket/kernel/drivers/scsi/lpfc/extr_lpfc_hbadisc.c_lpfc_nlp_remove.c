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
typedef  int /*<<< orphan*/  uint8_t ;
struct lpfc_vport {int /*<<< orphan*/  fc_sparam; int /*<<< orphan*/  vpi; struct lpfc_hba* phba; } ;
struct lpfc_rport_data {int /*<<< orphan*/ * pnode; } ;
struct lpfc_nodelist {int nlp_flag; TYPE_1__* rport; int /*<<< orphan*/  nlp_rpi; int /*<<< orphan*/  nlp_DID; } ;
struct lpfc_hba {int /*<<< orphan*/  mbox_mem_pool; } ;
struct TYPE_8__ {struct lpfc_nodelist* context2; struct lpfc_vport* vport; int /*<<< orphan*/  mbox_cmpl; int /*<<< orphan*/  mbox_flag; } ;
struct TYPE_7__ {struct lpfc_rport_data* dd_data; } ;
typedef  TYPE_2__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LPFC_MBX_IMED_UNREG ; 
 int MBX_NOT_FINISHED ; 
 int /*<<< orphan*/  MBX_NOWAIT ; 
 int NLP_DEFER_RM ; 
 int NLP_REG_LOGIN_SEND ; 
 int NLP_RPI_REGISTERED ; 
 int /*<<< orphan*/  lpfc_cancel_retry_delay_tmo (struct lpfc_vport*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_cleanup_node (struct lpfc_vport*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_mbx_cmpl_dflt_rpi ; 
 int lpfc_reg_rpi (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpfc_nlp_remove(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp)
{
	struct lpfc_hba  *phba = vport->phba;
	struct lpfc_rport_data *rdata;
	LPFC_MBOXQ_t *mbox;
	int rc;

	lpfc_cancel_retry_delay_tmo(vport, ndlp);
	if ((ndlp->nlp_flag & NLP_DEFER_RM) &&
	    !(ndlp->nlp_flag & NLP_REG_LOGIN_SEND) &&
	    !(ndlp->nlp_flag & NLP_RPI_REGISTERED)) {
		/* For this case we need to cleanup the default rpi
		 * allocated by the firmware.
		 */
		if ((mbox = mempool_alloc(phba->mbox_mem_pool, GFP_KERNEL))
			!= NULL) {
			rc = lpfc_reg_rpi(phba, vport->vpi, ndlp->nlp_DID,
			    (uint8_t *) &vport->fc_sparam, mbox, ndlp->nlp_rpi);
			if (rc) {
				mempool_free(mbox, phba->mbox_mem_pool);
			}
			else {
				mbox->mbox_flag |= LPFC_MBX_IMED_UNREG;
				mbox->mbox_cmpl = lpfc_mbx_cmpl_dflt_rpi;
				mbox->vport = vport;
				mbox->context2 = ndlp;
				rc =lpfc_sli_issue_mbox(phba, mbox, MBX_NOWAIT);
				if (rc == MBX_NOT_FINISHED) {
					mempool_free(mbox, phba->mbox_mem_pool);
				}
			}
		}
	}
	lpfc_cleanup_node(vport, ndlp);

	/*
	 * We can get here with a non-NULL ndlp->rport because when we
	 * unregister a rport we don't break the rport/node linkage.  So if we
	 * do, make sure we don't leaving any dangling pointers behind.
	 */
	if (ndlp->rport) {
		rdata = ndlp->rport->dd_data;
		rdata->pnode = NULL;
		ndlp->rport = NULL;
	}
}