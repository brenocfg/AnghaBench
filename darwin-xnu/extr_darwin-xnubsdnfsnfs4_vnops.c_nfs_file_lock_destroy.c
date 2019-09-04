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
struct nfs_lock_owner {int /*<<< orphan*/  nlo_lock; } ;
struct nfs_file_lock {int nfl_flags; struct nfs_lock_owner* nfl_owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (struct nfs_file_lock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int NFS_FILE_LOCK_ALLOC ; 
 int /*<<< orphan*/  bzero (struct nfs_file_lock*,int) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_lock_owner_rele (struct nfs_lock_owner*) ; 

void
nfs_file_lock_destroy(struct nfs_file_lock *nflp)
{
	struct nfs_lock_owner *nlop = nflp->nfl_owner;

	if (nflp->nfl_flags & NFS_FILE_LOCK_ALLOC) {
		nflp->nfl_owner = NULL;
		FREE(nflp, M_TEMP);
	} else {
		lck_mtx_lock(&nlop->nlo_lock);
		bzero(nflp, sizeof(*nflp));
		lck_mtx_unlock(&nlop->nlo_lock);
	}
	nfs_lock_owner_rele(nlop);
}