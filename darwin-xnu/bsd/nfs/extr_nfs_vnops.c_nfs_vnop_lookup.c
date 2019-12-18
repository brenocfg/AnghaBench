#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int /*<<< orphan*/  u_int64_t ;
struct vnop_lookup_args {scalar_t__* a_vpp; scalar_t__ a_dvp; struct componentname* a_cnp; int /*<<< orphan*/  a_context; } ;
struct vnop_access_args {int /*<<< orphan*/  a_context; int /*<<< orphan*/  a_action; scalar_t__ a_vp; int /*<<< orphan*/ * a_desc; } ;
struct nfsreq {int /*<<< orphan*/  r_auth; } ;
struct TYPE_24__ {scalar_t__ nfsa_maxname; int /*<<< orphan*/  nfsa_bitmap; } ;
struct nfsmount {int nm_vers; TYPE_3__* nm_funcs; TYPE_2__ nm_fsattr; } ;
struct nfs_vattr {int dummy; } ;
struct componentname {int cn_flags; char* cn_nameptr; int cn_namelen; int cn_nameiop; } ;
typedef  TYPE_4__* nfsnode_t ;
typedef  scalar_t__ mount_t ;
struct TYPE_27__ {scalar_t__ fh_len; int /*<<< orphan*/  fh_data; } ;
typedef  TYPE_5__ fhandle_t ;
struct TYPE_28__ {int /*<<< orphan*/  lookupcache_misses; int /*<<< orphan*/  lookupcache_hits; } ;
struct TYPE_23__ {int nva_flags; } ;
struct TYPE_26__ {int /*<<< orphan*/  n_flag; int /*<<< orphan*/  n_xid; TYPE_1__ n_vattr; } ;
struct TYPE_25__ {int (* nf_lookup_rpc_async ) (TYPE_4__*,char*,int,int /*<<< orphan*/ ,struct nfsreq**) ;int (* nf_lookup_rpc_async_finish ) (TYPE_4__*,char*,int,int /*<<< orphan*/ ,struct nfsreq*,int /*<<< orphan*/ *,TYPE_5__*,struct nfs_vattr*) ;} ;

/* Variables and functions */
 int CREATE ; 
#define  DELETE 130 
 int EISDIR ; 
 int EJUSTRETURN ; 
 int ENAMETOOLONG ; 
