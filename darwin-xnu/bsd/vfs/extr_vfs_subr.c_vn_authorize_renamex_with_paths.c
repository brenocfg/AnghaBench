#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int vfs_rename_flags_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
struct vnode {scalar_t__ v_type; struct vnode* v_parent; } ;
struct componentname {int cn_namelen; char* cn_nameptr; int cn_flags; int /*<<< orphan*/  cn_ndp; } ;
typedef  int kauth_action_t ;

/* Variables and functions */
 int EINVAL ; 
 int EISDIR ; 
 int ENOTDIR ; 
 int ISDOTDOT ; 
 int /*<<< orphan*/  KAUTH_FILEOP_WILL_RENAME ; 
 int KAUTH_VNODE_ADD_FILE ; 
 int KAUTH_VNODE_ADD_SUBDIRECTORY ; 
 int KAUTH_VNODE_DELETE ; 
 struct vnode* NULLVP ; 
 scalar_t__ VDIR ; 
 int VFS_RENAME_SWAP ; 
 int /*<<< orphan*/  kauth_authorize_fileop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t,uintptr_t) ; 
 int lookup_validate_creation_path (int /*<<< orphan*/ ) ; 
 int mac_vnode_check_rename (int /*<<< orphan*/ ,struct vnode*,struct vnode*,struct componentname*,struct vnode*,struct vnode*,struct componentname*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 
 int vnode_authorize (struct vnode*,struct vnode*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ vnode_compound_rename_available (struct vnode*) ; 
 scalar_t__ vnode_isdir (struct vnode*) ; 

int
vn_authorize_renamex_with_paths(struct vnode *fdvp,  struct vnode *fvp,  struct componentname *fcnp, const char *from_path,
					 struct vnode *tdvp,  struct vnode *tvp,  struct componentname *tcnp, const char *to_path,
					 vfs_context_t ctx, vfs_rename_flags_t flags, void *reserved)
{
	int error = 0;
	int moving = 0;
	bool swap = flags & VFS_RENAME_SWAP;

	if (reserved != NULL) {
		panic("Passed something other than NULL as reserved field!");
	}

	/*
	 * Avoid renaming "." and "..".
	 *
	 * XXX No need to check for this in the FS.  We should always have the leaves
	 * in VFS in this case.
	 */
	if (fvp->v_type == VDIR &&
	    ((fdvp == fvp) ||
	     (fcnp->cn_namelen == 1 && fcnp->cn_nameptr[0] == '.') ||
	     ((fcnp->cn_flags | tcnp->cn_flags) & ISDOTDOT)) ) {
		error = EINVAL;
		goto out;
	}

	if (tvp == NULLVP && vnode_compound_rename_available(tdvp)) {
		error = lookup_validate_creation_path(tcnp->cn_ndp);
		if (error) 
			goto out;
	}

	/***** <MACF> *****/
#if CONFIG_MACF
	error = mac_vnode_check_rename(ctx, fdvp, fvp, fcnp, tdvp, tvp, tcnp);
	if (error)
		goto out;
	if (swap) {
		error = mac_vnode_check_rename(ctx, tdvp, tvp, tcnp, fdvp, fvp, fcnp);
		if (error)
			goto out;
	}
#endif
	/***** </MACF> *****/

	/***** <MiscChecks> *****/
	if (tvp != NULL) {
		if (!swap) {
			if (fvp->v_type == VDIR && tvp->v_type != VDIR) {
				error = ENOTDIR;
				goto out;
			} else if (fvp->v_type != VDIR && tvp->v_type == VDIR) {
				error = EISDIR;
				goto out;
			}
		}
	} else if (swap) {
		/*
		 * Caller should have already checked this and returned
		 * ENOENT.  If we send back ENOENT here, caller will retry
		 * which isn't what we want so we send back EINVAL here
		 * instead.
		 */
		error = EINVAL;
		goto out;
	}

	if (fvp == tdvp) {
		error = EINVAL;
		goto out;
	}

	/*
	 * The following edge case is caught here:
	 * (to cannot be a descendent of from)
	 *
	 *       o fdvp
	 *      /
	 *     /
	 *    o fvp
	 *     \
	 *      \
	 *       o tdvp
	 *      /
	 *     /
	 *    o tvp
	 */
	if (tdvp->v_parent == fvp) {
		error = EINVAL;
		goto out;
	}

	if (swap && fdvp->v_parent == tvp) {
		error = EINVAL;
		goto out;
	}
	/***** </MiscChecks> *****/

	/***** <Kauth> *****/

	/*
	 * As part of the Kauth step, we call out to allow 3rd-party
	 * fileop notification of "about to rename".  This is needed
	 * in the event that 3rd-parties need to know that the DELETE
	 * authorization is actually part of a rename.  It's important
	 * that we guarantee that the DELETE call-out will always be
	 * made if the WILL_RENAME call-out is made.  Another fileop
	 * call-out will be performed once the operation is completed.
	 * We can ignore the result of kauth_authorize_fileop().
	 *
	 * N.B. We are passing the vnode and *both* paths to each
	 * call; kauth_authorize_fileop() extracts the "from" path
	 * when posting a KAUTH_FILEOP_WILL_RENAME notification.
	 * As such, we only post these notifications if all of the
	 * information we need is provided.
	 */

	if (swap) {
		kauth_action_t f = 0, t = 0;

		/*
		 * Directories changing parents need ...ADD_SUBDIR...  to
		 * permit changing ".."
		 */
		if (fdvp != tdvp) {
			if (vnode_isdir(fvp))
				f = KAUTH_VNODE_ADD_SUBDIRECTORY;
			if (vnode_isdir(tvp))
				t = KAUTH_VNODE_ADD_SUBDIRECTORY;
		}
		if (to_path != NULL)
			kauth_authorize_fileop(vfs_context_ucred(ctx),
					KAUTH_FILEOP_WILL_RENAME,
					(uintptr_t)fvp,
					(uintptr_t)to_path);
		error = vnode_authorize(fvp, fdvp, KAUTH_VNODE_DELETE | f, ctx);
		if (error)
			goto out;
		if (from_path != NULL)
			kauth_authorize_fileop(vfs_context_ucred(ctx),
					KAUTH_FILEOP_WILL_RENAME,
					(uintptr_t)tvp,
					(uintptr_t)from_path);
		error = vnode_authorize(tvp, tdvp, KAUTH_VNODE_DELETE | t, ctx);
		if (error)
			goto out;
		f = vnode_isdir(fvp) ? KAUTH_VNODE_ADD_SUBDIRECTORY : KAUTH_VNODE_ADD_FILE;
		t = vnode_isdir(tvp) ? KAUTH_VNODE_ADD_SUBDIRECTORY : KAUTH_VNODE_ADD_FILE;
		if (fdvp == tdvp)
			error = vnode_authorize(fdvp, NULL, f | t, ctx);
		else {
			error = vnode_authorize(fdvp, NULL, t, ctx);
			if (error)
				goto out;
			error = vnode_authorize(tdvp, NULL, f, ctx);
		}
		if (error)
			goto out;
	} else {
		error = 0;
		if ((tvp != NULL) && vnode_isdir(tvp)) {
			if (tvp != fdvp)
				moving = 1;
		} else if (tdvp != fdvp) {
			moving = 1;
		}

		/*
		 * must have delete rights to remove the old name even in
		 * the simple case of fdvp == tdvp.
		 *
		 * If fvp is a directory, and we are changing it's parent,
		 * then we also need rights to rewrite its ".." entry as well.
		 */
		if (to_path != NULL)
			kauth_authorize_fileop(vfs_context_ucred(ctx),
					KAUTH_FILEOP_WILL_RENAME,
					(uintptr_t)fvp,
					(uintptr_t)to_path);
		if (vnode_isdir(fvp)) {
			if ((error = vnode_authorize(fvp, fdvp, KAUTH_VNODE_DELETE | KAUTH_VNODE_ADD_SUBDIRECTORY, ctx)) != 0)
				goto out;
		} else {
			if ((error = vnode_authorize(fvp, fdvp, KAUTH_VNODE_DELETE, ctx)) != 0)
				goto out;
		}
		if (moving) {
			/* moving into tdvp or tvp, must have rights to add */
			if ((error = vnode_authorize(((tvp != NULL) && vnode_isdir(tvp)) ? tvp : tdvp,
							NULL, 
							vnode_isdir(fvp) ? KAUTH_VNODE_ADD_SUBDIRECTORY : KAUTH_VNODE_ADD_FILE,
							ctx)) != 0) {
				goto out;
			}
		} else {
			/* node staying in same directory, must be allowed to add new name */
			if ((error = vnode_authorize(fdvp, NULL,
							vnode_isdir(fvp) ? KAUTH_VNODE_ADD_SUBDIRECTORY : KAUTH_VNODE_ADD_FILE, ctx)) != 0)
				goto out;
		}
		/* overwriting tvp */
		if ((tvp != NULL) && !vnode_isdir(tvp) &&
				((error = vnode_authorize(tvp, tdvp, KAUTH_VNODE_DELETE, ctx)) != 0)) {
			goto out;
		}
	}

	/***** </Kauth> *****/

	/* XXX more checks? */
out:
	return error;
}