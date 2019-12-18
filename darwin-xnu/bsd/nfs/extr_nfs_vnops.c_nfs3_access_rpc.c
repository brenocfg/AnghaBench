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
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  u_int64_t ;
typedef  int u_int32_t ;
struct timeval {int /*<<< orphan*/  tv_sec; } ;
struct nfsmount {int /*<<< orphan*/  nm_auth; } ;
struct nfsm_chain {int dummy; } ;
typedef  TYPE_1__* nfsnode_t ;
struct TYPE_9__ {int* n_access; int n_flag; int /*<<< orphan*/ * n_accessstamp; int /*<<< orphan*/ * n_accessuid; int /*<<< orphan*/  n_auth; int /*<<< orphan*/  n_fhsize; int /*<<< orphan*/  n_fhp; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENXIO ; 
 int /*<<< orphan*/  NFSPROC_ACCESS ; 
 struct nfsmount* NFSTONMP (TYPE_1__*) ; 
 scalar_t__ NFSX_FH (int /*<<< orphan*/ ) ; 
 scalar_t__ NFSX_UNSIGNED ; 
 int NFS_ACCESS_DELETE ; 
 int NFS_ACCESS_EXTEND ; 
 int NFS_ACCESS_MODIFY ; 
 int /*<<< orphan*/  NFS_VER3 ; 
 int NISDOTZFSCHILD ; 
 scalar_t__ auth_is_kerberized (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_getuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  microuptime (struct timeval*) ; 
 scalar_t__ nfs_access_dotzfs ; 
 int /*<<< orphan*/  nfs_cred_getasid2uid (int /*<<< orphan*/ ) ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 
 int nfs_node_access_slot (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int nfs_node_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  nfs_node_unlock (TYPE_1__*) ; 
 int nfs_request2 (TYPE_1__*,int /*<<< orphan*/ *,struct nfsm_chain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct nfsm_chain*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  nfsm_chain_add_32 (int,struct nfsm_chain*,int) ; 
 int /*<<< orphan*/  nfsm_chain_add_fh (int,struct nfsm_chain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_build_alloc_init (int,struct nfsm_chain*,scalar_t__) ; 
 int /*<<< orphan*/  nfsm_chain_build_done (int,struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_cleanup (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_get_32 (int,struct nfsm_chain*,int) ; 
 int /*<<< orphan*/  nfsm_chain_null (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_postop_attr_update (int,struct nfsm_chain*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsmout_if (int) ; 
 int /*<<< orphan*/  vfs_context_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 

int
nfs3_access_rpc(nfsnode_t np, u_int32_t *access, int rpcflags, vfs_context_t ctx)
{
	int error = 0, lockerror = ENOENT, status, slot;
	uint32_t access_result = 0;
	u_int64_t xid;
	struct nfsm_chain nmreq, nmrep;
	struct nfsmount *nmp;
	struct timeval now;
	uid_t uid;

	nfsm_chain_null(&nmreq);
	nfsm_chain_null(&nmrep);

	nfsm_chain_build_alloc_init(error, &nmreq, NFSX_FH(NFS_VER3) + NFSX_UNSIGNED);
	nfsm_chain_add_fh(error, &nmreq, NFS_VER3, np->n_fhp, np->n_fhsize);
	nfsm_chain_add_32(error, &nmreq, *access);
	nfsm_chain_build_done(error, &nmreq);
	nfsmout_if(error);
	error = nfs_request2(np, NULL, &nmreq, NFSPROC_ACCESS,
		vfs_context_thread(ctx), vfs_context_ucred(ctx),
		NULL, rpcflags, &nmrep, &xid, &status);
	if ((lockerror = nfs_node_lock(np)))
		error = lockerror;
	nfsm_chain_postop_attr_update(error, &nmrep, np, &xid);
	if (!error)
		error = status;
	nfsm_chain_get_32(error, &nmrep, access_result);
	nfsmout_if(error);

	/* XXXab do we really need mount here, also why are we doing access cache management here? */
	nmp = NFSTONMP(np);
	if (nfs_mount_gone(nmp)) {
		error = ENXIO;
	}
	nfsmout_if(error);

	if (auth_is_kerberized(np->n_auth) || auth_is_kerberized(nmp->nm_auth)) {
		uid = nfs_cred_getasid2uid(vfs_context_ucred(ctx));
	} else {
		uid = kauth_cred_getuid(vfs_context_ucred(ctx));
	}
	slot = nfs_node_access_slot(np, uid, 1);
	np->n_accessuid[slot] = uid;
	microuptime(&now);
	np->n_accessstamp[slot] = now.tv_sec;
	np->n_access[slot] = access_result;

	/*
	 * If we asked for DELETE but didn't get it, the server
	 * may simply not support returning that bit (possible
	 * on UNIX systems).  So, we'll assume that it is OK,
	 * and just let any subsequent delete action fail if it
	 * really isn't deletable.
	 */
	if ((*access & NFS_ACCESS_DELETE) &&
	    !(np->n_access[slot] & NFS_ACCESS_DELETE))
		np->n_access[slot] |= NFS_ACCESS_DELETE;
	/* ".zfs" subdirectories may erroneously give a denied answer for add/remove */
	if (nfs_access_dotzfs && (np->n_flag & NISDOTZFSCHILD))
		np->n_access[slot] |= (NFS_ACCESS_MODIFY|NFS_ACCESS_EXTEND|NFS_ACCESS_DELETE);
	/* pass back the access returned with this request */
	*access = np->n_access[slot];
nfsmout:
	if (!lockerror)
		nfs_node_unlock(np);
	nfsm_chain_cleanup(&nmreq);
	nfsm_chain_cleanup(&nmrep);
	return (error);
}