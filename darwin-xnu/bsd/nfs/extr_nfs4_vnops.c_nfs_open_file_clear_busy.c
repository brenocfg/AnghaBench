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
struct nfs_open_file {int nof_flags; int /*<<< orphan*/  nof_lock; } ;

/* Variables and functions */
 int NFS_OPEN_FILE_BUSY ; 
 int NFS_OPEN_FILE_WANT ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  wakeup (struct nfs_open_file*) ; 

void
nfs_open_file_clear_busy(struct nfs_open_file *nofp)
{
	int wanted;

	lck_mtx_lock(&nofp->nof_lock);
	if (!(nofp->nof_flags & NFS_OPEN_FILE_BUSY))
		panic("nfs_open_file_clear_busy");
	wanted = (nofp->nof_flags & NFS_OPEN_FILE_WANT);
	nofp->nof_flags &= ~(NFS_OPEN_FILE_BUSY|NFS_OPEN_FILE_WANT);
	lck_mtx_unlock(&nofp->nof_lock);
	if (wanted)
		wakeup(nofp);
}