#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct TYPE_2__ {int /*<<< orphan*/  refcount; } ;
struct lpfc_nodelist {int /*<<< orphan*/  nlp_DID; int /*<<< orphan*/  nlp_rpi; TYPE_1__ kref; int /*<<< orphan*/  nlp_usg_map; } ;
struct lpfc_hba {scalar_t__ sli_rev; int /*<<< orphan*/  ndlp_lock; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  LOG_NODE ; 
 int /*<<< orphan*/  LPFC_DISC_TRC_NODE ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 scalar_t__ NLP_CHK_FREE_REQ (struct lpfc_nodelist*) ; 
 scalar_t__ NLP_CHK_NODE_ACT (struct lpfc_nodelist*) ; 
 int NLP_STE_UNUSED_NODE ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_debugfs_disc_trc (struct lpfc_vport*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_initialize_node (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_nlp_set_state (struct lpfc_vport*,struct lpfc_nodelist*,int) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sli4_alloc_rpi (struct lpfc_hba*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct lpfc_nodelist *
lpfc_enable_node(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp,
		 int state)
{
	struct lpfc_hba *phba = vport->phba;
	uint32_t did;
	unsigned long flags;

	if (!ndlp)
		return NULL;

	spin_lock_irqsave(&phba->ndlp_lock, flags);
	/* The ndlp should not be in memory free mode */
	if (NLP_CHK_FREE_REQ(ndlp)) {
		spin_unlock_irqrestore(&phba->ndlp_lock, flags);
		lpfc_printf_vlog(vport, KERN_WARNING, LOG_NODE,
				"0277 lpfc_enable_node: ndlp:x%p "
				"usgmap:x%x refcnt:%d\n",
				(void *)ndlp, ndlp->nlp_usg_map,
				atomic_read(&ndlp->kref.refcount));
		return NULL;
	}
	/* The ndlp should not already be in active mode */
	if (NLP_CHK_NODE_ACT(ndlp)) {
		spin_unlock_irqrestore(&phba->ndlp_lock, flags);
		lpfc_printf_vlog(vport, KERN_WARNING, LOG_NODE,
				"0278 lpfc_enable_node: ndlp:x%p "
				"usgmap:x%x refcnt:%d\n",
				(void *)ndlp, ndlp->nlp_usg_map,
				atomic_read(&ndlp->kref.refcount));
		return NULL;
	}

	/* Keep the original DID */
	did = ndlp->nlp_DID;

	/* re-initialize ndlp except of ndlp linked list pointer */
	memset((((char *)ndlp) + sizeof (struct list_head)), 0,
		sizeof (struct lpfc_nodelist) - sizeof (struct list_head));
	lpfc_initialize_node(vport, ndlp, did);

	spin_unlock_irqrestore(&phba->ndlp_lock, flags);
	if (vport->phba->sli_rev == LPFC_SLI_REV4)
		ndlp->nlp_rpi = lpfc_sli4_alloc_rpi(vport->phba);


	if (state != NLP_STE_UNUSED_NODE)
		lpfc_nlp_set_state(vport, ndlp, state);

	lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_NODE,
		"node enable:       did:x%x",
		ndlp->nlp_DID, 0, 0);
	return ndlp;
}