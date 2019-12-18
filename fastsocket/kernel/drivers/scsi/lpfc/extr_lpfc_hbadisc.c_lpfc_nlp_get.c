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
struct TYPE_2__ {int /*<<< orphan*/  refcount; } ;
struct lpfc_nodelist {TYPE_1__ kref; int /*<<< orphan*/  nlp_usg_map; int /*<<< orphan*/  vport; struct lpfc_hba* phba; int /*<<< orphan*/  nlp_flag; int /*<<< orphan*/  nlp_DID; } ;
struct lpfc_hba {int /*<<< orphan*/  ndlp_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  LOG_NODE ; 
 int /*<<< orphan*/  LPFC_DISC_TRC_NODE ; 
 scalar_t__ NLP_CHK_FREE_ACK (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  NLP_CHK_NODE_ACT (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_get (TYPE_1__*) ; 
 int /*<<< orphan*/  lpfc_debugfs_disc_trc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct lpfc_nodelist *
lpfc_nlp_get(struct lpfc_nodelist *ndlp)
{
	struct lpfc_hba *phba;
	unsigned long flags;

	if (ndlp) {
		lpfc_debugfs_disc_trc(ndlp->vport, LPFC_DISC_TRC_NODE,
			"node get:        did:x%x flg:x%x refcnt:x%x",
			ndlp->nlp_DID, ndlp->nlp_flag,
			atomic_read(&ndlp->kref.refcount));
		/* The check of ndlp usage to prevent incrementing the
		 * ndlp reference count that is in the process of being
		 * released.
		 */
		phba = ndlp->phba;
		spin_lock_irqsave(&phba->ndlp_lock, flags);
		if (!NLP_CHK_NODE_ACT(ndlp) || NLP_CHK_FREE_ACK(ndlp)) {
			spin_unlock_irqrestore(&phba->ndlp_lock, flags);
			lpfc_printf_vlog(ndlp->vport, KERN_WARNING, LOG_NODE,
				"0276 lpfc_nlp_get: ndlp:x%p "
				"usgmap:x%x refcnt:%d\n",
				(void *)ndlp, ndlp->nlp_usg_map,
				atomic_read(&ndlp->kref.refcount));
			return NULL;
		} else
			kref_get(&ndlp->kref);
		spin_unlock_irqrestore(&phba->ndlp_lock, flags);
	}
	return ndlp;
}