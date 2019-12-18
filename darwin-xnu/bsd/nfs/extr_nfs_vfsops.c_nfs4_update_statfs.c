#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_int64_t ;
struct nfsreq_secinfo_args {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  nfsa_bsize; } ;
struct nfsmount {int nm_vers; TYPE_7__ nm_fsattr; int /*<<< orphan*/  nm_lock; int /*<<< orphan*/  nm_minor_vers; TYPE_1__* nm_dnp; } ;
struct nfsm_chain {int dummy; } ;
struct nfs_vattr {int dummy; } ;
typedef  TYPE_1__* nfsnode_t ;
struct TYPE_11__ {int /*<<< orphan*/  n_fhsize; int /*<<< orphan*/  n_fhp; } ;

/* Variables and functions */
 int ENXIO ; 
 int EPROTO ; 
 int /*<<< orphan*/  NFS4_STATFS_ATTRIBUTES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFSPROC4_COMPOUND ; 
 int /*<<< orphan*/  NFSREQ_SECINFO_SET (struct nfsreq_secinfo_args*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int NFSTONMP (TYPE_1__*) ; 
 int /*<<< orphan*/  NFSTOV (TYPE_1__*) ; 
 int NFSX_UNSIGNED ; 
 int NFS_ATTR_BITMAP_LEN ; 
 int /*<<< orphan*/  NFS_COPY_ATTRIBUTES (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFS_FABLKSIZE ; 
 int /*<<< orphan*/  NFS_OP_GETATTR ; 
 int /*<<< orphan*/  NFS_OP_PUTFH ; 
 int /*<<< orphan*/  NVATTR_CLEANUP (struct nfs_vattr*) ; 
 int /*<<< orphan*/  NVATTR_INIT (struct nfs_vattr*) ; 
 int /*<<< orphan*/  R_SOFT ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int nfs4_parsefattr (struct nfsm_chain*,TYPE_7__*,struct nfs_vattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_getattr_bitmap ; 
 int /*<<< orphan*/  nfs_loadattrcache (TYPE_1__*,struct nfs_vattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nfs_node_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  nfs_node_unlock (TYPE_1__*) ; 
 int nfs_request2 (TYPE_1__*,int /*<<< orphan*/ *,struct nfsm_chain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nfsm_chain*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  nfsm_assert (int,int,int) ; 
 int /*<<< orphan*/  nfsm_chain_add_32 (int,struct nfsm_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_add_bitmap_supported (int,struct nfsm_chain*,int /*<<< orphan*/ *,struct nfsmount*,TYPE_1__*) ; 
 int /*<<< orphan*/  nfsm_chain_add_compound_header (int,struct nfsm_chain*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfsm_chain_add_fh (int,struct nfsm_chain*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_build_alloc_init (int,struct nfsm_chain*,int) ; 
 int /*<<< orphan*/  nfsm_chain_build_done (int,struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_cleanup (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_get_32 (int,struct nfsm_chain*,int) ; 
 int /*<<< orphan*/  nfsm_chain_null (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_op_check (int,struct nfsm_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_skip_tag (int,struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsmout_if (int) ; 
 int /*<<< orphan*/  vfs_context_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 
 int vnode_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_put (int /*<<< orphan*/ ) ; 

int
nfs4_update_statfs(struct nfsmount *nmp, vfs_context_t ctx)
{
	nfsnode_t np;
	int error = 0, lockerror, status, nfsvers, numops;
	u_int64_t xid;
	struct nfsm_chain nmreq, nmrep;
	uint32_t bitmap[NFS_ATTR_BITMAP_LEN];
	struct nfs_vattr nvattr;
	struct nfsreq_secinfo_args si;

	nfsvers = nmp->nm_vers;
	np = nmp->nm_dnp;
	if (!np)
		return (ENXIO);
	if ((error = vnode_get(NFSTOV(np))))
		return (error);

	NFSREQ_SECINFO_SET(&si, np, NULL, 0, NULL, 0);
	NVATTR_INIT(&nvattr);
	nfsm_chain_null(&nmreq);
	nfsm_chain_null(&nmrep);

	// PUTFH + GETATTR
	numops = 2;
	nfsm_chain_build_alloc_init(error, &nmreq, 15 * NFSX_UNSIGNED);
	nfsm_chain_add_compound_header(error, &nmreq, "statfs", nmp->nm_minor_vers, numops);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_PUTFH);
	nfsm_chain_add_fh(error, &nmreq, nfsvers, np->n_fhp, np->n_fhsize);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_GETATTR);
	NFS_COPY_ATTRIBUTES(nfs_getattr_bitmap, bitmap);
	NFS4_STATFS_ATTRIBUTES(bitmap);
	nfsm_chain_add_bitmap_supported(error, &nmreq, bitmap, nmp, np);
	nfsm_chain_build_done(error, &nmreq);
	nfsm_assert(error, (numops == 0), EPROTO);
	nfsmout_if(error);
	error = nfs_request2(np, NULL, &nmreq, NFSPROC4_COMPOUND,
		vfs_context_thread(ctx), vfs_context_ucred(ctx),
		NULL, R_SOFT, &nmrep, &xid, &status);
	nfsm_chain_skip_tag(error, &nmrep);
	nfsm_chain_get_32(error, &nmrep, numops);
	nfsm_chain_op_check(error, &nmrep, NFS_OP_PUTFH);
	nfsm_chain_op_check(error, &nmrep, NFS_OP_GETATTR);
	nfsm_assert(error, NFSTONMP(np), ENXIO);
	nfsmout_if(error);
	lck_mtx_lock(&nmp->nm_lock);
	error = nfs4_parsefattr(&nmrep, &nmp->nm_fsattr, &nvattr, NULL, NULL, NULL);
	lck_mtx_unlock(&nmp->nm_lock);
	nfsmout_if(error);
	if ((lockerror = nfs_node_lock(np)))
		error = lockerror;
	if (!error)
		nfs_loadattrcache(np, &nvattr, &xid, 0);
	if (!lockerror)
		nfs_node_unlock(np);
	nfsm_assert(error, NFSTONMP(np), ENXIO);
	nfsmout_if(error);
	nmp->nm_fsattr.nfsa_bsize = NFS_FABLKSIZE;
nfsmout:
	NVATTR_CLEANUP(&nvattr);
	nfsm_chain_cleanup(&nmreq);
	nfsm_chain_cleanup(&nmrep);
	vnode_put(NFSTOV(np));
	return (error);
}