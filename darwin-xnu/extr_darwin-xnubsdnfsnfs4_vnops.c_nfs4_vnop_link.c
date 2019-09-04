#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int /*<<< orphan*/  u_int64_t ;
struct vnop_link_args {struct componentname* a_cnp; int /*<<< orphan*/  a_tdvp; int /*<<< orphan*/  a_vp; int /*<<< orphan*/  a_context; } ;
struct nfsreq_secinfo_args {int dummy; } ;
struct nfsmount {int nm_vers; int /*<<< orphan*/  nm_minor_vers; } ;
struct nfsm_chain {int dummy; } ;
struct componentname {scalar_t__ cn_namelen; int /*<<< orphan*/  cn_nameptr; } ;
typedef  TYPE_2__* nfsnode_t ;
struct TYPE_19__ {int nva_flags; } ;
struct TYPE_20__ {int n_flag; int /*<<< orphan*/  n_fhsize; int /*<<< orphan*/  n_fhp; TYPE_1__ n_vattr; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENXIO ; 
 int /*<<< orphan*/  EPROTO ; 
 int EXDEV ; 
 int /*<<< orphan*/  MNT_WAIT ; 
 int /*<<< orphan*/  NATTRINVALIDATE (TYPE_2__*) ; 
 int /*<<< orphan*/  NFSPROC4_COMPOUND ; 
 int /*<<< orphan*/  NFSREQ_SECINFO_SET (struct nfsreq_secinfo_args*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int NFSX_UNSIGNED ; 
 int NFS_FFLAG_TRIGGER_REFERRAL ; 
 int /*<<< orphan*/  NFS_OP_GETATTR ; 
 int /*<<< orphan*/  NFS_OP_LINK ; 
 int /*<<< orphan*/  NFS_OP_PUTFH ; 
 int /*<<< orphan*/  NFS_OP_RESTOREFH ; 
 int /*<<< orphan*/  NFS_OP_SAVEFH ; 
 int NMODIFIED ; 
 int NNEGNCENTRIES ; 
 TYPE_2__* VTONFS (int /*<<< orphan*/ ) ; 
 struct nfsmount* VTONMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_IGNORE_WRITEERR ; 
 int /*<<< orphan*/  cache_purge_negatives (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_flush (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_getattr_bitmap ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 
 int /*<<< orphan*/  nfs_node_clear_busy2 (TYPE_2__*,TYPE_2__*) ; 
 int nfs_node_lock2 (TYPE_2__*,TYPE_2__*) ; 
 int nfs_node_set_busy2 (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_node_unlock2 (TYPE_2__*,TYPE_2__*) ; 
 int nfs_request (TYPE_2__*,int /*<<< orphan*/ *,struct nfsm_chain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfsreq_secinfo_args*,struct nfsm_chain*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  nfsm_assert (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_add_32 (int,struct nfsm_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_add_bitmap_supported (int,struct nfsm_chain*,int /*<<< orphan*/ ,struct nfsmount*,TYPE_2__*) ; 
 int /*<<< orphan*/  nfsm_chain_add_compound_header (int,struct nfsm_chain*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfsm_chain_add_fh (int,struct nfsm_chain*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_add_name (int,struct nfsm_chain*,int /*<<< orphan*/ ,scalar_t__,struct nfsmount*) ; 
 int /*<<< orphan*/  nfsm_chain_build_alloc_init (int,struct nfsm_chain*,scalar_t__) ; 
 int /*<<< orphan*/  nfsm_chain_build_done (int,struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_check_change_info (int,struct nfsm_chain*,TYPE_2__*) ; 
 int /*<<< orphan*/  nfsm_chain_cleanup (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_get_32 (int,struct nfsm_chain*,int) ; 
 int /*<<< orphan*/  nfsm_chain_loadattr (int,struct nfsm_chain*,TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsm_chain_null (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_op_check (int,struct nfsm_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_skip_tag (int,struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsmout_if (int) ; 
 int /*<<< orphan*/  vfs_context_thread (int /*<<< orphan*/ ) ; 
 scalar_t__ vnode_mount (int /*<<< orphan*/ ) ; 

int
nfs4_vnop_link(
	struct vnop_link_args /* {
		struct vnodeop_desc *a_desc;
		vnode_t a_vp;
		vnode_t a_tdvp;
		struct componentname *a_cnp;
		vfs_context_t a_context;
	} */ *ap)
{
	vfs_context_t ctx = ap->a_context;
	vnode_t vp = ap->a_vp;
	vnode_t tdvp = ap->a_tdvp;
	struct componentname *cnp = ap->a_cnp;
	int error = 0, lockerror = ENOENT, status;
	struct nfsmount *nmp;
	nfsnode_t np = VTONFS(vp);
	nfsnode_t tdnp = VTONFS(tdvp);
	int nfsvers, numops;
	u_int64_t xid, savedxid;
	struct nfsm_chain nmreq, nmrep;
	struct nfsreq_secinfo_args si;

	if (vnode_mount(vp) != vnode_mount(tdvp))
		return (EXDEV);

	nmp = VTONMP(vp);
	if (nfs_mount_gone(nmp))
		return (ENXIO);
	nfsvers = nmp->nm_vers;
	if (np->n_vattr.nva_flags & NFS_FFLAG_TRIGGER_REFERRAL)
		return (EINVAL);
	if (tdnp->n_vattr.nva_flags & NFS_FFLAG_TRIGGER_REFERRAL)
		return (EINVAL);

	/*
	 * Push all writes to the server, so that the attribute cache
	 * doesn't get "out of sync" with the server.
	 * XXX There should be a better way!
	 */
	nfs_flush(np, MNT_WAIT, vfs_context_thread(ctx), V_IGNORE_WRITEERR);

	if ((error = nfs_node_set_busy2(tdnp, np, vfs_context_thread(ctx))))
		return (error);

	NFSREQ_SECINFO_SET(&si, np, NULL, 0, NULL, 0);
	nfsm_chain_null(&nmreq);
	nfsm_chain_null(&nmrep);

	// PUTFH(SOURCE), SAVEFH, PUTFH(DIR), LINK, GETATTR(DIR), RESTOREFH, GETATTR
	numops = 7;
	nfsm_chain_build_alloc_init(error, &nmreq, 29 * NFSX_UNSIGNED + cnp->cn_namelen);
	nfsm_chain_add_compound_header(error, &nmreq, "link", nmp->nm_minor_vers, numops);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_PUTFH);
	nfsm_chain_add_fh(error, &nmreq, nfsvers, np->n_fhp, np->n_fhsize);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_SAVEFH);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_PUTFH);
	nfsm_chain_add_fh(error, &nmreq, nfsvers, tdnp->n_fhp, tdnp->n_fhsize);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_LINK);
	nfsm_chain_add_name(error, &nmreq, cnp->cn_nameptr, cnp->cn_namelen, nmp);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_GETATTR);
	nfsm_chain_add_bitmap_supported(error, &nmreq, nfs_getattr_bitmap, nmp, tdnp);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_RESTOREFH);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_GETATTR);
	nfsm_chain_add_bitmap_supported(error, &nmreq, nfs_getattr_bitmap, nmp, np);
	nfsm_chain_build_done(error, &nmreq);
	nfsm_assert(error, (numops == 0), EPROTO);
	nfsmout_if(error);
	error = nfs_request(tdnp, NULL, &nmreq, NFSPROC4_COMPOUND, ctx, &si, &nmrep, &xid, &status);

	if ((lockerror = nfs_node_lock2(tdnp, np))) {
		error = lockerror;
		goto nfsmout;
	}
	nfsm_chain_skip_tag(error, &nmrep);
	nfsm_chain_get_32(error, &nmrep, numops);
	nfsm_chain_op_check(error, &nmrep, NFS_OP_PUTFH);
	nfsm_chain_op_check(error, &nmrep, NFS_OP_SAVEFH);
	nfsm_chain_op_check(error, &nmrep, NFS_OP_PUTFH);
	nfsm_chain_op_check(error, &nmrep, NFS_OP_LINK);
	nfsm_chain_check_change_info(error, &nmrep, tdnp);
	/* directory attributes: if we don't get them, make sure to invalidate */
	nfsm_chain_op_check(error, &nmrep, NFS_OP_GETATTR);
	savedxid = xid;
	nfsm_chain_loadattr(error, &nmrep, tdnp, nfsvers, &xid);
	if (error)
		NATTRINVALIDATE(tdnp);
	/* link attributes: if we don't get them, make sure to invalidate */
	nfsm_chain_op_check(error, &nmrep, NFS_OP_RESTOREFH);
	nfsm_chain_op_check(error, &nmrep, NFS_OP_GETATTR);
	xid = savedxid;
	nfsm_chain_loadattr(error, &nmrep, np, nfsvers, &xid);
	if (error)
		NATTRINVALIDATE(np);
nfsmout:
	nfsm_chain_cleanup(&nmreq);
	nfsm_chain_cleanup(&nmrep);
	if (!lockerror)
		tdnp->n_flag |= NMODIFIED;
	/* Kludge: Map EEXIST => 0 assuming that it is a reply to a retry. */
	if (error == EEXIST)
		error = 0;
	if (!error && (tdnp->n_flag & NNEGNCENTRIES)) {
		tdnp->n_flag &= ~NNEGNCENTRIES;
		cache_purge_negatives(tdvp);
	}
	if (!lockerror)
		nfs_node_unlock2(tdnp, np);
	nfs_node_clear_busy2(tdnp, np);
	return (error);
}