#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  u_int64_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct timespec {int member_0; int /*<<< orphan*/  member_1; } ;
struct nfsmount {int nm_vers; TYPE_2__* nm_funcs; } ;
struct nfs_vattr {int /*<<< orphan*/ * nva_acl; int /*<<< orphan*/  nva_bitmap; } ;
typedef  TYPE_3__* nfsnode_t ;
typedef  enum vtype { ____Placeholder_vtype } vtype ;
struct TYPE_26__ {int /*<<< orphan*/  nva_size; } ;
struct TYPE_28__ {int n_flag; int n_openflags; int n_xid; TYPE_1__ n_vattr; int /*<<< orphan*/  n_size; int /*<<< orphan*/  n_ncgen; int /*<<< orphan*/  n_fhsize; int /*<<< orphan*/  n_fhp; int /*<<< orphan*/  n_lock; } ;
struct TYPE_27__ {int (* nf_access_rpc ) (TYPE_3__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ;int (* nf_getattr_rpc ) (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct nfs_vattr*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CLR (int,int) ; 
 int EINPROGRESS ; 
 int ENOENT ; 
 int ENXIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  FSDBG (int,int,TYPE_3__*,int,...) ; 
 int /*<<< orphan*/  FSDBG_BOT (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FSDBG_TOP (int,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int ISSET (int,int) ; 
 int NACC ; 
 scalar_t__ NATTRVALID (TYPE_3__*) ; 
 int NCHG ; 
 struct nfsmount* NFSTONMP (TYPE_3__*) ; 
 int /*<<< orphan*/  NFSTOV (TYPE_3__*) ; 
 int /*<<< orphan*/  NFS_ACCESS_ALL ; 
 int /*<<< orphan*/  NFS_BITMAP_CLR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NFS_CHANGED (int,TYPE_3__*,struct nfs_vattr*) ; 
 scalar_t__ NFS_CHANGED_NC (int,TYPE_3__*,struct nfs_vattr*) ; 
 int /*<<< orphan*/  NFS_CHANGED_UPDATE (int,TYPE_3__*,struct nfs_vattr*) ; 
 int /*<<< orphan*/  NFS_CHANGED_UPDATE_NC (int,TYPE_3__*,struct nfs_vattr*) ; 
 int /*<<< orphan*/  NFS_FATTR_ACL ; 
 int NFS_VER2 ; 
 int NFS_VER4 ; 
 int /*<<< orphan*/  NFS_VNOP_DBG (char*,int /*<<< orphan*/ ) ; 
 int NGA_ACL ; 
 int NGA_MONITOR ; 
 int NGA_SOFT ; 
 int NGA_UNCACHED ; 
 int NGETATTRINPROG ; 
 int NGETATTRWANT ; 
 int NNEGNCENTRIES ; 
 int NUPD ; 
 int NUPDATESIZE ; 
 int /*<<< orphan*/  NVATTR_CLEANUP (struct nfs_vattr*) ; 
 int /*<<< orphan*/  NVATTR_INIT (struct nfs_vattr*) ; 
 int N_DELEG_MASK ; 
 scalar_t__ PZERO ; 
 int R_SOFT ; 
 int /*<<< orphan*/  SET (int,int) ; 
 int VDIR ; 
 scalar_t__ VM_KERNEL_ADDRPERM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_SAVE ; 
 int /*<<< orphan*/  cache_purge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_acl_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (TYPE_3__*,int /*<<< orphan*/ *,scalar_t__,char*,struct timespec*) ; 
 scalar_t__ nfs_access_cache_timeout ; 
 scalar_t__ nfs_access_for_getattr ; 
 scalar_t__ nfs_attrcachetimeout (TYPE_3__*) ; 
 int /*<<< orphan*/  nfs_data_update_size (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int nfs_getattrcache (TYPE_3__*,struct nfs_vattr*,int) ; 
 int /*<<< orphan*/  nfs_invaldir (TYPE_3__*) ; 
 int nfs_loadattrcache (TYPE_3__*,struct nfs_vattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 
 int nfs_node_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  nfs_node_lock_force (TYPE_3__*) ; 
 int /*<<< orphan*/  nfs_node_unlock (TYPE_3__*) ; 
 int nfs_sigintr (struct nfsmount*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nfs_use_cache (struct nfsmount*) ; 
 int nfs_vinvalbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfsmout_if (int) ; 
 int stub1 (TYPE_3__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int stub2 (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct nfs_vattr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfs_context_thread (int /*<<< orphan*/ ) ; 
 int vnode_vtype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (TYPE_3__*) ; 

int
nfs_getattr_internal(nfsnode_t np, struct nfs_vattr *nvap, vfs_context_t ctx, int flags)
{
	struct nfsmount *nmp;
	int error = 0, nfsvers, inprogset = 0, wanted = 0, avoidfloods;
	struct nfs_vattr nvattr;
	struct timespec ts = { 2, 0 };
	u_int64_t xid;

	FSDBG_TOP(513, np->n_size, np, np->n_vattr.nva_size, np->n_flag);

	nmp = NFSTONMP(np);
	
	if (nfs_mount_gone(nmp))
		return (ENXIO);
	nfsvers = nmp->nm_vers;

	if (!nvap)
		nvap = &nvattr;
	NVATTR_INIT(nvap);

	/* Update local times for special files. */
	if (np->n_flag & (NACC | NUPD)) {
		nfs_node_lock_force(np);
		np->n_flag |= NCHG;
		nfs_node_unlock(np);
	}
	/* Update size, if necessary */
	if (ISSET(np->n_flag, NUPDATESIZE))
		nfs_data_update_size(np, 0);

	error = nfs_node_lock(np);
	nfsmout_if(error);
	if (!(flags & (NGA_UNCACHED|NGA_MONITOR)) || ((nfsvers >= NFS_VER4) && (np->n_openflags & N_DELEG_MASK))) {
		/*
		 * Use the cache or wait for any getattr in progress if:
		 * - it's a cached request, or
		 * - we have a delegation, or
		 * - the server isn't responding
		 */
		while (1) {
			error = nfs_getattrcache(np, nvap, flags);
			if (!error || (error != ENOENT)) {
				nfs_node_unlock(np);
				goto nfsmout;
			}
			error = 0;
			if (!ISSET(np->n_flag, NGETATTRINPROG))
				break;
			if (flags & NGA_MONITOR) {
				/* no need to wait if a request is pending */
				error = EINPROGRESS;
				nfs_node_unlock(np);
				goto nfsmout;
			}
			SET(np->n_flag, NGETATTRWANT);
			msleep(np, &np->n_lock, PZERO-1, "nfsgetattrwant", &ts);
			if ((error = nfs_sigintr(NFSTONMP(np), NULL, vfs_context_thread(ctx), 0))) {
				nfs_node_unlock(np);
				goto nfsmout;
			}
		}
		SET(np->n_flag, NGETATTRINPROG);
		inprogset = 1;
	} else if (!ISSET(np->n_flag, NGETATTRINPROG)) {
		SET(np->n_flag, NGETATTRINPROG);
		inprogset = 1;
	} else if (flags & NGA_MONITOR) {
		/* no need to make a request if one is pending */
		error = EINPROGRESS;
	}
	nfs_node_unlock(np);

	nmp = NFSTONMP(np);
	if (nfs_mount_gone(nmp))
		error = ENXIO;
	if (error)
		goto nfsmout;

	/*
	 * Return cached attributes if they are valid,
	 * if the server doesn't respond, and this is
	 * some softened up style of mount.
	 */
	if (NATTRVALID(np) && nfs_use_cache(nmp))
		flags |= NGA_SOFT;

	/*
	 * We might want to try to get both the attributes and access info by
	 * making an ACCESS call and seeing if it returns updated attributes.
	 * But don't bother if we aren't caching access info or if the
	 * attributes returned wouldn't be cached.
	 */
	if (!(flags & NGA_ACL) && (nfsvers != NFS_VER2) && nfs_access_for_getattr && (nfs_access_cache_timeout > 0)) {
		if (nfs_attrcachetimeout(np) > 0) {
			/*  OSAddAtomic(1, &nfsstats.accesscache_misses); */
			u_int32_t access = NFS_ACCESS_ALL;
			int rpcflags = 0;

			/* Return cached attrs if server doesn't respond */
			if (flags & NGA_SOFT)
				rpcflags |= R_SOFT;

			error = nmp->nm_funcs->nf_access_rpc(np, &access, rpcflags, ctx);

			if (error == ETIMEDOUT)
				goto returncached;

			if (error)
				goto nfsmout;
			nfs_node_lock_force(np);
			error = nfs_getattrcache(np, nvap, flags);
			nfs_node_unlock(np);
			if (!error || (error != ENOENT))
				goto nfsmout;
			/* Well, that didn't work... just do a getattr... */
			error = 0;
		}
	}

	avoidfloods = 0;

tryagain:
	error = nmp->nm_funcs->nf_getattr_rpc(np, NULL, np->n_fhp, np->n_fhsize, flags, ctx, nvap, &xid);
	if (!error) {
		nfs_node_lock_force(np);
		error = nfs_loadattrcache(np, nvap, &xid, 0);
		nfs_node_unlock(np);
	}

	/*
	 * If the server didn't respond, return cached attributes.
	 */
returncached:
	if ((flags & NGA_SOFT) && (error == ETIMEDOUT)) {
		nfs_node_lock_force(np);
		error = nfs_getattrcache(np, nvap, flags);
		if (!error || (error != ENOENT)) {
			nfs_node_unlock(np);
			goto nfsmout;
		}
		nfs_node_unlock(np);
	}
	nfsmout_if(error);

	if (!xid) { /* out-of-order rpc - attributes were dropped */
		FSDBG(513, -1, np, np->n_xid >> 32, np->n_xid);
		if (avoidfloods++ < 20)
			goto tryagain;
		/* avoidfloods>1 is bizarre.  at 20 pull the plug */
		/* just return the last attributes we got */
	}
nfsmout:
	nfs_node_lock_force(np);
	if (inprogset) {
		wanted = ISSET(np->n_flag, NGETATTRWANT);
		CLR(np->n_flag, (NGETATTRINPROG | NGETATTRWANT));
	}
	if (!error) {
		/* check if the node changed on us */
		vnode_t vp = NFSTOV(np);
		enum vtype vtype = vnode_vtype(vp);
		if ((vtype == VDIR) && NFS_CHANGED_NC(nfsvers, np, nvap)) {
			FSDBG(513, -1, np, 0, np);
			np->n_flag &= ~NNEGNCENTRIES;
			cache_purge(vp);
			np->n_ncgen++;
			NFS_CHANGED_UPDATE_NC(nfsvers, np, nvap);
			NFS_VNOP_DBG("Purge directory 0x%llx\n", 
			      (uint64_t)VM_KERNEL_ADDRPERM(vp));
		}
		if (NFS_CHANGED(nfsvers, np, nvap)) {
			FSDBG(513, -1, np, -1, np);
			if (vtype == VDIR) {
				NFS_VNOP_DBG("Invalidate directory 0x%llx\n", 
			               (uint64_t)VM_KERNEL_ADDRPERM(vp));
				nfs_invaldir(np);
			}
			nfs_node_unlock(np);
			if (wanted)
				wakeup(np);
			error = nfs_vinvalbuf(vp, V_SAVE, ctx, 1);
			FSDBG(513, -1, np, -2, error);
			if (!error) {
				nfs_node_lock_force(np);
				NFS_CHANGED_UPDATE(nfsvers, np, nvap);
				nfs_node_unlock(np);
			}
		} else {
			nfs_node_unlock(np);
			if (wanted)
				wakeup(np);
		}
	} else {
		nfs_node_unlock(np);
		if (wanted)
			wakeup(np);
	}

	if (nvap == &nvattr) {
		NVATTR_CLEANUP(nvap);
	} else if (!(flags & NGA_ACL)) {
		/* make sure we don't return an ACL if it wasn't asked for */
		NFS_BITMAP_CLR(nvap->nva_bitmap, NFS_FATTR_ACL);
		if (nvap->nva_acl) {
			kauth_acl_free(nvap->nva_acl);
			nvap->nva_acl = NULL;
		}
	}
	FSDBG_BOT(513, np->n_size, error, np->n_vattr.nva_size, np->n_flag);
	return (error);
}