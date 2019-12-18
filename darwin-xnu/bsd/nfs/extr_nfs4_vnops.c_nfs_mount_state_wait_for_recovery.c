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
struct timespec {int member_0; int /*<<< orphan*/  member_1; } ;
struct nfsmount {int nm_state; int /*<<< orphan*/  nm_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTR ; 
 int NFSSTA_RECOVER ; 
 scalar_t__ NMFLAG (struct nfsmount*,int /*<<< orphan*/ ) ; 
 int PCATCH ; 
 int PZERO ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int*,int /*<<< orphan*/ *,int,char*,struct timespec*) ; 
 int /*<<< orphan*/  nfs_mount_sock_thread_wake (struct nfsmount*) ; 
 int nfs_sigintr (struct nfsmount*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
nfs_mount_state_wait_for_recovery(struct nfsmount *nmp)
{
	struct timespec ts = { 1, 0 };
	int error = 0, slpflag = NMFLAG(nmp, INTR) ? PCATCH : 0;

	lck_mtx_lock(&nmp->nm_lock);
	while (nmp->nm_state & NFSSTA_RECOVER) {
		if ((error = nfs_sigintr(nmp, NULL, current_thread(), 1)))
			break;
		nfs_mount_sock_thread_wake(nmp);
		msleep(&nmp->nm_state, &nmp->nm_lock, slpflag|(PZERO-1), "nfsrecoverwait", &ts);
		slpflag = 0;
	}
	lck_mtx_unlock(&nmp->nm_lock);

	return (error);
}