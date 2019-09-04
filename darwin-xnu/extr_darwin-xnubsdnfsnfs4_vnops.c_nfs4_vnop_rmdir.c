#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
struct vnop_rmdir_args {struct componentname* a_cnp; int /*<<< orphan*/  a_dvp; int /*<<< orphan*/  a_vp; int /*<<< orphan*/  a_context; } ;
struct TYPE_18__ {int nfsa_flags; } ;
struct nfsmount {TYPE_1__ nm_fsattr; } ;
struct nfs_dulookup {int dummy; } ;
struct componentname {int /*<<< orphan*/  cn_namelen; int /*<<< orphan*/  cn_nameptr; } ;
typedef  TYPE_2__* nfsnode_t ;
struct TYPE_19__ {int n_hflag; int /*<<< orphan*/  n_flag; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENXIO ; 
 int /*<<< orphan*/  FSDBG (int,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LIST_REMOVE (TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct nfsmount* NFSTONMP (TYPE_2__*) ; 
 int NFS_FSFLAG_NAMED_ATTR ; 
 int /*<<< orphan*/  NGA_CACHED ; 
 int NHHASHED ; 
 scalar_t__ VDIR ; 
 TYPE_2__* VTONFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  n_hash ; 
 int nfs4_remove_rpc (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_dulookup_finish (struct nfs_dulookup*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_dulookup_init (struct nfs_dulookup*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_dulookup_start (struct nfs_dulookup*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_getattr (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 
 int /*<<< orphan*/  nfs_name_cache_purge (TYPE_2__*,TYPE_2__*,struct componentname*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_node_clear_busy2 (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  nfs_node_hash_mutex ; 
 int nfs_node_set_busy2 (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 
 scalar_t__ vnode_vtype (int /*<<< orphan*/ ) ; 

int
nfs4_vnop_rmdir(
	struct vnop_rmdir_args /* {
		struct vnodeop_desc *a_desc;
		vnode_t a_dvp;
		vnode_t a_vp;
		struct componentname *a_cnp;
		vfs_context_t a_context;
	} */ *ap)
{
	vfs_context_t ctx = ap->a_context;
	vnode_t vp = ap->a_vp;
	vnode_t dvp = ap->a_dvp;
	struct componentname *cnp = ap->a_cnp;
	struct nfsmount *nmp;
	int error = 0, namedattrs;
	nfsnode_t np = VTONFS(vp);
	nfsnode_t dnp = VTONFS(dvp);
	struct nfs_dulookup dul;

	if (vnode_vtype(vp) != VDIR)
		return (EINVAL);

	nmp = NFSTONMP(dnp);
	if (nfs_mount_gone(nmp))
		return (ENXIO);
	namedattrs = (nmp->nm_fsattr.nfsa_flags & NFS_FSFLAG_NAMED_ATTR);

	if ((error = nfs_node_set_busy2(dnp, np, vfs_context_thread(ctx))))
		return (error);

	if (!namedattrs) {
		nfs_dulookup_init(&dul, dnp, cnp->cn_nameptr, cnp->cn_namelen, ctx);
		nfs_dulookup_start(&dul, dnp, ctx);
	}

	error = nfs4_remove_rpc(dnp, cnp->cn_nameptr, cnp->cn_namelen,
			vfs_context_thread(ctx), vfs_context_ucred(ctx));

	nfs_name_cache_purge(dnp, np, cnp, ctx);
	/* nfs_getattr() will check changed and purge caches */
	nfs_getattr(dnp, NULL, ctx, NGA_CACHED);
	if (!namedattrs)
		nfs_dulookup_finish(&dul, dnp, ctx);
	nfs_node_clear_busy2(dnp, np);

	/*
	 * Kludge: Map ENOENT => 0 assuming that you have a reply to a retry.
	 */
	if (error == ENOENT)
		error = 0;
	if (!error) {
		/*
		 * remove nfsnode from hash now so we can't accidentally find it
		 * again if another object gets created with the same filehandle
		 * before this vnode gets reclaimed
		 */
		lck_mtx_lock(nfs_node_hash_mutex);
		if (np->n_hflag & NHHASHED) {
			LIST_REMOVE(np, n_hash);
			np->n_hflag &= ~NHHASHED;
			FSDBG(266, 0, np, np->n_flag, 0xb1eb1e);
		}
		lck_mtx_unlock(nfs_node_hash_mutex);
	}
	return (error);
}