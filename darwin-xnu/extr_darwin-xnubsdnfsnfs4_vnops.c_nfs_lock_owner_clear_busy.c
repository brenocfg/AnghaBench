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
struct nfs_lock_owner {int nlo_flags; int /*<<< orphan*/  nlo_lock; } ;

/* Variables and functions */
 int NFS_LOCK_OWNER_BUSY ; 
 int NFS_LOCK_OWNER_WANT ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  wakeup (struct nfs_lock_owner*) ; 

void
nfs_lock_owner_clear_busy(struct nfs_lock_owner *nlop)
{
	int wanted;

	lck_mtx_lock(&nlop->nlo_lock);
	if (!(nlop->nlo_flags & NFS_LOCK_OWNER_BUSY))
		panic("nfs_lock_owner_clear_busy");
	wanted = (nlop->nlo_flags & NFS_LOCK_OWNER_WANT);
	nlop->nlo_flags &= ~(NFS_LOCK_OWNER_BUSY|NFS_LOCK_OWNER_WANT);
	lck_mtx_unlock(&nlop->nlo_lock);
	if (wanted)
		wakeup(nlop);
}