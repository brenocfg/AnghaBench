#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct nfsmount {int /*<<< orphan*/  nm_lock; int /*<<< orphan*/  nm_dreturnq; } ;
typedef  TYPE_2__* nfsnode_t ;
struct TYPE_6__ {scalar_t__ tqe_next; } ;
struct TYPE_7__ {TYPE_1__ n_dreturn; int /*<<< orphan*/  n_openlock; int /*<<< orphan*/  n_openflags; } ;

/* Variables and functions */
 scalar_t__ NFSNOLIST ; 
 struct nfsmount* NFSTONMP (TYPE_2__*) ; 
 int /*<<< orphan*/  N_DELEG_RETURN ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  n_dreturn ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 
 int /*<<< orphan*/  nfs_mount_sock_thread_wake (struct nfsmount*) ; 

void
nfs4_delegation_return_enqueue(nfsnode_t np)
{
	struct nfsmount *nmp;

	nmp = NFSTONMP(np);
	if (nfs_mount_gone(nmp))
		return;

	lck_mtx_lock(&np->n_openlock);
	np->n_openflags |= N_DELEG_RETURN;
	lck_mtx_unlock(&np->n_openlock);

	lck_mtx_lock(&nmp->nm_lock);
	if (np->n_dreturn.tqe_next == NFSNOLIST)
		TAILQ_INSERT_TAIL(&nmp->nm_dreturnq, np, n_dreturn);
	nfs_mount_sock_thread_wake(nmp);
	lck_mtx_unlock(&nmp->nm_lock);
}