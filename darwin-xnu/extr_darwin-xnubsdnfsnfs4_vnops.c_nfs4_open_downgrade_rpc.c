#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int /*<<< orphan*/  u_int64_t ;
struct nfsreq_secinfo_args {int dummy; } ;
struct nfsmount {int nm_vers; int /*<<< orphan*/  nm_minor_vers; } ;
struct nfsm_chain {int dummy; } ;
struct nfs_open_owner {int /*<<< orphan*/  noo_seqid; } ;
struct nfs_open_file {int /*<<< orphan*/  nof_stateid; int /*<<< orphan*/  nof_deny; int /*<<< orphan*/  nof_access; struct nfs_open_owner* nof_owner; } ;
typedef  TYPE_1__* nfsnode_t ;
struct TYPE_10__ {int /*<<< orphan*/  n_fhsize; int /*<<< orphan*/  n_fhp; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENXIO ; 
 int /*<<< orphan*/  EPROTO ; 
 int /*<<< orphan*/  NFSPROC4_COMPOUND ; 
 int /*<<< orphan*/  NFSREQ_SECINFO_SET (struct nfsreq_secinfo_args*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nfsmount* NFSTONMP (TYPE_1__*) ; 
 int NFSX_UNSIGNED ; 
 int /*<<< orphan*/  NFS_OP_GETATTR ; 
 int /*<<< orphan*/  NFS_OP_OPEN_DOWNGRADE ; 
 int /*<<< orphan*/  NFS_OP_PUTFH ; 
 int /*<<< orphan*/  R_NOINTR ; 
 int /*<<< orphan*/  nfs_getattr_bitmap ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 
 int nfs_node_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  nfs_node_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  nfs_open_owner_clear_busy (struct nfs_open_owner*) ; 
 int nfs_open_owner_set_busy (struct nfs_open_owner*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_owner_seqid_increment (struct nfs_open_owner*,int /*<<< orphan*/ *,int) ; 
 int nfs_request2 (TYPE_1__*,int /*<<< orphan*/ *,struct nfsm_chain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfsreq_secinfo_args*,int /*<<< orphan*/ ,struct nfsm_chain*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  nfsm_assert (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_add_32 (int,struct nfsm_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_add_bitmap_supported (int,struct nfsm_chain*,int /*<<< orphan*/ ,struct nfsmount*,TYPE_1__*) ; 
 int /*<<< orphan*/  nfsm_chain_add_compound_header (int,struct nfsm_chain*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfsm_chain_add_fh (int,struct nfsm_chain*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_add_stateid (int,struct nfsm_chain*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsm_chain_build_alloc_init (int,struct nfsm_chain*,int) ; 
 int /*<<< orphan*/  nfsm_chain_build_done (int,struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_cleanup (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_get_32 (int,struct nfsm_chain*,int) ; 
 int /*<<< orphan*/  nfsm_chain_get_stateid (int,struct nfsm_chain*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsm_chain_loadattr (int,struct nfsm_chain*,TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsm_chain_null (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_op_check (int,struct nfsm_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_skip_tag (int,struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsmout_if (int) ; 
 int /*<<< orphan*/  vfs_context_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 

int
nfs4_open_downgrade_rpc(
	nfsnode_t np,
	struct nfs_open_file *nofp,
	vfs_context_t ctx)
{
	struct nfs_open_owner *noop = nofp->nof_owner;
	struct nfsmount *nmp;
	int error, lockerror = ENOENT, status, nfsvers, numops;
	struct nfsm_chain nmreq, nmrep;
	u_int64_t xid;
	struct nfsreq_secinfo_args si;

	nmp = NFSTONMP(np);
	if (nfs_mount_gone(nmp))
		return (ENXIO);
	nfsvers = nmp->nm_vers;

	if ((error = nfs_open_owner_set_busy(noop, NULL)))
		return (error);

	NFSREQ_SECINFO_SET(&si, np, NULL, 0, NULL, 0);
	nfsm_chain_null(&nmreq);
	nfsm_chain_null(&nmrep);

	// PUTFH, OPEN_DOWNGRADE, GETATTR
	numops = 3;
	nfsm_chain_build_alloc_init(error, &nmreq, 23 * NFSX_UNSIGNED);
	nfsm_chain_add_compound_header(error, &nmreq, "open_downgrd", nmp->nm_minor_vers, numops);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_PUTFH);
	nfsm_chain_add_fh(error, &nmreq, nfsvers, np->n_fhp, np->n_fhsize);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_OPEN_DOWNGRADE);
	nfsm_chain_add_stateid(error, &nmreq, &nofp->nof_stateid);
	nfsm_chain_add_32(error, &nmreq, noop->noo_seqid);
	nfsm_chain_add_32(error, &nmreq, nofp->nof_access);
	nfsm_chain_add_32(error, &nmreq, nofp->nof_deny);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_GETATTR);
	nfsm_chain_add_bitmap_supported(error, &nmreq, nfs_getattr_bitmap, nmp, np);
	nfsm_chain_build_done(error, &nmreq);
	nfsm_assert(error, (numops == 0), EPROTO);
	nfsmout_if(error);
	error = nfs_request2(np, NULL, &nmreq, NFSPROC4_COMPOUND,
			vfs_context_thread(ctx), vfs_context_ucred(ctx),
			&si, R_NOINTR, &nmrep, &xid, &status);

	if ((lockerror = nfs_node_lock(np)))
		error = lockerror;
	nfsm_chain_skip_tag(error, &nmrep);
	nfsm_chain_get_32(error, &nmrep, numops);
	nfsm_chain_op_check(error, &nmrep, NFS_OP_PUTFH);
	nfsmout_if(error);
	nfsm_chain_op_check(error, &nmrep, NFS_OP_OPEN_DOWNGRADE);
	nfs_owner_seqid_increment(noop, NULL, error);
	nfsm_chain_get_stateid(error, &nmrep, &nofp->nof_stateid);
	nfsm_chain_op_check(error, &nmrep, NFS_OP_GETATTR);
	nfsm_chain_loadattr(error, &nmrep, np, nfsvers, &xid);
nfsmout:
	if (!lockerror)
		nfs_node_unlock(np);
	nfs_open_owner_clear_busy(noop);
	nfsm_chain_cleanup(&nmreq);
	nfsm_chain_cleanup(&nmrep);
	return (error);
}