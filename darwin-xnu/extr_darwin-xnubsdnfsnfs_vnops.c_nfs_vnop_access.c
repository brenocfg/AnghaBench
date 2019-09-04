#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int /*<<< orphan*/  uid_t ;
typedef  int u_int32_t ;
struct vnop_access_args {int a_action; int /*<<< orphan*/  a_vp; int /*<<< orphan*/  a_context; } ;
struct timeval {scalar_t__ tv_sec; } ;
struct nfsmount {int nm_vers; TYPE_1__* nm_funcs; int /*<<< orphan*/  nm_auth; } ;
typedef  TYPE_2__* nfsnode_t ;
struct TYPE_10__ {scalar_t__* n_accessstamp; int* n_access; int /*<<< orphan*/  n_auth; } ;
struct TYPE_9__ {int (* nf_access_rpc ) (TYPE_2__*,int*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EACCES ; 
 int ENXIO ; 
 int EROFS ; 
 int ETIMEDOUT ; 
 int KAUTH_VNODE_ADD_FILE ; 
 int KAUTH_VNODE_ADD_SUBDIRECTORY ; 
 int KAUTH_VNODE_APPEND_DATA ; 
 int KAUTH_VNODE_CHANGE_OWNER ; 
 int KAUTH_VNODE_DELETE ; 
 int KAUTH_VNODE_DELETE_CHILD ; 
 int KAUTH_VNODE_EXECUTE ; 
 int KAUTH_VNODE_LIST_DIRECTORY ; 
 int KAUTH_VNODE_READ_DATA ; 
 int KAUTH_VNODE_READ_EXTATTRIBUTES ; 
 int KAUTH_VNODE_SEARCH ; 
 int KAUTH_VNODE_WRITE_ATTRIBUTES ; 
 int KAUTH_VNODE_WRITE_DATA ; 
 int KAUTH_VNODE_WRITE_EXTATTRIBUTES ; 
 int KAUTH_VNODE_WRITE_RIGHTS ; 
 int KAUTH_VNODE_WRITE_SECURITY ; 
 scalar_t__ NACCESSVALID (TYPE_2__*,int) ; 
 int NFS_ACCESS_DELETE ; 
 int NFS_ACCESS_EXECUTE ; 
 int NFS_ACCESS_EXTEND ; 
 int NFS_ACCESS_LOOKUP ; 
 int NFS_ACCESS_MODIFY ; 
 int NFS_ACCESS_READ ; 
 int NFS_VER2 ; 
 int R_SOFT ; 
 TYPE_2__* VTONFS (int /*<<< orphan*/ ) ; 
 struct nfsmount* VTONMP (int /*<<< orphan*/ ) ; 
 scalar_t__ auth_is_kerberized (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_getuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  microuptime (struct timeval*) ; 
 scalar_t__ nfs_access_cache_timeout ; 
 int /*<<< orphan*/  nfs_cred_getasid2uid (int /*<<< orphan*/ ) ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 
 int nfs_node_access_slot (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfs_node_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  nfs_node_unlock (TYPE_2__*) ; 
 scalar_t__ nfs_use_cache (struct nfsmount*) ; 
 int stub1 (TYPE_2__*,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 
 scalar_t__ vfs_isrdonly (int /*<<< orphan*/ ) ; 
 scalar_t__ vnode_isdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_mount (int /*<<< orphan*/ ) ; 

int
nfs_vnop_access(
	struct vnop_access_args /* {
		struct vnodeop_desc *a_desc;
		vnode_t a_vp;
		int a_action;
		vfs_context_t a_context;
	} */ *ap)
{
	vfs_context_t ctx = ap->a_context;
	vnode_t vp = ap->a_vp;
	int error = 0, slot, dorpc, rpcflags = 0;
	u_int32_t access, waccess;
	nfsnode_t np = VTONFS(vp);
	struct nfsmount *nmp;
	int nfsvers;
	struct timeval now;
	uid_t uid;

	nmp = VTONMP(vp);
	if (nfs_mount_gone(nmp))
		return (ENXIO);
	nfsvers = nmp->nm_vers;

	if (nfsvers == NFS_VER2) {
		if ((ap->a_action & KAUTH_VNODE_WRITE_RIGHTS) &&
		    vfs_isrdonly(vnode_mount(vp)))
			return (EROFS);
		return (0);
	}

	/*
	 * For NFS v3, do an access rpc, otherwise you are stuck emulating
	 * ufs_access() locally using the vattr. This may not be correct,
	 * since the server may apply other access criteria such as
	 * client uid-->server uid mapping that we do not know about, but
	 * this is better than just returning anything that is lying about
	 * in the cache.
	 */

	/*
	 * Convert KAUTH primitives to NFS access rights.
	 */
	access = 0;
	if (vnode_isdir(vp)) {
		/* directory */
		if (ap->a_action &
		    (KAUTH_VNODE_LIST_DIRECTORY |
		    KAUTH_VNODE_READ_EXTATTRIBUTES))
			access |= NFS_ACCESS_READ;
		if (ap->a_action & KAUTH_VNODE_SEARCH)
			access |= NFS_ACCESS_LOOKUP;
		if (ap->a_action &
		    (KAUTH_VNODE_ADD_FILE |
		    KAUTH_VNODE_ADD_SUBDIRECTORY))
			access |= NFS_ACCESS_MODIFY | NFS_ACCESS_EXTEND;
		if (ap->a_action & KAUTH_VNODE_DELETE_CHILD)
			access |= NFS_ACCESS_MODIFY;
	} else {
		/* file */
		if (ap->a_action &
		    (KAUTH_VNODE_READ_DATA |
		    KAUTH_VNODE_READ_EXTATTRIBUTES))
			access |= NFS_ACCESS_READ;
		if (ap->a_action & KAUTH_VNODE_WRITE_DATA)
			access |= NFS_ACCESS_MODIFY | NFS_ACCESS_EXTEND;
		if (ap->a_action & KAUTH_VNODE_APPEND_DATA)
			access |= NFS_ACCESS_EXTEND;
		if (ap->a_action & KAUTH_VNODE_EXECUTE)
			access |= NFS_ACCESS_EXECUTE;
	}
	/* common */
	if (ap->a_action & KAUTH_VNODE_DELETE)
		access |= NFS_ACCESS_DELETE;
	if (ap->a_action &
	    (KAUTH_VNODE_WRITE_ATTRIBUTES |
	    KAUTH_VNODE_WRITE_EXTATTRIBUTES |
	    KAUTH_VNODE_WRITE_SECURITY))
		access |= NFS_ACCESS_MODIFY;
	/* XXX this is pretty dubious */
	if (ap->a_action & KAUTH_VNODE_CHANGE_OWNER)
		access |= NFS_ACCESS_MODIFY;

	/* if caching, always ask for every right */
	if (nfs_access_cache_timeout > 0) {
		waccess = NFS_ACCESS_READ | NFS_ACCESS_MODIFY |
			NFS_ACCESS_EXTEND | NFS_ACCESS_EXECUTE |
			NFS_ACCESS_DELETE | NFS_ACCESS_LOOKUP;
	} else {
		waccess = access;
	}

	if ((error = nfs_node_lock(np)))
		return (error);

	/*
	 * Does our cached result allow us to give a definite yes to
	 * this request?
	 */
	if (auth_is_kerberized(np->n_auth) || auth_is_kerberized(nmp->nm_auth))
		uid = nfs_cred_getasid2uid(vfs_context_ucred(ctx));
	else
		uid = kauth_cred_getuid(vfs_context_ucred(ctx));
	slot = nfs_node_access_slot(np, uid, 0);
	dorpc = 1;
	if (access == 0) {
		/* not asking for any rights understood by NFS, so don't bother doing an RPC */
		/* OSAddAtomic(1, &nfsstats.accesscache_hits); */
		dorpc = 0;
		waccess = 0;
	} else if (NACCESSVALID(np, slot)) {
		microuptime(&now);
		if (((now.tv_sec < (np->n_accessstamp[slot] + nfs_access_cache_timeout)) &&
		    ((np->n_access[slot] & access) == access)) || nfs_use_cache(nmp)) {
			/* OSAddAtomic(1, &nfsstats.accesscache_hits); */
			dorpc = 0;
			waccess = np->n_access[slot];
		}
	}
	nfs_node_unlock(np);
	if (dorpc) {
		/* Either a no, or a don't know.  Go to the wire. */
		/* OSAddAtomic(1, &nfsstats.accesscache_misses); */

		/*
		 * Allow an access call to timeout if we have it cached
		 * so we won't hang if the server isn't responding.
		 */
		if (NACCESSVALID(np, slot))
			rpcflags |= R_SOFT;

		error = nmp->nm_funcs->nf_access_rpc(np, &waccess, rpcflags, ctx);

		/*
		 * If the server didn't respond return the cached access.
		 */
		if ((error == ETIMEDOUT) && (rpcflags & R_SOFT)) {
			error = 0;
			waccess = np->n_access[slot];
		}
	}
	if (!error && ((waccess & access) != access))
		error = EACCES;

	return (error);
}