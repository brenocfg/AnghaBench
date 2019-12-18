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
typedef  int /*<<< orphan*/  thread_t ;
struct timespec {int member_0; int /*<<< orphan*/  member_1; } ;
struct nfsmount {int nm_state; int nm_mounterror; int /*<<< orphan*/  nm_lock; scalar_t__ nm_nss; int /*<<< orphan*/  nm_sockflags; int /*<<< orphan*/  nm_mountp; } ;
struct TYPE_2__ {char* f_mntfromname; } ;

/* Variables and functions */
 int EIO ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  INTR ; 
 scalar_t__ KERN_SUCCESS ; 
 int NFSSTA_MOUNT_THREAD ; 
 scalar_t__ NMFLAG (struct nfsmount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NMSOCK_UNMOUNT ; 
 int PCATCH ; 
 int PSOCK ; 
 int /*<<< orphan*/  current_thread () ; 
 scalar_t__ kernel_thread_start (int /*<<< orphan*/ ,struct nfsmount*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int msleep (scalar_t__*,int /*<<< orphan*/ *,int,char*,struct timespec*) ; 
 int /*<<< orphan*/  nfs_mount_connect_thread ; 
 int nfs_sigintr (struct nfsmount*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  thread_deallocate (int /*<<< orphan*/ ) ; 
 TYPE_1__* vfs_statfs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (scalar_t__) ; 

int
nfs_mount_connect(struct nfsmount *nmp)
{
	int error = 0, slpflag;
	thread_t thd;
	struct timespec ts = { 2, 0 };

	/*
	 * Set up the socket.  Perform initial search for a location/server/address to
	 * connect to and negotiate any unspecified mount parameters.  This work is
	 * done on a kernel thread to satisfy reserved port usage needs.
	 */
	slpflag = NMFLAG(nmp, INTR) ? PCATCH : 0;
	lck_mtx_lock(&nmp->nm_lock);
	/* set flag that the thread is running */
	nmp->nm_state |= NFSSTA_MOUNT_THREAD;
	if (kernel_thread_start(nfs_mount_connect_thread, nmp, &thd) != KERN_SUCCESS) {
		nmp->nm_state &= ~NFSSTA_MOUNT_THREAD;
		nmp->nm_mounterror = EIO;
		printf("nfs mount %s start socket connect thread failed\n", vfs_statfs(nmp->nm_mountp)->f_mntfromname);
	} else {
		thread_deallocate(thd);
	}

	/* wait until mount connect thread is finished/gone */
	while (nmp->nm_state & NFSSTA_MOUNT_THREAD) {
		error = msleep(&nmp->nm_nss, &nmp->nm_lock, slpflag|PSOCK, "nfsconnectthread", &ts);
		if ((error && (error != EWOULDBLOCK)) || ((error = nfs_sigintr(nmp, NULL, current_thread(), 1)))) {
			/* record error */
			if (!nmp->nm_mounterror)
				nmp->nm_mounterror = error;
			/* signal the thread that we are aborting */
			nmp->nm_sockflags |= NMSOCK_UNMOUNT;
			if (nmp->nm_nss)
				wakeup(nmp->nm_nss);
			/* and continue waiting on it to finish */
			slpflag = 0;
		}
	}
	lck_mtx_unlock(&nmp->nm_lock);

	/* grab mount connect status */
	error = nmp->nm_mounterror;

	return (error);
}