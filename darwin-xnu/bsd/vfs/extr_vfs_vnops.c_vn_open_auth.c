#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vfs_context_t ;
typedef  int uint32_t ;
struct vnode_attr {int /*<<< orphan*/  va_dataprotect_flags; } ;
struct vnode {int v_flag; struct vnode* v_parent; } ;
struct TYPE_3__ {scalar_t__ cn_context; int cn_flags; int /*<<< orphan*/  cn_nameiop; } ;
struct nameidata {int ni_flag; struct vnode* ni_vp; TYPE_1__ ni_cnd; struct vnode* ni_dvp; int /*<<< orphan*/  ni_op; } ;
typedef  int boolean_t ;
struct TYPE_4__ {int p_flag; } ;

/* Variables and functions */
 int AUDITVNPATH1 ; 
 int CN_ALLOWRSRCFORK ; 
 int CN_RAW_ENCRYPTED ; 
 int CN_SKIPNAMECACHE ; 
 int /*<<< orphan*/  CREATE ; 
 int EEXIST ; 
 int EINVAL ; 
 int EKEEPLOOKING ; 
 int ENOENT ; 
 int EPERM ; 
 int EREDRIVEOPEN ; 
 int FALSE ; 
 int FENCRYPTED ; 
 int FOLLOW ; 
 int FUNENCRYPTED ; 
 int FWRITE ; 
 int IOTaskHasEntitlement (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int LOCKLEAF ; 
 int LOCKPARENT ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  MIN (int,int) ; 
 void* NAMEI_COMPOUNDOPEN ; 
 int NAMEI_CONTLOOKUP ; 
 int NOCROSSMOUNT ; 
 struct vnode* NULLVP ; 
 int /*<<< orphan*/  OP_LINK ; 
 int O_CREAT ; 
 int O_DIRECTORY ; 
 int O_EVTONLY ; 
 int O_EXCL ; 
 int O_NOFOLLOW ; 
 int O_SYMLINK ; 
 int O_TRUNC ; 
 int /*<<< orphan*/  PVFS ; 
 int P_CHECKOPENEVT ; 
 int RETRY_NO_YIELD_COUNT ; 
 int TRUE ; 
 int USEDVP ; 
 scalar_t__ VATTR_IS_ACTIVE (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VA_DP_RAWENCRYPTED ; 
 int /*<<< orphan*/  VA_DP_RAWUNENCRYPTED ; 
 int /*<<< orphan*/  VNOP_CLOSE (struct vnode*,int,scalar_t__) ; 
 int VNOP_COMPOUND_OPEN (struct vnode*,struct vnode**,struct nameidata*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int VNOP_OPEN (struct vnode*,int,scalar_t__) ; 
 int VOPENEVT ; 
 int WANTPARENT ; 
 TYPE_2__* current_proc () ; 
 int /*<<< orphan*/  current_task () ; 
 int hz ; 
 int namei (struct nameidata*) ; 
 int /*<<< orphan*/  nameidone (struct nameidata*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  tsleep (int*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va_dataprotect_flags ; 
 scalar_t__ vfs_context_kernel () ; 
 int vn_authorize_open_existing (struct vnode*,TYPE_1__*,int,scalar_t__,int /*<<< orphan*/ *) ; 
 int vn_open_auth_do_create (struct nameidata*,struct vnode_attr*,int,int*,int*,scalar_t__) ; 
 int vn_open_auth_finish (struct vnode*,int,scalar_t__) ; 
 int vnode_compound_open_available (struct vnode*) ; 
 scalar_t__ vnode_isnamedstream (struct vnode*) ; 
 scalar_t__ vnode_isshadow (struct vnode*) ; 
 scalar_t__ vnode_isswap (struct vnode*) ; 
 int /*<<< orphan*/  vnode_isvroot (struct vnode*) ; 
 scalar_t__ vnode_mount (struct vnode*) ; 
 int /*<<< orphan*/  vnode_put (struct vnode*) ; 
 int /*<<< orphan*/  vnode_recycle (struct vnode*) ; 

int
vn_open_auth(struct nameidata *ndp, int *fmodep, struct vnode_attr *vap)
{
	struct vnode *vp;
	struct vnode *dvp;
	vfs_context_t ctx = ndp->ni_cnd.cn_context;
	int error;
	int fmode;
	uint32_t origcnflags;
	boolean_t did_create;
	boolean_t did_open;
	boolean_t need_vnop_open;
	boolean_t batched;
	boolean_t ref_failed;
	int nretries = 0;

again:
	vp = NULL;
	dvp = NULL;
	batched = FALSE;
	did_create = FALSE;
	need_vnop_open = TRUE;
	ref_failed = FALSE;
	fmode = *fmodep;
	origcnflags = ndp->ni_cnd.cn_flags;

	// If raw encrypted mode is requested, handle that here
	if (VATTR_IS_ACTIVE (vap, va_dataprotect_flags)
		&& ISSET(vap->va_dataprotect_flags, VA_DP_RAWENCRYPTED)) {
		fmode |= FENCRYPTED;
	}

	/*
	 * O_CREAT
	 */
	if (fmode & O_CREAT) {
	        if ( (fmode & O_DIRECTORY) ) {
		        error = EINVAL;
			goto out;
		}
		ndp->ni_cnd.cn_nameiop = CREATE;
#if CONFIG_TRIGGERS
		ndp->ni_op = OP_LINK;
#endif
		/* Inherit USEDVP, vnode_open() supported flags only */
		ndp->ni_cnd.cn_flags &= (USEDVP | NOCROSSMOUNT);
		ndp->ni_cnd.cn_flags |= LOCKPARENT | LOCKLEAF | AUDITVNPATH1;
		ndp->ni_flag = NAMEI_COMPOUNDOPEN;
#if NAMEDRSRCFORK
		/* open calls are allowed for resource forks. */
		ndp->ni_cnd.cn_flags |= CN_ALLOWRSRCFORK;
#endif
		if ((fmode & O_EXCL) == 0 && (fmode & O_NOFOLLOW) == 0 && (origcnflags & FOLLOW) != 0)
			ndp->ni_cnd.cn_flags |= FOLLOW;

continue_create_lookup:
		if ( (error = namei(ndp)) )
			goto out;

		dvp = ndp->ni_dvp;
		vp = ndp->ni_vp;

		batched = vnode_compound_open_available(dvp);

		/* not found, create */
		if (vp == NULL) {
			/* must have attributes for a new file */
			if (vap == NULL) {
				vnode_put(dvp);
				error = EINVAL;
				goto out;
			}
			/*
			 * Attempt a create.   For a system supporting compound VNOPs, we may
			 * find an existing file or create one; in either case, we will already
			 * have the file open and no VNOP_OPEN() will be needed.
			 */
			error = vn_open_auth_do_create(ndp, vap, fmode, &did_create, &did_open, ctx);

			dvp = ndp->ni_dvp;
			vp = ndp->ni_vp;

			/* 
			 * Detected a node that the filesystem couldn't handle.  Don't call
			 * nameidone() yet, because we need that path buffer.
			 */
			if (error == EKEEPLOOKING) {
				if (!batched) {
					panic("EKEEPLOOKING from a filesystem that doesn't support compound VNOPs?");
				}
				goto continue_create_lookup;
			}

			nameidone(ndp);
			if (dvp) {
				panic("Shouldn't have a dvp here.");
			}

			if (error) {
				/*
				 * Check for a create race.
				 */
				if ((error == EEXIST) && !(fmode & O_EXCL)){
					if (vp) 
						vnode_put(vp);
					goto again;
				}
				goto bad;
			}

			need_vnop_open = !did_open;
		} 
		else {
			if (fmode & O_EXCL)
				error = EEXIST;

			/* 
			 * We have a vnode.  Use compound open if available 
			 * or else fall through to "traditional" path.  Note: can't
			 * do a compound open for root, because the parent belongs
			 * to a different FS.
			 */
			if (error == 0 && batched && (vnode_mount(dvp) == vnode_mount(vp))) {
				error = VNOP_COMPOUND_OPEN(dvp, &ndp->ni_vp, ndp, 0, fmode, NULL, NULL, ctx);

				if (error == 0) {
					vp = ndp->ni_vp;
					need_vnop_open = FALSE;
				} else if (error == EKEEPLOOKING) {
					if ((ndp->ni_flag & NAMEI_CONTLOOKUP) == 0) {
						panic("EKEEPLOOKING, but continue flag not set?");
					}
					goto continue_create_lookup;
				} 
			}
			nameidone(ndp);
			vnode_put(dvp);
			ndp->ni_dvp = NULLVP;

			if (error) {
				goto bad;
			}

			fmode &= ~O_CREAT;

			/* Fall through */
		}
	}
    else {
		/*
		 * Not O_CREAT
		 */
		ndp->ni_cnd.cn_nameiop = LOOKUP;
		/* Inherit USEDVP, vnode_open() supported flags only */
		ndp->ni_cnd.cn_flags &= (USEDVP | NOCROSSMOUNT);
		ndp->ni_cnd.cn_flags |= FOLLOW | LOCKLEAF | AUDITVNPATH1 | WANTPARENT;
#if NAMEDRSRCFORK
		/* open calls are allowed for resource forks. */
		ndp->ni_cnd.cn_flags |= CN_ALLOWRSRCFORK;
#endif
		if (fmode & FENCRYPTED)
			ndp->ni_cnd.cn_flags |= CN_RAW_ENCRYPTED | CN_SKIPNAMECACHE;
		ndp->ni_flag = NAMEI_COMPOUNDOPEN;

		/* preserve NOFOLLOW from vnode_open() */
		if (fmode & O_NOFOLLOW || fmode & O_SYMLINK || (origcnflags & FOLLOW) == 0) {
			ndp->ni_cnd.cn_flags &= ~FOLLOW;
		}

		/* Do a lookup, possibly going directly to filesystem for compound operation */
		do {
			if ( (error = namei(ndp)) )
				goto out;
			vp = ndp->ni_vp;
			dvp = ndp->ni_dvp;

			/* Check for batched lookup-open */
			batched = vnode_compound_open_available(dvp);
			if (batched && ((vp == NULLVP) || (vnode_mount(dvp) == vnode_mount(vp)))) {
				error = VNOP_COMPOUND_OPEN(dvp, &ndp->ni_vp, ndp, 0, fmode, NULL, NULL, ctx);
				vp = ndp->ni_vp;
				if (error == 0) {
					need_vnop_open = FALSE;
				} else if (error == EKEEPLOOKING) {
					if ((ndp->ni_flag & NAMEI_CONTLOOKUP) == 0) {
						panic("EKEEPLOOKING, but continue flag not set?");
					}
				}
			}
		} while (error == EKEEPLOOKING);

		nameidone(ndp);
		vnode_put(dvp);
		ndp->ni_dvp = NULLVP;

		if (error) {
			goto bad;
		}
	}

	/* 
	 * By this point, nameidone() is called, dvp iocount is dropped,
	 * and dvp pointer is cleared.
	 */
	if (ndp->ni_dvp != NULLVP) {
		panic("Haven't cleaned up adequately in vn_open_auth()");
	}

#if DEVELOPMENT || DEBUG
	/*
	 * XXX VSWAP: Check for entitlements or special flag here
	 * so we can restrict access appropriately.
	 */
#else /* DEVELOPMENT || DEBUG */

	if (vnode_isswap(vp) && (fmode & (FWRITE | O_TRUNC)) && (ctx != vfs_context_kernel())) {
		error = EPERM;
		goto bad;
	}
#endif /* DEVELOPMENT || DEBUG */

	/*
	 * Expect to use this code for filesystems without compound VNOPs, for the root 
	 * of a filesystem, which can't be "looked up" in the sense of VNOP_LOOKUP(),
	 * and for shadow files, which do not live on the same filesystems as their "parents."
	 */
	if (need_vnop_open) {
		if (batched && !vnode_isvroot(vp) && !vnode_isnamedstream(vp)) {
			panic("Why am I trying to use VNOP_OPEN() on anything other than the root or a named stream?");
		}

		if (!did_create) {
			error = vn_authorize_open_existing(vp, &ndp->ni_cnd, fmode, ctx, NULL);
			if (error) {
				goto bad;
			}
		}

		if (VATTR_IS_ACTIVE (vap, va_dataprotect_flags)
			&& ISSET(vap->va_dataprotect_flags, VA_DP_RAWUNENCRYPTED)) {
			/* Don't allow unencrypted io request from user space unless entitled */
			boolean_t entitled = FALSE;
#if !SECURE_KERNEL
			entitled = IOTaskHasEntitlement(current_task(), "com.apple.private.security.file-unencrypt-access");
#endif
			if (!entitled) {
				error = EPERM;
				goto bad;
			}
			fmode |= FUNENCRYPTED;
		}

		error = VNOP_OPEN(vp, fmode, ctx);
		if (error) {
			goto bad;
		}
		need_vnop_open = FALSE;
	}

	// if the vnode is tagged VOPENEVT and the current process
	// has the P_CHECKOPENEVT flag set, then we or in the O_EVTONLY
	// flag to the open mode so that this open won't count against
	// the vnode when carbon delete() does a vnode_isinuse() to see
	// if a file is currently in use.  this allows spotlight
	// importers to not interfere with carbon apps that depend on
	// the no-delete-if-busy semantics of carbon delete().
	//
	if (!did_create && (vp->v_flag & VOPENEVT) && (current_proc()->p_flag & P_CHECKOPENEVT)) {
		fmode |= O_EVTONLY;
	}

	/*
	 * Grab reference, etc.
	 */
	error = vn_open_auth_finish(vp, fmode, ctx);
	if (error) {
		ref_failed = TRUE;
		goto bad;
	}

	/* Compound VNOP open is responsible for doing the truncate */
	if (batched || did_create) 
		fmode &= ~O_TRUNC;

	*fmodep = fmode;
	return (0);

bad:
	/* Opened either explicitly or by a batched create */
	if (!need_vnop_open) {
		VNOP_CLOSE(vp, fmode, ctx);
	}

	ndp->ni_vp = NULL;
	if (vp) {
#if NAMEDRSRCFORK
		/* Aggressively recycle shadow files if we error'd out during open() */
		if ((vnode_isnamedstream(vp)) &&
			(vp->v_parent != NULLVP) && 
			(vnode_isshadow(vp))) {
				vnode_recycle(vp);
		}
#endif
		vnode_put(vp);
		/*
		 * Check for a race against unlink.  We had a vnode
		 * but according to vnode_authorize or VNOP_OPEN it
		 * no longer exists.
		 *
		 * EREDRIVEOPEN: means that we were hit by the tty allocation race.
		 */
		if (((error == ENOENT) && (*fmodep & O_CREAT)) || (error == EREDRIVEOPEN) || ref_failed) {
			/*
			 * We'll retry here but it may be possible that we get
			 * into a retry "spin" inside the kernel and not allow
			 * threads, which need to run in order for the retry
			 * loop to end, to run. An example is an open of a
			 * terminal which is getting revoked and we spin here
			 * without yielding becasue namei and VNOP_OPEN are
			 * successful but vnode_ref fails. The revoke needs
			 * threads with an iocount to run but if spin here we
			 * may possibly be blcoking other threads from running.
			 *
			 * We start yielding the CPU after some number of
			 * retries for increasing durations. Note that this is
			 * still a loop without an exit condition.
			 */
			nretries += 1;
			if (nretries > RETRY_NO_YIELD_COUNT) {
				/* Every hz/100 secs is 10 msecs ... */
				tsleep(&nretries, PVFS, "vn_open_auth_retry",
				    MIN((nretries * (hz/100)), hz));
			}
			goto again;
		}
	}

out:
	return (error);
}