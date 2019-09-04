#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
struct timeval {scalar_t__ tv_sec; } ;
struct nameidata {char* ni_next; TYPE_2__* ni_dvp; TYPE_2__* ni_vp; TYPE_2__* ni_usedvp; scalar_t__ ni_pathlen; TYPE_2__* ni_rootdir; int /*<<< orphan*/  ni_flag; } ;
struct componentname {char* cn_nameptr; unsigned int cn_hash; int cn_namelen; int cn_flags; scalar_t__ cn_nameiop; } ;
typedef  TYPE_3__* mount_t ;
typedef  scalar_t__ kauth_cred_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_18__ {scalar_t__ mnt_generation; scalar_t__ mnt_realrootvp_vid; TYPE_2__* mnt_realrootvp; } ;
struct TYPE_17__ {scalar_t__ v_cred_timestamp; scalar_t__ v_cred; int v_authorized_actions; int v_flag; scalar_t__ v_type; scalar_t__ v_id; TYPE_3__* v_mountedhere; struct TYPE_17__* v_parent; TYPE_1__* v_mount; } ;
struct TYPE_16__ {int mnt_kern_flag; scalar_t__ mnt_authcache_ttl; } ;

/* Variables and functions */
 int CN_SKIPNAMECACHE ; 
 int ENODEV ; 
 int ENOENT ; 
 int ERECYCLE ; 
 scalar_t__ FALSE ; 
 int ISDOTDOT ; 
 int ISLASTCN ; 
 int KAUTH_VNODE_SEARCH ; 
 int KAUTH_VNODE_SEARCHBYANYONE ; 
 int LOCKPARENT ; 
 scalar_t__ LOOKUP ; 
 int MAKEENTRY ; 
 int MNTK_AUTH_CACHE_TTL ; 
 int MNTK_AUTH_OPAQUE ; 
 int /*<<< orphan*/  NAMEI_TRAILINGSLASH ; 
 int /*<<< orphan*/  NAME_CACHE_LOCK_SHARED () ; 
 int /*<<< orphan*/  NAME_CACHE_UNLOCK () ; 
 int NOCACHE ; 
 int NOCROSSMOUNT ; 
 TYPE_2__* NULLVP ; 
 int SAVESTART ; 
 scalar_t__ TRUE ; 
 scalar_t__ VDIR ; 
 int VISHARDLINK ; 
 scalar_t__ VLNK ; 
 int VROOT ; 
 int WANTPARENT ; 
 scalar_t__ cache_check_vnode_issubdir (TYPE_2__*,TYPE_2__*,scalar_t__*,TYPE_2__**) ; 
 TYPE_2__* cache_lookup_locked (TYPE_2__*,struct componentname*) ; 
 unsigned int* crc32tab ; 
 int /*<<< orphan*/  microuptime (struct timeval*) ; 
 scalar_t__ mount_generation ; 
 TYPE_2__* rootvnode ; 
 int /*<<< orphan*/  vfs_context_issuser (int /*<<< orphan*/ ) ; 
 scalar_t__ vfs_context_ucred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_get (TYPE_2__*) ; 
 int vnode_getwithvid_drainok (TYPE_2__*,int) ; 
 int /*<<< orphan*/  vnode_put (TYPE_2__*) ; 

