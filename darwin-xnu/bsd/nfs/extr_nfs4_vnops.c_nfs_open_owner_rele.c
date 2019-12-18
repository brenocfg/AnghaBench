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
struct nfs_open_owner {int noo_refcnt; int noo_flags; int /*<<< orphan*/  noo_lock; } ;

/* Variables and functions */
 int NFS_OPEN_OWNER_BUSY ; 
 int NFS_OPEN_OWNER_LINK ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_open_owner_destroy (struct nfs_open_owner*) ; 
 int /*<<< orphan*/  panic (char*) ; 

void
nfs_open_owner_rele(struct nfs_open_owner *noop)
{
	lck_mtx_lock(&noop->noo_lock);
	if (noop->noo_refcnt < 1)
		panic("nfs_open_owner_rele: no refcnt");
	noop->noo_refcnt--;
	if (!noop->noo_refcnt && (noop->noo_flags & NFS_OPEN_OWNER_BUSY))
		panic("nfs_open_owner_rele: busy");
	/* XXX we may potentially want to clean up idle/unused open owner structures */
	if (noop->noo_refcnt || (noop->noo_flags & NFS_OPEN_OWNER_LINK)) {
		lck_mtx_unlock(&noop->noo_lock);
		return;
	}
	/* owner is no longer referenced or linked to mount, so destroy it */
	lck_mtx_unlock(&noop->noo_lock);
	nfs_open_owner_destroy(noop);
}