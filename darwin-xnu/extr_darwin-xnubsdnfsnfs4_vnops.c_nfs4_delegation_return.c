#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thread_t ;
struct nfsmount {int /*<<< orphan*/  nm_lock; int /*<<< orphan*/  nm_dreturnq; int /*<<< orphan*/  nm_delegations; } ;
typedef  TYPE_3__* nfsnode_t ;
typedef  int /*<<< orphan*/  nfs_stateid ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
struct TYPE_15__ {int /*<<< orphan*/  fh_len; int /*<<< orphan*/  fh_data; } ;
typedef  TYPE_4__ fhandle_t ;
struct TYPE_13__ {scalar_t__ tqe_next; } ;
struct TYPE_12__ {scalar_t__ tqe_next; } ;
struct TYPE_14__ {int n_openflags; int /*<<< orphan*/  n_openlock; TYPE_2__ n_dreturn; TYPE_1__ n_dlink; int /*<<< orphan*/  n_fhp; int /*<<< orphan*/  n_fhsize; int /*<<< orphan*/  n_dstateid; } ;

/* Variables and functions */
 int ENXIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  NFSERR_EXPIRED ; 
 int NFSERR_LEASE_MOVED ; 
 int NFSERR_MOVED ; 
 scalar_t__ NFSNOLIST ; 
 struct nfsmount* NFSTONMP (TYPE_3__*) ; 
 int /*<<< orphan*/  NP (TYPE_3__*,char*,int) ; 
 int N_DELEG_MASK ; 
 int N_DELEG_RETURN ; 
 int N_DELEG_RETURNING ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  n_dlink ; 
 int /*<<< orphan*/  n_dreturn ; 
 int nfs4_claim_delegated_state_for_node (TYPE_3__*,int) ; 
 int nfs4_delegreturn_rpc (struct nfsmount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 
 scalar_t__ nfs_mount_state_error_delegation_lost (int) ; 
 scalar_t__ nfs_mount_state_error_should_restart (int) ; 
 int /*<<< orphan*/  nfs_need_reconnect (struct nfsmount*) ; 
 int /*<<< orphan*/  nfs_need_recover (struct nfsmount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_open_state_clear_busy (TYPE_3__*) ; 
 int nfs_open_state_set_busy (TYPE_3__*,int /*<<< orphan*/ *) ; 

int
nfs4_delegation_return(nfsnode_t np, int flags, thread_t thd, kauth_cred_t cred)
{
	struct nfsmount *nmp;
	fhandle_t fh;
	nfs_stateid dstateid;
	int error;

	nmp = NFSTONMP(np);
	if (nfs_mount_gone(nmp))
		return (ENXIO);

	/* first, make sure the node's marked for delegation return */
	lck_mtx_lock(&np->n_openlock);
	np->n_openflags |= (N_DELEG_RETURN|N_DELEG_RETURNING);
	lck_mtx_unlock(&np->n_openlock);

	/* make sure nobody else is using the delegation state */
	if ((error = nfs_open_state_set_busy(np, NULL)))
		goto out;

	/* claim any delegated state */
	if ((error = nfs4_claim_delegated_state_for_node(np, flags)))
		goto out;

	/* return the delegation */
	lck_mtx_lock(&np->n_openlock);
	dstateid = np->n_dstateid;
	fh.fh_len = np->n_fhsize;
	bcopy(np->n_fhp, &fh.fh_data, fh.fh_len);
	lck_mtx_unlock(&np->n_openlock);
	error = nfs4_delegreturn_rpc(NFSTONMP(np), fh.fh_data, fh.fh_len, &dstateid, flags, thd, cred);
	/* assume delegation is gone for all errors except ETIMEDOUT, NFSERR_*MOVED */
	if ((error != ETIMEDOUT) && (error != NFSERR_MOVED) && (error != NFSERR_LEASE_MOVED)) {
		lck_mtx_lock(&np->n_openlock);
		np->n_openflags &= ~N_DELEG_MASK;
		lck_mtx_lock(&nmp->nm_lock);
		if (np->n_dlink.tqe_next != NFSNOLIST) {
			TAILQ_REMOVE(&nmp->nm_delegations, np, n_dlink);
			np->n_dlink.tqe_next = NFSNOLIST;
		}
		lck_mtx_unlock(&nmp->nm_lock);
		lck_mtx_unlock(&np->n_openlock);
	}

out:
	/* make sure it's no longer on the return queue and clear the return flags */
	lck_mtx_lock(&nmp->nm_lock);
	if (np->n_dreturn.tqe_next != NFSNOLIST) {
		TAILQ_REMOVE(&nmp->nm_dreturnq, np, n_dreturn);
		np->n_dreturn.tqe_next = NFSNOLIST;
	}
	lck_mtx_unlock(&nmp->nm_lock);
	lck_mtx_lock(&np->n_openlock);
	np->n_openflags &= ~(N_DELEG_RETURN|N_DELEG_RETURNING);
	lck_mtx_unlock(&np->n_openlock);

	if (error) {
		NP(np, "nfs4_delegation_return, error %d", error);
		if (error == ETIMEDOUT)
			nfs_need_reconnect(nmp);
		if (nfs_mount_state_error_should_restart(error)) {
			/* make sure recovery happens */
			lck_mtx_lock(&nmp->nm_lock);
			nfs_need_recover(nmp, nfs_mount_state_error_delegation_lost(error) ? NFSERR_EXPIRED : 0);
			lck_mtx_unlock(&nmp->nm_lock);
		}
	}

	nfs_open_state_clear_busy(np);

	return (error);
}