int 
cache_lookup_path(struct nameidata *ndp, struct componentname *cnp, vnode_t dp, 
		vfs_context_t ctx, int *dp_authorized, vnode_t last_dp)
{
	char		*cp;		/* pointer into pathname argument */
	int		vid;
	int		vvid = 0;	/* protected by vp != NULLVP */
	vnode_t		vp = NULLVP;
	vnode_t		tdp = NULLVP;
	kauth_cred_t	ucred;
	boolean_t	ttl_enabled = FALSE;
	struct timeval	tv;
        mount_t		mp;
	unsigned int	hash;
	int		error = 0;
	boolean_t	dotdotchecked = FALSE;

#if CONFIG_TRIGGERS
	vnode_t 	trigger_vp;
#endif /* CONFIG_TRIGGERS */

	ucred = vfs_context_ucred(ctx);
	ndp->ni_flag &= ~(NAMEI_TRAILINGSLASH);

	NAME_CACHE_LOCK_SHARED();

	if ( dp->v_mount && (dp->v_mount->mnt_kern_flag & (MNTK_AUTH_OPAQUE | MNTK_AUTH_CACHE_TTL)) ) {
		ttl_enabled = TRUE;
		microuptime(&tv);
	}
	for (;;) {
		/*
		 * Search a directory.
		 *
		 * The cn_hash value is for use by cache_lookup
		 * The last component of the filename is left accessible via
		 * cnp->cn_nameptr for callers that need the name.
		 */
	        hash = 0;
		cp = cnp->cn_nameptr;

		while (*cp && (*cp != '/')) {
			hash = crc32tab[((hash >> 24) ^ (unsigned char)*cp++)] ^ hash << 8;
		}
		/*
		 * the crc generator can legitimately generate
		 * a 0... however, 0 for us means that we
		 * haven't computed a hash, so use 1 instead
		 */
		if (hash == 0)
		        hash = 1;
		cnp->cn_hash = hash;
		cnp->cn_namelen = cp - cnp->cn_nameptr;

		ndp->ni_pathlen -= cnp->cn_namelen;
		ndp->ni_next = cp;

		/*
		 * Replace multiple slashes by a single slash and trailing slashes
		 * by a null.  This must be done before VNOP_LOOKUP() because some
		 * fs's don't know about trailing slashes.  Remember if there were
		 * trailing slashes to handle symlinks, existing non-directories
		 * and non-existing files that won't be directories specially later.
		 */
		while (*cp == '/' && (cp[1] == '/' || cp[1] == '\0')) {
		        cp++;
			ndp->ni_pathlen--;

			if (*cp == '\0') {
			        ndp->ni_flag |= NAMEI_TRAILINGSLASH;
				*ndp->ni_next = '\0';
			}
		}
		ndp->ni_next = cp;

		cnp->cn_flags &= ~(MAKEENTRY | ISLASTCN | ISDOTDOT);

		if (*cp == '\0')
		        cnp->cn_flags |= ISLASTCN;

		if (cnp->cn_namelen == 2 && cnp->cn_nameptr[1] == '.' && cnp->cn_nameptr[0] == '.')
		        cnp->cn_flags |= ISDOTDOT;

		*dp_authorized = 0;
#if NAMEDRSRCFORK
		/*
		 * Process a request for a file's resource fork.
		 *
		 * Consume the _PATH_RSRCFORKSPEC suffix and tag the path.
		 */
		if ((ndp->ni_pathlen == sizeof(_PATH_RSRCFORKSPEC)) &&
		    (cp[1] == '.' && cp[2] == '.') &&
		    bcmp(cp, _PATH_RSRCFORKSPEC, sizeof(_PATH_RSRCFORKSPEC)) == 0) {
		    	/* Skip volfs file systems that don't support native streams. */
			if ((dp->v_mount != NULL) &&
			    (dp->v_mount->mnt_flag & MNT_DOVOLFS) &&
			    (dp->v_mount->mnt_kern_flag & MNTK_NAMED_STREAMS) == 0) {
				goto skiprsrcfork;
			}
			cnp->cn_flags |= CN_WANTSRSRCFORK;
			cnp->cn_flags |= ISLASTCN;
			ndp->ni_next[0] = '\0';
			ndp->ni_pathlen = 1;
		}
skiprsrcfork:
#endif

#if CONFIG_MACF

		/*
		 * Name cache provides authorization caching (see below)
		 * that will short circuit MAC checks in lookup().
		 * We must perform MAC check here.  On denial
		 * dp_authorized will remain 0 and second check will
		 * be perfomed in lookup().
		 */
		if (!(cnp->cn_flags & DONOTAUTH)) {
			error = mac_vnode_check_lookup(ctx, dp, cnp);
			if (error) {
				NAME_CACHE_UNLOCK();
				goto errorout;
			}
		}
#endif /* MAC */
		if (ttl_enabled &&
		    (dp->v_mount->mnt_authcache_ttl == 0 ||
		    ((tv.tv_sec - dp->v_cred_timestamp) > dp->v_mount->mnt_authcache_ttl))) {
		        break;
		}

		/*
		 * NAME_CACHE_LOCK holds these fields stable
		 *
		 * We can't cache KAUTH_VNODE_SEARCHBYANYONE for root correctly
		 * so we make an ugly check for root here. root is always
		 * allowed and breaking out of here only to find out that is
		 * authorized by virtue of being root is very very expensive.
		 * However, the check for not root is valid only for filesystems
		 * which use local authorization.
		 *
		 * XXX: Remove the check for root when we can reliably set
		 * KAUTH_VNODE_SEARCHBYANYONE as root.
		 */
		if ((dp->v_cred != ucred || !(dp->v_authorized_actions & KAUTH_VNODE_SEARCH)) &&
		    !(dp->v_authorized_actions & KAUTH_VNODE_SEARCHBYANYONE) &&
		    (ttl_enabled || !vfs_context_issuser(ctx)))  {
		        break;
		}

		/*
		 * indicate that we're allowed to traverse this directory...
		 * even if we fail the cache lookup or decide to bail for
		 * some other reason, this information is valid and is used
		 * to avoid doing a vnode_authorize before the call to VNOP_LOOKUP
		 */
		*dp_authorized = 1;

		if ( (cnp->cn_flags & (ISLASTCN | ISDOTDOT)) ) {
			if (cnp->cn_nameiop != LOOKUP)
				break;
			if (cnp->cn_flags & LOCKPARENT) 
				break;
			if (cnp->cn_flags & NOCACHE)
				break;
			if (cnp->cn_flags & ISDOTDOT) {
				/*
				 * Force directory hardlinks to go to
				 * file system for ".." requests.
				 */
				if ((dp->v_flag & VISHARDLINK)) {
					break;
				}
				/*
				 * Quit here only if we can't use
				 * the parent directory pointer or
				 * don't have one.  Otherwise, we'll
				 * use it below.
				 */
				if ((dp->v_flag & VROOT)  ||
				    dp == ndp->ni_rootdir ||
				    dp->v_parent == NULLVP)
					break;
			}
		}

		if ((cnp->cn_flags & CN_SKIPNAMECACHE)) {
			/*
			 * Force lookup to go to the filesystem with
			 * all cnp fields set up.
			 */
			break;
		}

		/*
		 * "." and ".." aren't supposed to be cached, so check
		 * for them before checking the cache.
		 */
		if (cnp->cn_namelen == 1 && cnp->cn_nameptr[0] == '.')
			vp = dp;
		else if ( (cnp->cn_flags & ISDOTDOT) ) {
			/*
			 * If this is a chrooted process, we need to check if
			 * the process is trying to break out of its chrooted
			 * jail. We do that by trying to determine if dp is
			 * a subdirectory of ndp->ni_rootdir. If we aren't
			 * able to determine that by the v_parent pointers, we
			 * will leave the fast path.
			 *
			 * Since this function may see dotdot components
			 * many times and it has the name cache lock held for
			 * the entire duration, we optimise this by doing this
			 * check only once per cache_lookup_path call.
			 * If dotdotchecked is set, it means we've done this
			 * check once already and don't need to do it again.
			 */
			if (!dotdotchecked && (ndp->ni_rootdir != rootvnode)) {
				vnode_t tvp = dp;
				boolean_t defer = FALSE;
				boolean_t is_subdir = FALSE;

				defer = cache_check_vnode_issubdir(tvp,
				    ndp->ni_rootdir, &is_subdir, &tvp);

				if (defer) {
					/* defer to Filesystem */
					break;
				} else if (!is_subdir) {
					/*
					 * This process is trying to break  out
					 * of its chrooted jail, so all its
					 * dotdot accesses will be translated to
					 * its root directory.
					 */
					vp = ndp->ni_rootdir;
				} else {
					/*
					 * All good, let this dotdot access
					 * proceed normally
					 */
					vp = dp->v_parent;
				}
				dotdotchecked = TRUE;
			} else {
				vp = dp->v_parent;
			}
		} else {
			if ( (vp = cache_lookup_locked(dp, cnp)) == NULLVP)
				break;

			if ( (vp->v_flag & VISHARDLINK) ) {
				/*
				 * The file system wants a VNOP_LOOKUP on this vnode
				 */
				vp = NULL;
				break;
			}
		}
		if ( (cnp->cn_flags & ISLASTCN) )
		        break;

		if (vp->v_type != VDIR) {
		        if (vp->v_type != VLNK)
			        vp = NULL;
		        break;
		}

		if ( (mp = vp->v_mountedhere) && ((cnp->cn_flags & NOCROSSMOUNT) == 0)) {
			vnode_t tmp_vp = mp->mnt_realrootvp;
			if (tmp_vp == NULLVP || mp->mnt_generation != mount_generation ||
				mp->mnt_realrootvp_vid != tmp_vp->v_id)
				break;
			vp = tmp_vp;
		}

#if CONFIG_TRIGGERS
		/*
		 * After traversing all mountpoints stacked here, if we have a
		 * trigger in hand, resolve it.  Note that we don't need to 
		 * leave the fast path if the mount has already happened.
		 */
		if (vp->v_resolve)
			break;
#endif /* CONFIG_TRIGGERS */


		dp = vp;
		vp = NULLVP;

		cnp->cn_nameptr = ndp->ni_next + 1;
		ndp->ni_pathlen--;
		while (*cnp->cn_nameptr == '/') {
		        cnp->cn_nameptr++;
			ndp->ni_pathlen--;
		}
	}
	if (vp != NULLVP)
	        vvid = vp->v_id;
	vid = dp->v_id;
	
	NAME_CACHE_UNLOCK();

	if ((vp != NULLVP) && (vp->v_type != VLNK) &&
	    ((cnp->cn_flags & (ISLASTCN | LOCKPARENT | WANTPARENT | SAVESTART)) == ISLASTCN)) {
	        /*
		 * if we've got a child and it's the last component, and 
		 * the lookup doesn't need to return the parent then we
		 * can skip grabbing an iocount on the parent, since all
		 * we're going to do with it is a vnode_put just before
		 * we return from 'lookup'.  If it's a symbolic link,
		 * we need the parent in case the link happens to be
		 * a relative pathname.
		 */
	        tdp = dp;
	        dp = NULLVP;
	} else {
need_dp:
		/*
		 * return the last directory we looked at
		 * with an io reference held. If it was the one passed
		 * in as a result of the last iteration of VNOP_LOOKUP,
		 * it should already hold an io ref. No need to increase ref.
		 */
		if (last_dp != dp){
			
			if (dp == ndp->ni_usedvp) {
				/*
				 * if this vnode matches the one passed in via USEDVP
				 * than this context already holds an io_count... just
				 * use vnode_get to get an extra ref for lookup to play
				 * with... can't use the getwithvid variant here because
				 * it will block behind a vnode_drain which would result
				 * in a deadlock (since we already own an io_count that the
				 * vnode_drain is waiting on)... vnode_get grabs the io_count
				 * immediately w/o waiting... it always succeeds
				 */
				vnode_get(dp);
			} else if ((error = vnode_getwithvid_drainok(dp, vid))) {
				/*
				 * failure indicates the vnode
				 * changed identity or is being
				 * TERMINATED... in either case
				 * punt this lookup.
				 * 
				 * don't necessarily return ENOENT, though, because
				 * we really want to go back to disk and make sure it's
				 * there or not if someone else is changing this
				 * vnode. That being said, the one case where we do want
				 * to return ENOENT is when the vnode's mount point is
				 * in the process of unmounting and we might cause a deadlock
				 * in our attempt to take an iocount. An ENODEV error return
				 * is from vnode_get* is an indication this but we change that
				 * ENOENT for upper layers.
				 */
				if (error == ENODEV) {
					error = ENOENT;
				} else {
					error = ERECYCLE;
				}
				goto errorout;
			}
		}
	}
	if (vp != NULLVP) {
	        if ( (vnode_getwithvid_drainok(vp, vvid)) ) {
		        vp = NULLVP;

		        /*
			 * can't get reference on the vp we'd like
			 * to return... if we didn't grab a reference
			 * on the directory (due to fast path bypass),
			 * then we need to do it now... we can't return
			 * with both ni_dvp and ni_vp NULL, and no 
			 * error condition
			 */
			if (dp == NULLVP) {
			        dp = tdp;
				goto need_dp;
			}
		}
	}

	ndp->ni_dvp = dp;
	ndp->ni_vp  = vp;

#if CONFIG_TRIGGERS
	trigger_vp = vp ? vp : dp;
	if ((error == 0) && (trigger_vp != NULLVP) && vnode_isdir(trigger_vp)) {
		error = vnode_trigger_resolve(trigger_vp, ndp, ctx);
		if (error) {
			if (vp)
				vnode_put(vp);
			if (dp) 
				vnode_put(dp);
			goto errorout;
		}
	} 
#endif /* CONFIG_TRIGGERS */

errorout:
	/* 
	 * If we came into cache_lookup_path after an iteration of the lookup loop that
	 * resulted in a call to VNOP_LOOKUP, then VNOP_LOOKUP returned a vnode with a io ref
	 * on it.  It is now the job of cache_lookup_path to drop the ref on this vnode 
	 * when it is no longer needed.  If we get to this point, and last_dp is not NULL
	 * and it is ALSO not the dvp we want to return to caller of this function, it MUST be
	 * the case that we got to a subsequent path component and this previous vnode is 
	 * no longer needed.  We can then drop the io ref on it.
	 */
	if ((last_dp != NULLVP) && (last_dp != ndp->ni_dvp)){
		vnode_put(last_dp);
	}
	
	//initialized to 0, should be the same if no error cases occurred.
	return error;
}