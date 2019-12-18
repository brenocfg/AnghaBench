#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct nfsmount {int /*<<< orphan*/  nm_lock; int /*<<< orphan*/  nm_state; } ;
typedef  TYPE_1__* nfsnode_t ;
struct TYPE_8__ {int n_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSSTA_REVOKE ; 
 struct nfsmount* NFSTONMP (TYPE_1__*) ; 
 int /*<<< orphan*/  NP (TYPE_1__*,char*,...) ; 
 int NREVOKE ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_mount_sock_thread_wake (struct nfsmount*) ; 
 int /*<<< orphan*/  nfs_node_lock_force (TYPE_1__*) ; 
 int /*<<< orphan*/  nfs_node_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  nfs_release_open_state_for_node (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
nfs_revoke_open_state_for_node(nfsnode_t np)
{
	struct nfsmount *nmp;

	/* mark node as needing to be revoked */
	nfs_node_lock_force(np);
	if (np->n_flag & NREVOKE)  /* already revoked? */
	{
		NP(np, "nfs_revoke_open_state_for_node(): already revoked");
		nfs_node_unlock(np);
		return;
	}
	np->n_flag |= NREVOKE;
	nfs_node_unlock(np);

	nfs_release_open_state_for_node(np, 0);
	NP(np, "nfs: state lost for %p 0x%x", np, np->n_flag);

	/* mark mount as needing a revoke scan and have the socket thread do it. */
	if ((nmp = NFSTONMP(np))) {
		lck_mtx_lock(&nmp->nm_lock);
		nmp->nm_state |= NFSSTA_REVOKE;
		nfs_mount_sock_thread_wake(nmp);
		lck_mtx_unlock(&nmp->nm_lock);
	}
}