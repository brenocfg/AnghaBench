#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ u_int64_t ;
struct timespec {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct nfsmount {int nm_state; int nm_vers; scalar_t__ nm_verf; int /*<<< orphan*/  nm_lock; } ;
struct nfsm_chain {int dummy; } ;
typedef  TYPE_1__* nfsnode_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
struct TYPE_9__ {int /*<<< orphan*/  n_fhsize; int /*<<< orphan*/  n_fhp; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  FSDBG (int,TYPE_1__*,scalar_t__,scalar_t__,int) ; 
 int NFSERR_STALEWRITEVERF ; 
 int /*<<< orphan*/  NFSPROC_COMMIT ; 
 int NFSSTA_HASWRITEVERF ; 
 struct nfsmount* NFSTONMP (TYPE_1__*) ; 
 int /*<<< orphan*/  NFSX_FH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFS_VER3 ; 
 scalar_t__ UINT32_MAX ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 
 int nfs_node_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  nfs_node_unlock (TYPE_1__*) ; 
 int nfs_request2 (TYPE_1__*,int /*<<< orphan*/ *,struct nfsm_chain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nfsm_chain*,scalar_t__*,int*) ; 
 int /*<<< orphan*/  nfsm_chain_add_32 (int,struct nfsm_chain*,scalar_t__) ; 
 int /*<<< orphan*/  nfsm_chain_add_64 (int,struct nfsm_chain*,scalar_t__) ; 
 int /*<<< orphan*/  nfsm_chain_add_fh (int,struct nfsm_chain*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_build_alloc_init (int,struct nfsm_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_build_done (int,struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_cleanup (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_get_64 (int,struct nfsm_chain*,scalar_t__) ; 
 int /*<<< orphan*/  nfsm_chain_get_wcc_data (int,struct nfsm_chain*,TYPE_1__*,struct timespec*,int*,scalar_t__*) ; 
 int /*<<< orphan*/  nfsm_chain_null (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsmout_if (int) ; 

int
nfs3_commit_rpc(
	nfsnode_t np,
	uint64_t offset,
	uint64_t count,
	kauth_cred_t cred,
	uint64_t wverf)
{
	struct nfsmount *nmp;
	int error = 0, lockerror, status, wccpostattr = 0, nfsvers;
	struct timespec premtime = { 0, 0 };
	u_int64_t xid, newwverf;
	uint32_t count32;
	struct nfsm_chain nmreq, nmrep;

	nmp = NFSTONMP(np);
	FSDBG(521, np, offset, count, nmp ? nmp->nm_state : 0);
	if (nfs_mount_gone(nmp))
		return (ENXIO);
	if (!(nmp->nm_state & NFSSTA_HASWRITEVERF))
		return (0);
	nfsvers = nmp->nm_vers;

	if (count > UINT32_MAX)
		count32 = 0;
	else
		count32 = count;

	nfsm_chain_null(&nmreq);
	nfsm_chain_null(&nmrep);

	nfsm_chain_build_alloc_init(error, &nmreq, NFSX_FH(NFS_VER3));
	nfsm_chain_add_fh(error, &nmreq, nfsvers, np->n_fhp, np->n_fhsize);
	nfsm_chain_add_64(error, &nmreq, offset);
	nfsm_chain_add_32(error, &nmreq, count32);
	nfsm_chain_build_done(error, &nmreq);
	nfsmout_if(error);
	error = nfs_request2(np, NULL, &nmreq, NFSPROC_COMMIT,
			current_thread(), cred, NULL, 0, &nmrep, &xid, &status);
	if ((lockerror = nfs_node_lock(np)))
		error = lockerror;
	/* can we do anything useful with the wcc info? */
	nfsm_chain_get_wcc_data(error, &nmrep, np, &premtime, &wccpostattr, &xid);
	if (!lockerror)
		nfs_node_unlock(np);
	if (!error)
		error = status;
	nfsm_chain_get_64(error, &nmrep, newwverf);
	nfsmout_if(error);
	lck_mtx_lock(&nmp->nm_lock);
	if (nmp->nm_verf != newwverf)
		nmp->nm_verf = newwverf;
	if (wverf != newwverf)
		error = NFSERR_STALEWRITEVERF;
	lck_mtx_unlock(&nmp->nm_lock);
nfsmout:
	nfsm_chain_cleanup(&nmreq);
	nfsm_chain_cleanup(&nmrep);
	return (error);
}