#define  ENOENT 129 
 int ENXIO ; 
 int EROFS ; 
 int ISLASTCN ; 
 int /*<<< orphan*/  KAUTH_VNODE_SEARCH ; 
 int MAKEENTRY ; 
 scalar_t__ NFSTOV (TYPE_4__*) ; 
 scalar_t__ NFS_BITMAP_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NFS_CMPFH (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  NFS_FATTR_MAXNAME ; 
 int NFS_FFLAG_TRIGGER ; 
 int NFS_VER2 ; 
 int NFS_VER4 ; 
 int /*<<< orphan*/  NGA_CACHED ; 
 int NG_MAKEENTRY ; 
 scalar_t__ NMFLAG (struct nfsmount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NNEGNCENTRIES ; 
 int /*<<< orphan*/  NONEGNAMECACHE ; 
 scalar_t__ NULLVP ; 
 int /*<<< orphan*/  NVATTR_CLEANUP (struct nfs_vattr*) ; 
 int /*<<< orphan*/  NVATTR_INIT (struct nfs_vattr*) ; 
 int /*<<< orphan*/  OSAddAtomic64 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RDIRPLUS ; 
#define  RENAME 128 
 struct nfsmount* VFSTONFS (scalar_t__) ; 
 TYPE_4__* VTONFS (scalar_t__) ; 
 struct nfsmount* VTONMP (scalar_t__) ; 
 int /*<<< orphan*/  cache_enter (scalar_t__,int /*<<< orphan*/ *,struct componentname*) ; 
 int cache_lookup (scalar_t__,scalar_t__*,struct componentname*) ; 
 int nfs_dir_buf_cache_lookup (TYPE_4__*,TYPE_4__**,struct componentname*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfs_getattr (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_loadattrcache (TYPE_4__*,struct nfs_vattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 
 int nfs_nget (scalar_t__,TYPE_4__*,struct componentname*,int /*<<< orphan*/ ,scalar_t__,struct nfs_vattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,TYPE_4__**) ; 
 int /*<<< orphan*/  nfs_node_clear_busy (TYPE_4__*) ; 
 int /*<<< orphan*/  nfs_node_lock_force (TYPE_4__*) ; 
 int nfs_node_set_busy (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_node_unlock (TYPE_4__*) ; 
 int nfs_vnop_access (struct vnop_access_args*) ; 
 int /*<<< orphan*/  nfsmout_if (int) ; 
 TYPE_9__ nfsstats ; 
 int stub1 (TYPE_4__*,char*,int,int /*<<< orphan*/ ,struct nfsreq**) ; 
 int stub2 (TYPE_4__*,char*,int,int /*<<< orphan*/ ,struct nfsreq*,int /*<<< orphan*/ *,TYPE_5__*,struct nfs_vattr*) ; 
 int /*<<< orphan*/  vfs_context_thread (int /*<<< orphan*/ ) ; 
 int vnode_get (scalar_t__) ; 
 scalar_t__ vnode_getparent (scalar_t__) ; 
 scalar_t__ vnode_mount (scalar_t__) ; 
 int /*<<< orphan*/  vnode_put (scalar_t__) ; 
 scalar_t__ vnode_vfsisrdonly (scalar_t__) ; 
 int /*<<< orphan*/  vnop_access_desc ; 

int
nfs_vnop_lookup(
	struct vnop_lookup_args /* {
		struct vnodeop_desc *a_desc;
		vnode_t a_dvp;
		vnode_t *a_vpp;
		struct componentname *a_cnp;
		vfs_context_t a_context;
	} */ *ap)
{
	vfs_context_t ctx = ap->a_context;
	struct componentname *cnp = ap->a_cnp;
	vnode_t dvp = ap->a_dvp;
	vnode_t *vpp = ap->a_vpp;
	int flags = cnp->cn_flags;
	vnode_t newvp;
	nfsnode_t dnp, np;
	struct nfsmount *nmp;
	mount_t mp;
	int nfsvers, error, busyerror = ENOENT, isdot, isdotdot, negnamecache;
	u_int64_t xid;
	struct nfs_vattr nvattr;
	int ngflags;
	struct vnop_access_args naa;
	fhandle_t fh;
	struct nfsreq rq, *req = &rq;

	*vpp = NULLVP;

	dnp = VTONFS(dvp);
	NVATTR_INIT(&nvattr);

	mp = vnode_mount(dvp);
	nmp = VFSTONFS(mp);
	if (nfs_mount_gone(nmp)) {
		error = ENXIO;
		goto error_return;
	}
	nfsvers = nmp->nm_vers;
	negnamecache = !NMFLAG(nmp, NONEGNAMECACHE);

	if ((error = busyerror = nfs_node_set_busy(dnp, vfs_context_thread(ctx))))
		goto error_return;
	/* nfs_getattr() will check changed and purge caches */
	if ((error = nfs_getattr(dnp, NULL, ctx, NGA_CACHED)))
		goto error_return;

	error = cache_lookup(dvp, vpp, cnp);
	switch (error) {
	case ENOENT:
		/* negative cache entry */
		goto error_return;
	case 0:
		/* cache miss */
		if ((nfsvers > NFS_VER2) && NMFLAG(nmp, RDIRPLUS)) {
			/* if rdirplus, try dir buf cache lookup */
			error = nfs_dir_buf_cache_lookup(dnp, &np, cnp, ctx, 0);
			if (!error && np) {
				/* dir buf cache hit */
				*vpp = NFSTOV(np);
				error = -1;
			}
		}
		if (error != -1) /* cache miss */
			break;
		/* FALLTHROUGH */
	case -1:
		/* cache hit, not really an error */
		OSAddAtomic64(1, &nfsstats.lookupcache_hits);

		nfs_node_clear_busy(dnp);
		busyerror = ENOENT;

		/* check for directory access */
		naa.a_desc = &vnop_access_desc;
		naa.a_vp = dvp;
		naa.a_action = KAUTH_VNODE_SEARCH;
		naa.a_context = ctx;

		/* compute actual success/failure based on accessibility */
		error = nfs_vnop_access(&naa);
		/* FALLTHROUGH */
	default:
		/* unexpected error from cache_lookup */
		goto error_return;
	}

	/* skip lookup, if we know who we are: "." or ".." */
	isdot = isdotdot = 0;
	if (cnp->cn_nameptr[0] == '.') {
		if (cnp->cn_namelen == 1)
			isdot = 1;
		if ((cnp->cn_namelen == 2) && (cnp->cn_nameptr[1] == '.'))
			isdotdot = 1;
	}
	if (isdotdot || isdot) {
		fh.fh_len = 0;
		goto found;
	}
	if ((nfsvers >= NFS_VER4) && (dnp->n_vattr.nva_flags & NFS_FFLAG_TRIGGER)) {
		/* we should never be looking things up in a trigger directory, return nothing */
		error = ENOENT;
		goto error_return;
	}

	/* do we know this name is too long? */
	nmp = VTONMP(dvp);
	if (nfs_mount_gone(nmp)) {
		error = ENXIO;
		goto error_return;
	}
	if (NFS_BITMAP_ISSET(nmp->nm_fsattr.nfsa_bitmap, NFS_FATTR_MAXNAME) &&
	     (cnp->cn_namelen > (int)nmp->nm_fsattr.nfsa_maxname)) {
		error = ENAMETOOLONG;
		goto error_return;
	}

	error = 0;
	newvp = NULLVP;

	OSAddAtomic64(1, &nfsstats.lookupcache_misses);

	error = nmp->nm_funcs->nf_lookup_rpc_async(dnp, cnp->cn_nameptr, cnp->cn_namelen, ctx, &req);
	nfsmout_if(error);
	error = nmp->nm_funcs->nf_lookup_rpc_async_finish(dnp, cnp->cn_nameptr, cnp->cn_namelen, ctx, req, &xid, &fh, &nvattr);
	nfsmout_if(error);

	/* is the file handle the same as this directory's file handle? */
	isdot = NFS_CMPFH(dnp, fh.fh_data, fh.fh_len);

found:
	if (flags & ISLASTCN) {
		switch (cnp->cn_nameiop) {
		case DELETE:
			cnp->cn_flags &= ~MAKEENTRY;
			break;
		case RENAME:
			cnp->cn_flags &= ~MAKEENTRY;
			if (isdot) {
				error = EISDIR;
				goto error_return;
			}
			break;
		}
	}

	if (isdotdot) {
		newvp = vnode_getparent(dvp);
		if (!newvp) {
			error = ENOENT;
			goto error_return;
		}
	} else if (isdot) {
		error = vnode_get(dvp);
		if (error)
			goto error_return;
		newvp = dvp;
		nfs_node_lock_force(dnp);
		if (fh.fh_len && (dnp->n_xid <= xid))
			nfs_loadattrcache(dnp, &nvattr, &xid, 0);
		nfs_node_unlock(dnp);
	} else {
		ngflags = (cnp->cn_flags & MAKEENTRY) ? NG_MAKEENTRY : 0;
		error = nfs_nget(mp, dnp, cnp, fh.fh_data, fh.fh_len, &nvattr, &xid, rq.r_auth, ngflags, &np);
		if (error)
			goto error_return;
		newvp = NFSTOV(np);
		nfs_node_unlock(np);
	}
	*vpp = newvp;

nfsmout:
	if (error) {
		if (((cnp->cn_nameiop == CREATE) || (cnp->cn_nameiop == RENAME)) &&
		    (flags & ISLASTCN) && (error == ENOENT)) {
			if (vnode_mount(dvp) && vnode_vfsisrdonly(dvp))
				error = EROFS;
			else
				error = EJUSTRETURN;
		}
	}
	if ((error == ENOENT) && (cnp->cn_flags & MAKEENTRY) &&
	    (cnp->cn_nameiop != CREATE) && negnamecache) {
		/* add a negative entry in the name cache */
		nfs_node_lock_force(dnp);
		cache_enter(dvp, NULL, cnp);
		dnp->n_flag |= NNEGNCENTRIES;
		nfs_node_unlock(dnp);
	}
error_return:
	NVATTR_CLEANUP(&nvattr);
	if (!busyerror)
		nfs_node_clear_busy(dnp);
	if (error && *vpp) {
	        vnode_put(*vpp);
		*vpp = NULLVP;
	}
	return (error);
}