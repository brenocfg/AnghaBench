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
typedef  TYPE_2__* vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
struct componentname {int cn_flags; char* cn_nameptr; scalar_t__ cn_consume; int /*<<< orphan*/  cn_context; } ;
struct nameidata {int ni_flag; int ni_ncgeneration; char* ni_next; TYPE_2__* ni_vp; TYPE_2__* ni_dvp; TYPE_2__* ni_startdir; TYPE_2__* ni_rootdir; struct componentname ni_cnd; } ;
struct TYPE_20__ {int v_nc_generation; int v_flag; scalar_t__ v_type; TYPE_1__* v_mount; } ;
struct TYPE_19__ {int mnt_flag; TYPE_2__* mnt_vnodecovered; } ;

/* Variables and functions */
 int CN_NBMOUNTLOOK ; 
 int DONOTAUTH ; 
 int EBADF ; 
 int EJUSTRETURN ; 
 int ENOENT ; 
 int ENOTDIR ; 
 int FALSE ; 
 int FOLLOW ; 
 int ISDOTDOT ; 
 int ISLASTCN ; 
 int ISSYMLINK ; 
 int LK_NOWAIT ; 
 int LOCKPARENT ; 
 int MAKEENTRY ; 
 int MNT_UNION ; 
 int NAMEI_TRAILINGSLASH ; 
 int NAMEI_UNFINISHED ; 
 int NOCACHE ; 
 int NOCROSSMOUNT ; 
 TYPE_2__* NULLVP ; 
 int RDONLY ; 
 int SAVESTART ; 
 scalar_t__ VDIR ; 
 scalar_t__ VLNK ; 
 int VNOP_LOOKUP (TYPE_2__*,TYPE_2__**,struct componentname*,int /*<<< orphan*/ ) ; 
 int VROOT ; 
 int WANTPARENT ; 
 int cache_lookup_path (struct nameidata*,struct componentname*,TYPE_2__*,int /*<<< orphan*/ ,int*,TYPE_2__*) ; 
 scalar_t__ kdebug_enable ; 
 int /*<<< orphan*/  kdebug_lookup (TYPE_2__*,struct componentname*) ; 
 int lookup_authorize_search (TYPE_2__*,struct componentname*,int,int /*<<< orphan*/ ) ; 
 int lookup_handle_emptyname (struct nameidata*,struct componentname*,int) ; 
 int lookup_handle_found_vnode (struct nameidata*,struct componentname*,int,int,int*,int,int,int,int /*<<< orphan*/ ) ; 
 int lookup_traverse_union (TYPE_2__*,TYPE_2__**,int /*<<< orphan*/ ) ; 
 int lookup_validate_creation_path (struct nameidata*) ; 
 scalar_t__ namei_compound_available (TYPE_2__*,struct nameidata*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 TYPE_2__* rootvnode ; 
 int /*<<< orphan*/  vfs_context_kernel () ; 
 scalar_t__ vnode_get (TYPE_2__*) ; 
 scalar_t__ vnode_getwithref (TYPE_2__*) ; 
 int vnode_issubdir (TYPE_2__*,TYPE_2__*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_put (TYPE_2__*) ; 

int
lookup(struct nameidata *ndp)
{
	char	*cp;		/* pointer into pathname argument */
	vnode_t		tdp;		/* saved dp */
	vnode_t		dp;		/* the directory we are searching */
	int docache = 1;		/* == 0 do not cache last component */
	int wantparent;			/* 1 => wantparent or lockparent flag */
	int rdonly;			/* lookup read-only flag bit */
	int dp_authorized = 0;
	int error = 0;
	struct componentname *cnp = &ndp->ni_cnd;
	vfs_context_t ctx = cnp->cn_context;
	int vbusyflags = 0;
	int nc_generation = 0;
	vnode_t last_dp = NULLVP;
	int keep_going;
	int atroot;

	/*
	 * Setup: break out flag bits into variables.
	 */
	if (cnp->cn_flags & NOCACHE) {
	        docache = 0;
	}
	wantparent = cnp->cn_flags & (LOCKPARENT | WANTPARENT);
	rdonly = cnp->cn_flags & RDONLY;
	cnp->cn_flags &= ~ISSYMLINK;
	cnp->cn_consume = 0;

	dp = ndp->ni_startdir;
	ndp->ni_startdir = NULLVP;

	if ((cnp->cn_flags & CN_NBMOUNTLOOK) != 0)
			vbusyflags = LK_NOWAIT;
	cp = cnp->cn_nameptr;

	if (*cp == '\0') {
	        if ( (vnode_getwithref(dp)) ) {
			dp = NULLVP;
		        error = ENOENT;
			goto bad;
		}
		ndp->ni_vp = dp;
		error = lookup_handle_emptyname(ndp, cnp, wantparent);
		if (error) {
			goto bad;
		}

		return 0;
	}
dirloop: 
	atroot = 0;
	ndp->ni_vp = NULLVP;

	if ( (error = cache_lookup_path(ndp, cnp, dp, ctx, &dp_authorized, last_dp)) ) {
		dp = NULLVP;
		goto bad;
	}
	if ((cnp->cn_flags & ISLASTCN)) {
	        if (docache)
		        cnp->cn_flags |= MAKEENTRY;
	} else
	        cnp->cn_flags |= MAKEENTRY;

	dp = ndp->ni_dvp;

	if (ndp->ni_vp != NULLVP) {
	        /*
		 * cache_lookup_path returned a non-NULL ni_vp then,
		 * we're guaranteed that the dp is a VDIR, it's 
		 * been authorized, and vp is not ".."
		 *
		 * make sure we don't try to enter the name back into
		 * the cache if this vp is purged before we get to that
		 * check since we won't have serialized behind whatever
		 * activity is occurring in the FS that caused the purge
		 */
	        if (dp != NULLVP)
		        nc_generation = dp->v_nc_generation - 1;

	        goto returned_from_lookup_path;
	}

	/*
	 * Handle "..": two special cases.
	 * 1. If at root directory (e.g. after chroot)
	 *    or at absolute root directory
	 *    then ignore it so can't get out.
	 * 2. If this vnode is the root of a mounted
	 *    filesystem, then replace it with the
	 *    vnode which was mounted on so we take the
	 *    .. in the other file system.
	 */
	if ( (cnp->cn_flags & ISDOTDOT) ) {
		/*
		 * if this is a chroot'ed process, check if the current
		 * directory is still a subdirectory of the process's
		 * root directory.
		 */
		if (ndp->ni_rootdir && (ndp->ni_rootdir != rootvnode) &&
		    dp !=  ndp->ni_rootdir) {
			int sdir_error;
			int is_subdir = FALSE;

			sdir_error = vnode_issubdir(dp, ndp->ni_rootdir,
			    &is_subdir, vfs_context_kernel());

			/*
			 * If we couldn't determine if dp is a subdirectory of
			 * ndp->ni_rootdir (sdir_error != 0), we let the request
			 * proceed.
			 */
			if (!sdir_error && !is_subdir) {
				vnode_put(dp);
				dp = ndp->ni_rootdir;
				/*
				 * There's a ref on the process's root directory
				 * but we can't use vnode_getwithref here as
				 * there is nothing preventing that ref being
				 * released by another thread.
				 */
				if (vnode_get(dp)) {
					error = ENOENT;
					goto bad;
				}
			}
		}

		for (;;) {
		        if (dp == ndp->ni_rootdir || dp == rootvnode) {
			        ndp->ni_dvp = dp;
				ndp->ni_vp = dp;
				/*
				 * we're pinned at the root
				 * we've already got one reference on 'dp'
				 * courtesy of cache_lookup_path... take
				 * another one for the ".."
				 * if we fail to get the new reference, we'll
				 * drop our original down in 'bad'
				 */
				if ( (vnode_get(dp)) ) {
					error = ENOENT;
					goto bad;
				}
				atroot = 1;
				goto returned_from_lookup_path;
			}
			if ((dp->v_flag & VROOT) == 0 ||
			    (cnp->cn_flags & NOCROSSMOUNT))
			        break;
			if (dp->v_mount == NULL) {	/* forced umount */
			        error = EBADF;
				goto bad;
			}
			tdp = dp;
			dp = tdp->v_mount->mnt_vnodecovered;

			vnode_put(tdp);

			if ( (vnode_getwithref(dp)) ) {
			        dp = NULLVP;
				error = ENOENT;
				goto bad;
			}
			ndp->ni_dvp = dp;
			dp_authorized = 0;
		}
	}

	/*
	 * We now have a segment name to search for, and a directory to search.
	 */
unionlookup:
	ndp->ni_vp = NULLVP;

	if (dp->v_type != VDIR) {
	        error = ENOTDIR;
	        goto lookup_error;
	}
	if ( (cnp->cn_flags & DONOTAUTH) != DONOTAUTH ) {
		error = lookup_authorize_search(dp, cnp, dp_authorized, ctx);
		if (error) {
			goto lookup_error;
		}
	}

	/*
	 * Now that we've authorized a lookup, can bail out if the filesystem
	 * will be doing a batched operation.  Return an iocount on dvp.
	 */
#if NAMEDRSRCFORK
	if ((cnp->cn_flags & ISLASTCN) && namei_compound_available(dp, ndp) && !(cnp->cn_flags & CN_WANTSRSRCFORK)) { 
#else 
	if ((cnp->cn_flags & ISLASTCN) && namei_compound_available(dp, ndp)) {
#endif /* NAMEDRSRCFORK */
		ndp->ni_flag |= NAMEI_UNFINISHED;
		ndp->ni_ncgeneration = dp->v_nc_generation;
		return 0;
	}

        nc_generation = dp->v_nc_generation;

	/*
	 * Note: 
	 * Filesystems that support hardlinks may want to call vnode_update_identity
	 * if the lookup operation below will modify the in-core vnode to belong to a new point
	 * in the namespace.  VFS cannot infer whether or not the look up operation makes the vnode
	 * name change or change parents.  Without this, the lookup may make update
	 * filesystem-specific in-core metadata but fail to update the v_parent or v_name
	 * fields in the vnode.  If VFS were to do this, it would be necessary to call
	 * vnode_update_identity on every lookup operation -- expensive!
	 *
	 * However, even with this in place, multiple lookups may occur in between this lookup
	 * and the subsequent vnop, so, at best, we could only guarantee that you would get a
	 * valid path back, and not necessarily the one that you wanted. 
	 *
	 * Example: 
	 * /tmp/a == /foo/b
	 * 
	 * If you are now looking up /foo/b and the vnode for this link represents /tmp/a, 
	 * vnode_update_identity will fix the parentage so that you can get /foo/b back 
	 * through the v_parent chain (preventing you from getting /tmp/b back). It would 
	 * not fix whether or not you should or should not get /tmp/a vs. /foo/b.
	 */

	error = VNOP_LOOKUP(dp, &ndp->ni_vp, cnp, ctx);

	if ( error ) {
lookup_error:
		if ((error == ENOENT) &&
		    (dp->v_mount != NULL) &&
		    (dp->v_mount->mnt_flag & MNT_UNION)) {
			tdp = dp;
			error = lookup_traverse_union(tdp, &dp, ctx);
			vnode_put(tdp);
			if (error) {
			        dp = NULLVP;
				goto bad;
			}

			ndp->ni_dvp = dp;
			dp_authorized = 0;
			goto unionlookup;
		}

		if (error != EJUSTRETURN)
			goto bad;

		if (ndp->ni_vp != NULLVP)
			panic("leaf should be empty");

#if NAMEDRSRCFORK
		/* 
		 * At this point, error should be EJUSTRETURN.
		 * 
		 * If CN_WANTSRSRCFORK is set, that implies that the 
		 * underlying filesystem could not find the "parent" of the
		 * resource fork (the data fork), and we are doing a lookup 
		 * for a CREATE event.
		 *
		 * However, this should be converted to an error, as the
		 * failure to find this parent should disallow further
		 * progress to try and acquire a resource fork vnode. 
		 */
		if (cnp->cn_flags & CN_WANTSRSRCFORK) {
			error = ENOENT;
			goto bad;
		}
#endif

		error = lookup_validate_creation_path(ndp);
		if (error)
			goto bad;
		/*
		 * We return with ni_vp NULL to indicate that the entry
		 * doesn't currently exist, leaving a pointer to the
		 * referenced directory vnode in ndp->ni_dvp.
		 */
		if (cnp->cn_flags & SAVESTART) {
			if ( (vnode_get(ndp->ni_dvp)) ) {
				error = ENOENT;
				goto bad;
			}
			ndp->ni_startdir = ndp->ni_dvp;
		}
		if (!wantparent)
		        vnode_put(ndp->ni_dvp);

		if (kdebug_enable)
		        kdebug_lookup(ndp->ni_dvp, cnp);
		return (0);
	}
returned_from_lookup_path:
	/* We'll always have an iocount on ni_vp when this finishes. */
	error = lookup_handle_found_vnode(ndp, cnp, rdonly, vbusyflags, &keep_going, nc_generation, wantparent, atroot, ctx);
	if (error != 0) {
		goto bad2; 
	}

	if (keep_going) {
		dp = ndp->ni_vp;

		/* namei() will handle symlinks */
		if ((dp->v_type == VLNK) &&
				((cnp->cn_flags & FOLLOW) || (ndp->ni_flag & NAMEI_TRAILINGSLASH) || *ndp->ni_next == '/')) {
			return 0; 
		}

		/*
		 * Otherwise, there's more path to process.  
		 * cache_lookup_path is now responsible for dropping io ref on dp
		 * when it is called again in the dirloop.  This ensures we hold
		 * a ref on dp until we complete the next round of lookup.
		 */
		last_dp = dp;

		goto dirloop;
	}

	return (0);
bad2:
	if (ndp->ni_dvp)
		vnode_put(ndp->ni_dvp);

	vnode_put(ndp->ni_vp);
	ndp->ni_vp = NULLVP;

	if (kdebug_enable)
	        kdebug_lookup(dp, cnp);
	return (error);

bad:
	if (dp)
	        vnode_put(dp);
	ndp->ni_vp = NULLVP;

	if (kdebug_enable)
	        kdebug_lookup(dp, cnp);
	return (error);
}