#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
struct vnop_rename_args {struct componentname* a_fcnp; struct componentname* a_tcnp; int /*<<< orphan*/ * a_tvp; int /*<<< orphan*/ * a_tdvp; int /*<<< orphan*/ * a_fvp; int /*<<< orphan*/ * a_fdvp; int /*<<< orphan*/  a_context; } ;
struct nfsmount {int nm_vers; TYPE_1__* nm_funcs; } ;
struct nfs_vattr {int nva_nlink; } ;
struct componentname {int /*<<< orphan*/  cn_namelen; int /*<<< orphan*/  cn_nameptr; } ;
typedef  TYPE_2__* nfsnode_t ;
typedef  int /*<<< orphan*/ * mount_t ;
struct TYPE_29__ {int n_hflag; int n_openflags; int n_flag; int /*<<< orphan*/ * n_parent; int /*<<< orphan*/  n_sillyrename; } ;
struct TYPE_28__ {int (* nf_rename_rpc ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENOENT ; 
 int ENXIO ; 
 int EXDEV ; 
 int /*<<< orphan*/  FSDBG (int,int /*<<< orphan*/ ,TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  LIST_REMOVE (TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct nfsmount* NFSTONMP (TYPE_2__*) ; 
 int NFS_VER4 ; 
 int /*<<< orphan*/  NGA_CACHED ; 
 int NHHASHED ; 
 int NHLOCKED ; 
 int NHLOCKWANT ; 
 int NMODIFIED ; 
 int NNEGNCENTRIES ; 
 int N_DELEG_MASK ; 
 int /*<<< orphan*/  PINOD ; 
 scalar_t__ VDIR ; 
 TYPE_2__* VTONFS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cache_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct componentname*) ; 
 int /*<<< orphan*/  cache_purge_negatives (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  n_hash ; 
 int /*<<< orphan*/  nfs4_delegation_return (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_getattr (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nfs_getattrcache (TYPE_2__*,struct nfs_vattr*,int /*<<< orphan*/ ) ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 
 int /*<<< orphan*/  nfs_name_cache_purge (TYPE_2__*,TYPE_2__*,struct componentname*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_node_clear_busy4 (TYPE_2__*,TYPE_2__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  nfs_node_hash_mutex ; 
 int /*<<< orphan*/  nfs_node_lock_force (TYPE_2__*) ; 
 int nfs_node_set_busy4 (TYPE_2__*,TYPE_2__*,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_node_unlock (TYPE_2__*) ; 
 int nfs_sillyrename (TYPE_2__*,TYPE_2__*,struct componentname*,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_get (int /*<<< orphan*/ *) ; 
 int vnode_isinuse (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vnode_mount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnode_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnode_recycle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnode_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnode_rele (int /*<<< orphan*/ *) ; 
 scalar_t__ vnode_vtype (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (TYPE_2__*) ; 

int
nfs_vnop_rename(
	struct vnop_rename_args  /* {
		struct vnodeop_desc *a_desc;
		vnode_t a_fdvp;
		vnode_t a_fvp;
		struct componentname *a_fcnp;
		vnode_t a_tdvp;
		vnode_t a_tvp;
		struct componentname *a_tcnp;
		vfs_context_t a_context;
	} */ *ap)
{
	vfs_context_t ctx = ap->a_context;
	vnode_t fdvp = ap->a_fdvp;
	vnode_t fvp = ap->a_fvp;
	vnode_t tdvp = ap->a_tdvp;
	vnode_t tvp = ap->a_tvp;
	nfsnode_t fdnp, fnp, tdnp, tnp;
	struct componentname *tcnp = ap->a_tcnp;
	struct componentname *fcnp = ap->a_fcnp;
	int error, nfsvers, inuse=0, tvprecycle=0, locked=0;
	mount_t fmp, tdmp, tmp;
	struct nfs_vattr nvattr;
	struct nfsmount *nmp;

	fdnp = VTONFS(fdvp);
	fnp = VTONFS(fvp);
	tdnp = VTONFS(tdvp);
	tnp = tvp ? VTONFS(tvp) : NULL;

	nmp = NFSTONMP(fdnp);
	if (nfs_mount_gone(nmp))
		return (ENXIO);
	nfsvers = nmp->nm_vers;

	error = nfs_node_set_busy4(fdnp, fnp, tdnp, tnp, vfs_context_thread(ctx));
	if (error)
		return (error);

	if (tvp && (tvp != fvp)) {
		/* lock the node while we rename over the existing file */
		lck_mtx_lock(nfs_node_hash_mutex);
		while (tnp->n_hflag & NHLOCKED) {
			tnp->n_hflag |= NHLOCKWANT;
			msleep(tnp, nfs_node_hash_mutex, PINOD, "nfs_rename", NULL);
		}
		tnp->n_hflag |= NHLOCKED;
		lck_mtx_unlock(nfs_node_hash_mutex);
		locked = 1;
	}

	/* Check for cross-device rename */
	fmp = vnode_mount(fvp);
	tmp = tvp ? vnode_mount(tvp) : NULL;
	tdmp = vnode_mount(tdvp);
	if ((fmp != tdmp) || (tvp && (fmp != tmp))) {
		error = EXDEV;
		goto out;
	}

	/* XXX prevent renaming from/over a sillyrenamed file? */

	/*
	 * If the tvp exists and is in use, sillyrename it before doing the
	 * rename of the new file over it.
	 * XXX Can't sillyrename a directory.
	 * Don't sillyrename if source and target are same vnode (hard
	 * links or case-variants)
	 */
	if (tvp && (tvp != fvp))
		inuse = vnode_isinuse(tvp, 0);
	if (inuse && !tnp->n_sillyrename && (vnode_vtype(tvp) != VDIR)) {
		error = nfs_sillyrename(tdnp, tnp, tcnp, ctx);
		if (error) {
			/* sillyrename failed. Instead of pressing on, return error */
			goto out; /* should not be ENOENT. */
		} else {
			/* sillyrename succeeded.*/
			tvp = NULL;
		}
	} else if (tvp && (nmp->nm_vers >= NFS_VER4) && (tnp->n_openflags & N_DELEG_MASK)) {
		nfs4_delegation_return(tnp, 0, vfs_context_thread(ctx), vfs_context_ucred(ctx));
	}

	error = nmp->nm_funcs->nf_rename_rpc(fdnp, fcnp->cn_nameptr, fcnp->cn_namelen,
			tdnp, tcnp->cn_nameptr, tcnp->cn_namelen, ctx);

	/*
	 * Kludge: Map ENOENT => 0 assuming that it is a reply to a retry.
	 */
	if (error == ENOENT)
		error = 0;

	if (tvp && (tvp != fvp) && !tnp->n_sillyrename) {
		nfs_node_lock_force(tnp);
		tvprecycle = (!error && !vnode_isinuse(tvp, 0) &&
		    (nfs_getattrcache(tnp, &nvattr, 0) || (nvattr.nva_nlink == 1)));
		nfs_node_unlock(tnp);
		lck_mtx_lock(nfs_node_hash_mutex);
		if (tvprecycle && (tnp->n_hflag & NHHASHED)) {
			/*
			 * remove nfsnode from hash now so we can't accidentally find it
			 * again if another object gets created with the same filehandle
			 * before this vnode gets reclaimed
			 */
			LIST_REMOVE(tnp, n_hash);
			tnp->n_hflag &= ~NHHASHED;
			FSDBG(266, 0, tnp, tnp->n_flag, 0xb1eb1e);
		}
		lck_mtx_unlock(nfs_node_hash_mutex);
	}

	/* purge the old name cache entries and enter the new one */
	nfs_name_cache_purge(fdnp, fnp, fcnp, ctx);
	if (tvp) {
		nfs_name_cache_purge(tdnp, tnp, tcnp, ctx);
		if (tvprecycle) {
			/* clear flags now: won't get nfs_vnop_inactive for recycled vnode */
			/* clear all flags other than these */
			nfs_node_lock_force(tnp);
			tnp->n_flag &= (NMODIFIED);
			nfs_node_unlock(tnp);
			vnode_recycle(tvp);
		}
	}
	if (!error) {
		nfs_node_lock_force(tdnp);
		if (tdnp->n_flag & NNEGNCENTRIES) {
			tdnp->n_flag &= ~NNEGNCENTRIES;
			cache_purge_negatives(tdvp);
		}
		nfs_node_unlock(tdnp);
		nfs_node_lock_force(fnp);
		cache_enter(tdvp, fvp, tcnp);
		if (tdvp != fdvp) {	/* update parent pointer */
			if (fnp->n_parent && !vnode_get(fnp->n_parent)) {
				/* remove ref from old parent */
				vnode_rele(fnp->n_parent);
				vnode_put(fnp->n_parent);
			}
			fnp->n_parent = tdvp;
			if (tdvp && !vnode_get(tdvp)) {
				/* add ref to new parent */
				vnode_ref(tdvp);
				vnode_put(tdvp);
			} else {
				fnp->n_parent = NULL;
			}
		}
		nfs_node_unlock(fnp);
	}
out:
	/* nfs_getattr() will check changed and purge caches */
	nfs_getattr(fdnp, NULL, ctx, NGA_CACHED);
	nfs_getattr(tdnp, NULL, ctx, NGA_CACHED);
	if (locked) {
		/* unlock node */
		lck_mtx_lock(nfs_node_hash_mutex);
		tnp->n_hflag &= ~NHLOCKED;
		if (tnp->n_hflag & NHLOCKWANT) {
			tnp->n_hflag &= ~NHLOCKWANT;
			wakeup(tnp);
		}
		lck_mtx_unlock(nfs_node_hash_mutex);
	}
	nfs_node_clear_busy4(fdnp, fnp, tdnp, tnp);
	return (error);
}