#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  qi_quotaofflock; int /*<<< orphan*/ * qi_gquotaip; int /*<<< orphan*/ * qi_uquotaip; int /*<<< orphan*/  qi_dqlist_lock; int /*<<< orphan*/  qi_dqlist; } ;
typedef  TYPE_1__ xfs_quotainfo_t ;
struct TYPE_7__ {TYPE_1__* m_quotainfo; } ;
typedef  TYPE_2__ xfs_mount_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRELE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xfs_Gqm ; 
 int /*<<< orphan*/  xfs_qm_rele_quotafs_ref (TYPE_2__*) ; 

void
xfs_qm_destroy_quotainfo(
	xfs_mount_t	*mp)
{
	xfs_quotainfo_t *qi;

	qi = mp->m_quotainfo;
	ASSERT(qi != NULL);
	ASSERT(xfs_Gqm != NULL);

	/*
	 * Release the reference that XQM kept, so that we know
	 * when the XQM structure should be freed. We cannot assume
	 * that xfs_Gqm is non-null after this point.
	 */
	xfs_qm_rele_quotafs_ref(mp);

	ASSERT(list_empty(&qi->qi_dqlist));
	mutex_destroy(&qi->qi_dqlist_lock);

	if (qi->qi_uquotaip) {
		IRELE(qi->qi_uquotaip);
		qi->qi_uquotaip = NULL; /* paranoia */
	}
	if (qi->qi_gquotaip) {
		IRELE(qi->qi_gquotaip);
		qi->qi_gquotaip = NULL;
	}
	mutex_destroy(&qi->qi_quotaofflock);
	kmem_free(qi);
	mp->m_quotainfo = NULL;
}