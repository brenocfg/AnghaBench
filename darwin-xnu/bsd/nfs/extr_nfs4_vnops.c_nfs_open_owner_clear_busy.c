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
struct nfs_open_owner {int noo_flags; int /*<<< orphan*/  noo_lock; } ;

/* Variables and functions */
 int NFS_OPEN_OWNER_BUSY ; 
 int NFS_OPEN_OWNER_WANT ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  wakeup (struct nfs_open_owner*) ; 

void
nfs_open_owner_clear_busy(struct nfs_open_owner *noop)
{
	int wanted;

	lck_mtx_lock(&noop->noo_lock);
	if (!(noop->noo_flags & NFS_OPEN_OWNER_BUSY))
		panic("nfs_open_owner_clear_busy");
	wanted = (noop->noo_flags & NFS_OPEN_OWNER_WANT);
	noop->noo_flags &= ~(NFS_OPEN_OWNER_BUSY|NFS_OPEN_OWNER_WANT);
	lck_mtx_unlock(&noop->noo_lock);
	if (wanted)
		wakeup(noop);
}