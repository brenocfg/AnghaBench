#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nfs_lock_owner {int nlo_refcnt; int nlo_flags; int /*<<< orphan*/  nlo_lock; } ;

/* Variables and functions */
 int NFS_LOCK_OWNER_BUSY ; 
 int NFS_LOCK_OWNER_LINK ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_lock_owner_destroy (struct nfs_lock_owner*) ; 
 int /*<<< orphan*/  panic (char*) ; 

void
nfs_lock_owner_rele(struct nfs_lock_owner *nlop)
{
	lck_mtx_lock(&nlop->nlo_lock);
	if (nlop->nlo_refcnt < 1)
		panic("nfs_lock_owner_rele: no refcnt");
	nlop->nlo_refcnt--;
	if (!nlop->nlo_refcnt && (nlop->nlo_flags & NFS_LOCK_OWNER_BUSY))
		panic("nfs_lock_owner_rele: busy");
	/* XXX we may potentially want to clean up idle/unused lock owner structures */
	if (nlop->nlo_refcnt || (nlop->nlo_flags & NFS_LOCK_OWNER_LINK)) {
		lck_mtx_unlock(&nlop->nlo_lock);
		return;
	}
	/* owner is no longer referenced or linked to mount, so destroy it */
	lck_mtx_unlock(&nlop->nlo_lock);
	nfs_lock_owner_destroy(nlop);
}