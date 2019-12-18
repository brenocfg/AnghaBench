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
 scalar_t__ NLP_CHK_FREE_REQ (struct lpfc_nodelist*) ; 
 scalar_t__ NLP_CHK_IACT_REQ (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  NLP_SET_FREE_ACK (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  NLP_SET_IACT_REQ (struct lpfc_nodelist*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int kref_put (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_debugfs_disc_trc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lpfc_nlp_release ; 
 int /*<<< orphan*/  lpfc_printf_vlog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
lpfc_nlp_put(struct lpfc_nodelist *ndlp)
{
	struct lpfc_hba *phba;
	unsigned long flags;

	if (!ndlp)
		return 1;

	lpfc_debugfs_disc_trc(ndlp->vport, LPFC_DISC_TRC_NODE,
	"node put:        did:x%x flg:x%x refcnt:x%x",
		ndlp->nlp_DID, ndlp->nlp_flag,
		atomic_read(&ndlp->kref.refcount));
	phba = ndlp->phba;
	spin_lock_irqsave(&phba->ndlp_lock, flags);
	/* Check the ndlp memory free acknowledge flag to avoid the
	 * possible race condition that kref_put got invoked again
	 * after previous one has done ndlp memory free.
	 */
	if (NLP_CHK_FREE_ACK(ndlp)) {
		spin_unlock_irqrestore(&phba->ndlp_lock, flags);
		lpfc_printf_vlog(ndlp->vport, KERN_WARNING, LOG_NODE,
				"0274 lpfc_nlp_put: ndlp:x%p "
				"usgmap:x%x refcnt:%d\n",
				(void *)ndlp, ndlp->nlp_usg_map,
				atomic_read(&ndlp->kref.refcount));
		return 1;
	}
	/* Check the ndlp inactivate log flag to avoid the possible
	 * race condition that kref_put got invoked again after ndlp
	 * is already in inactivating state.
	 */
	if (NLP_CHK_IACT_REQ(ndlp)) {
		spin_unlock_irqrestore(&phba->ndlp_lock, flags);
		lpfc_printf_vlog(ndlp->vport, KERN_WARNING, LOG_NODE,
				"0275 lpfc_nlp_put: ndlp:x%p "
				"usgmap:x%x refcnt:%d\n",
				(void *)ndlp, ndlp->nlp_usg_map,
				atomic_read(&ndlp->kref.refcount));
		return 1;
	}
	/* For last put, mark the ndlp usage flags to make sure no
	 * other kref_get and kref_put on the same ndlp shall get
	 * in between the process when the final kref_put has been
	 * invoked on this ndlp.
	 */
	if (atomic_read(&ndlp->kref.refcount) == 1) {
		/* Indicate ndlp is put to inactive state. */
		NLP_SET_IACT_REQ(ndlp);
		/* Acknowledge ndlp memory free has been seen. */
		if (NLP_CHK_FREE_REQ(ndlp))
			NLP_SET_FREE_ACK(ndlp);
	}
	spin_unlock_irqrestore(&phba->ndlp_lock, flags);
	/* Note, the kref_put returns 1 when decrementing a reference
	 * count that was 1, it invokes the release callback function,
	 * but it still left the reference count as 1 (not actually
	 * performs the last decrementation). Otherwise, it actually
	 * decrements the reference count and returns 0.
	 */
	return kref_put(&ndlp->kref, lpfc_nlp_release);
}