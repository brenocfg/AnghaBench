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
struct nfsmount {int nm_state; } ;

/* Variables and functions */
 int NFSERR_ADMIN_REVOKED ; 
 int NFSERR_EXPIRED ; 
 int NFSERR_STALE_CLIENTID ; 
 int NFSSTA_RECOVER ; 
 int NFSSTA_RECOVER_EXPIRED ; 
 int /*<<< orphan*/  nfs_mount_sock_thread_wake (struct nfsmount*) ; 

void
nfs_need_recover(struct nfsmount *nmp, int error)
{
	int wake = !(nmp->nm_state & NFSSTA_RECOVER);

	nmp->nm_state |= NFSSTA_RECOVER;
	if ((error == NFSERR_ADMIN_REVOKED) ||
	    (error == NFSERR_EXPIRED) ||
	    (error == NFSERR_STALE_CLIENTID))
		nmp->nm_state |= NFSSTA_RECOVER_EXPIRED;
	if (wake)
		nfs_mount_sock_thread_wake(nmp);
}