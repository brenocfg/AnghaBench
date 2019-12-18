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
struct nfsmount {int nm_stategenid; scalar_t__ nm_stateinuse; int nm_state; int /*<<< orphan*/  nm_lock; int /*<<< orphan*/  nm_mountp; } ;
struct TYPE_2__ {char* f_mntfromname; } ;

/* Variables and functions */
 int NFSERR_GRACE ; 
 int NFSERR_OLD_STATEID ; 
 int NFSSTA_RECOVER ; 
 scalar_t__ PZERO ; 
 int hz ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 
 int nfs_mount_state_error_should_restart (int) ; 
 int /*<<< orphan*/  nfs_need_recover (struct nfsmount*,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,int,char*,int) ; 
 int /*<<< orphan*/  tsleep (int*,scalar_t__,char*,int) ; 
 TYPE_1__* vfs_statfs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (scalar_t__*) ; 

int
nfs_mount_state_in_use_end(struct nfsmount *nmp, int error)
{
	int restart = nfs_mount_state_error_should_restart(error);

	if (nfs_mount_gone(nmp))
		return (restart);
	lck_mtx_lock(&nmp->nm_lock);
	if (restart && (error != NFSERR_OLD_STATEID) && (error != NFSERR_GRACE)) {
		printf("nfs_mount_state_in_use_end: error %d, initiating recovery for %s, 0x%x\n",
			error, vfs_statfs(nmp->nm_mountp)->f_mntfromname, nmp->nm_stategenid);
		nfs_need_recover(nmp, error);
	}
	if (nmp->nm_stateinuse > 0)
		nmp->nm_stateinuse--;
	else
		panic("NFS mount state in use count underrun");
	if (!nmp->nm_stateinuse && (nmp->nm_state & NFSSTA_RECOVER))
		wakeup(&nmp->nm_stateinuse);
	lck_mtx_unlock(&nmp->nm_lock);
	if (error == NFSERR_GRACE)
		tsleep(&nmp->nm_state, (PZERO-1), "nfsgrace", 2*hz);

	return (restart);
}