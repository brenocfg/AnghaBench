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
struct nfs_open_file {int /*<<< orphan*/  nof_lock; TYPE_1__* nof_owner; } ;
struct TYPE_2__ {int /*<<< orphan*/  noo_lock; int /*<<< orphan*/  noo_opens; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (struct nfs_open_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct nfs_open_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_open_grp ; 
 int /*<<< orphan*/  nfs_open_owner_rele (TYPE_1__*) ; 
 int /*<<< orphan*/  nof_oolink ; 

void
nfs_open_file_destroy(struct nfs_open_file *nofp)
{
	lck_mtx_lock(&nofp->nof_owner->noo_lock);
	TAILQ_REMOVE(&nofp->nof_owner->noo_opens, nofp, nof_oolink);
	lck_mtx_unlock(&nofp->nof_owner->noo_lock);
	nfs_open_owner_rele(nofp->nof_owner);
	lck_mtx_destroy(&nofp->nof_lock, nfs_open_grp);
	FREE(nofp, M_TEMP);
}