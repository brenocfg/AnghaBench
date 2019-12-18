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
struct TYPE_2__ {scalar_t__ tqe_next; } ;
struct nfsmount {TYPE_1__ nm_ldlink; } ;
typedef  scalar_t__ mach_port_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 scalar_t__ IPC_PORT_DEAD ; 
 scalar_t__ IPC_PORT_NULL ; 
 int /*<<< orphan*/  IPC_PORT_VALID (scalar_t__) ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ NFSNOLIST ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct nfsmount*,int /*<<< orphan*/ ) ; 
 scalar_t__ host_get_lockd_port (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  host_priv_self () ; 
 int /*<<< orphan*/  ipc_port_release_send (scalar_t__) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ lockd_shutdown (scalar_t__) ; 
 int /*<<< orphan*/  nfs_lock_mutex ; 
 int /*<<< orphan*/  nfs_lockd_mount_list ; 
 scalar_t__ nfs_lockd_mounts ; 
 scalar_t__ nfs_lockd_request_sent ; 
 int /*<<< orphan*/  nm_ldlink ; 
 int /*<<< orphan*/  printf (char*,scalar_t__,...) ; 

void
nfs_lockd_mount_unregister(struct nfsmount *nmp)
{
	int send_shutdown;
	mach_port_t lockd_port = IPC_PORT_NULL;
	kern_return_t kr;

	lck_mtx_lock(nfs_lock_mutex);
	if (nmp->nm_ldlink.tqe_next == NFSNOLIST) {
		lck_mtx_unlock(nfs_lock_mutex);
		return;
	}
	
	TAILQ_REMOVE(&nfs_lockd_mount_list, nmp, nm_ldlink);
	nmp->nm_ldlink.tqe_next = NFSNOLIST;

	nfs_lockd_mounts--;

	/* send a shutdown request if there are no more lockd mounts */
	send_shutdown = ((nfs_lockd_mounts == 0) && nfs_lockd_request_sent);
	if (send_shutdown)
		nfs_lockd_request_sent = 0;

	lck_mtx_unlock(nfs_lock_mutex);

	if (!send_shutdown)
		return;

	/*
	 * Let lockd know that it is no longer needed for any NFS mounts
	 */
	kr = host_get_lockd_port(host_priv_self(), &lockd_port);
	if ((kr != KERN_SUCCESS) || !IPC_PORT_VALID(lockd_port)) {
		printf("nfs_lockd_mount_change: shutdown couldn't get port, kr %d, port %s\n",
			kr, (lockd_port == IPC_PORT_NULL) ? "NULL" :
			(lockd_port == IPC_PORT_DEAD) ? "DEAD" : "VALID");
		return;
	}

	kr = lockd_shutdown(lockd_port);
	if (kr != KERN_SUCCESS)
		printf("nfs_lockd_mount_change: shutdown %d\n", kr);

	ipc_port_release_send(lockd_port);
}