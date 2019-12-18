#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  u_int64_t ;
typedef  int u_int32_t ;
struct timeval {int /*<<< orphan*/  tv_sec; } ;
struct nfsreq_secinfo_args {int dummy; } ;
struct nfsmount {int nm_vers; int /*<<< orphan*/  nm_auth; int /*<<< orphan*/  nm_minor_vers; } ;
struct nfsm_chain {int dummy; } ;
typedef  TYPE_2__* nfsnode_t ;
struct TYPE_15__ {int nva_flags; } ;
struct TYPE_16__ {int n_flag; int* n_access; int /*<<< orphan*/ * n_accessstamp; int /*<<< orphan*/ * n_accessuid; int /*<<< orphan*/  n_auth; int /*<<< orphan*/  n_fhsize; int /*<<< orphan*/  n_fhp; TYPE_1__ n_vattr; } ;
struct TYPE_14__ {int n_flag; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENXIO ; 
 int /*<<< orphan*/  EPROTO ; 
 int /*<<< orphan*/  NFSPROC4_COMPOUND ; 
 int /*<<< orphan*/  NFSREQ_SECINFO_SET (struct nfsreq_secinfo_args*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nfsmount* NFSTONMP (TYPE_2__*) ; 
 int /*<<< orphan*/  NFSTOV (TYPE_2__*) ; 
 int NFSX_UNSIGNED ; 
 int NFS_ACCESS_DELETE ; 
 int NFS_ACCESS_EXTEND ; 
 int NFS_ACCESS_MODIFY ; 
 int NFS_FFLAG_TRIGGER_REFERRAL ; 
 int NFS_OP_ACCESS ; 
 int NFS_OP_GETATTR ; 
 int NFS_OP_PUTFH ; 
 int NISDOTZFSCHILD ; 
 scalar_t__ NULLVP ; 
 TYPE_10__* VTONFS (scalar_t__) ; 
 scalar_t__ auth_is_kerberized (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_getuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  microuptime (struct timeval*) ; 
 scalar_t__ nfs_access_delete ; 
 scalar_t__ nfs_access_dotzfs ; 
 int /*<<< orphan*/  nfs_cred_getasid2uid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_getattr_bitmap ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 
 int nfs_node_access_slot (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int nfs_node_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  nfs_node_unlock (TYPE_2__*) ; 
 int nfs_request2 (TYPE_2__*,int /*<<< orphan*/ *,struct nfsm_chain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfsreq_secinfo_args*,int,struct nfsm_chain*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  nfsm_assert (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_add_32 (int,struct nfsm_chain*,int) ; 
 int /*<<< orphan*/  nfsm_chain_add_bitmap_supported (int,struct nfsm_chain*,int /*<<< orphan*/ ,struct nfsmount*,TYPE_2__*) ; 
 int /*<<< orphan*/  nfsm_chain_add_compound_header (int,struct nfsm_chain*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfsm_chain_add_fh (int,struct nfsm_chain*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_build_alloc_init (int,struct nfsm_chain*,int) ; 
 int /*<<< orphan*/  nfsm_chain_build_done (int,struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_cleanup (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_get_32 (int,struct nfsm_chain*,int) ; 
 int /*<<< orphan*/  nfsm_chain_loadattr (int,struct nfsm_chain*,TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsm_chain_null (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_op_check (int,struct nfsm_chain*,int) ; 
 int /*<<< orphan*/  nfsm_chain_skip_tag (int,struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsmout_if (int) ; 
 int /*<<< orphan*/  vfs_context_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 
 scalar_t__ vnode_getparent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_put (scalar_t__) ; 

int
nfs4_access_rpc(nfsnode_t np, u_int32_t *access, int rpcflags, vfs_context_t ctx)
{
	int error = 0, lockerror = ENOENT, status, numops, slot;
	u_int64_t xid;
	struct nfsm_chain nmreq, nmrep;
	struct timeval now;
	uint32_t access_result = 0, supported = 0, missing;
	struct nfsmount *nmp = NFSTONMP(np);
	int nfsvers = nmp->nm_vers;
	uid_t uid;
	struct nfsreq_secinfo_args si;

	if (np->n_vattr.nva_flags & NFS_FFLAG_TRIGGER_REFERRAL)
		return (0);

	NFSREQ_SECINFO_SET(&si, np, NULL, 0, NULL, 0);
	nfsm_chain_null(&nmreq);
	nfsm_chain_null(&nmrep);

	// PUTFH, ACCESS, GETATTR
	numops = 3;
	nfsm_chain_build_alloc_init(error, &nmreq, 17 * NFSX_UNSIGNED);
	nfsm_chain_add_compound_header(error, &nmreq, "access", nmp->nm_minor_vers, numops);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_PUTFH);
	nfsm_chain_add_fh(error, &nmreq, nfsvers, np->n_fhp, np->n_fhsize);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_ACCESS);
	nfsm_chain_add_32(error, &nmreq, *access);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_GETATTR);
	nfsm_chain_add_bitmap_supported(error, &nmreq, nfs_getattr_bitmap, nmp, np);
	nfsm_chain_build_done(error, &nmreq);
	nfsm_assert(error, (numops == 0), EPROTO);
	nfsmout_if(error);
	error = nfs_request2(np, NULL, &nmreq, NFSPROC4_COMPOUND,
		vfs_context_thread(ctx), vfs_context_ucred(ctx),
		&si, rpcflags, &nmrep, &xid, &status);

	if ((lockerror = nfs_node_lock(np)))
		error = lockerror;
	nfsm_chain_skip_tag(error, &nmrep);
	nfsm_chain_get_32(error, &nmrep, numops);
	nfsm_chain_op_check(error, &nmrep, NFS_OP_PUTFH);
	nfsm_chain_op_check(error, &nmrep, NFS_OP_ACCESS);
	nfsm_chain_get_32(error, &nmrep, supported);
	nfsm_chain_get_32(error, &nmrep, access_result);
	nfsmout_if(error);
	if ((missing = (*access & ~supported))) {
		/* missing support for something(s) we wanted */
		if (missing & NFS_ACCESS_DELETE) {
			/*
			 * If the server doesn't report DELETE (possible
			 * on UNIX systems), we'll assume that it is OK
			 * and just let any subsequent delete action fail
			 * if it really isn't deletable.
			 */
			access_result |= NFS_ACCESS_DELETE;
		}
	}
	/* ".zfs" subdirectories may erroneously give a denied answer for modify/delete */
	if (nfs_access_dotzfs) {
		vnode_t dvp = NULLVP;
		if (np->n_flag & NISDOTZFSCHILD) /* may be able to create/delete snapshot dirs */
			access_result |= (NFS_ACCESS_MODIFY|NFS_ACCESS_EXTEND|NFS_ACCESS_DELETE);
		else if (((dvp = vnode_getparent(NFSTOV(np))) != NULLVP) && (VTONFS(dvp)->n_flag & NISDOTZFSCHILD))
			access_result |= NFS_ACCESS_DELETE; /* may be able to delete snapshot dirs */
		if (dvp != NULLVP)
			vnode_put(dvp);
	}
	/* Some servers report DELETE support but erroneously give a denied answer. */
	if (nfs_access_delete && (*access & NFS_ACCESS_DELETE) && !(access_result & NFS_ACCESS_DELETE))
		access_result |= NFS_ACCESS_DELETE;
	nfsm_chain_op_check(error, &nmrep, NFS_OP_GETATTR);
	nfsm_chain_loadattr(error, &nmrep, np, nfsvers, &xid);
	nfsmout_if(error);

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

	/* pass back the access returned with this request */
	*access = np->n_access[slot];
nfsmout:
	if (!lockerror)
		nfs_node_unlock(np);
	nfsm_chain_cleanup(&nmreq);
	nfsm_chain_cleanup(&nmrep);
	return (error);
}