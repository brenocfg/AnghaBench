#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
struct vnode_attr {scalar_t__ va_uid; } ;
struct componentname {int dummy; } ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_9__ {scalar_t__ v_type; int /*<<< orphan*/  v_flag; int /*<<< orphan*/ * v_mountedhere; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_WRITE_DATA ; 
 int EBUSY ; 
 int ENOTDIR ; 
 int EPERM ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MNT_WAIT ; 
 int /*<<< orphan*/  SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VATTR_INIT (struct vnode_attr*) ; 
 int /*<<< orphan*/  VATTR_WANTED (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 scalar_t__ VDIR ; 
 int /*<<< orphan*/  VMOUNT ; 
 int VNOP_FSYNC (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int buf_invalidateblks (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kauth_cred_getuid (int /*<<< orphan*/ ) ; 
 int mac_mount_check_mount (int /*<<< orphan*/ ,TYPE_1__*,struct componentname*,char const*) ; 
 int /*<<< orphan*/  va_uid ; 
 int /*<<< orphan*/  vfs_context_issuser (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 
 int vnode_getattr (TYPE_1__*,struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_lock_spin (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_unlock (TYPE_1__*) ; 

int
prepare_coveredvp(vnode_t vp, vfs_context_t ctx, struct componentname *cnp, const char *fsname, boolean_t skip_auth)
{
#if !CONFIG_MACF
#pragma unused(cnp,fsname)
#endif
	struct vnode_attr va;
	int error;

	if (!skip_auth) {
		/*
		 * If the user is not root, ensure that they own the directory
		 * onto which we are attempting to mount.
		 */
		VATTR_INIT(&va);
		VATTR_WANTED(&va, va_uid);
		if ((error = vnode_getattr(vp, &va, ctx)) ||
				(va.va_uid != kauth_cred_getuid(vfs_context_ucred(ctx)) &&
				 (!vfs_context_issuser(ctx)))) {
			error = EPERM;
			goto out;
		}
	}

	if ( (error = VNOP_FSYNC(vp, MNT_WAIT, ctx)) )
		goto out;

	if ( (error = buf_invalidateblks(vp, BUF_WRITE_DATA, 0, 0)) )
		goto out;

	if (vp->v_type != VDIR) {
		error = ENOTDIR;
		goto out;
	}

	if (ISSET(vp->v_flag, VMOUNT) && (vp->v_mountedhere != NULL)) {
		error = EBUSY;
		goto out;
	}

#if CONFIG_MACF
	error = mac_mount_check_mount(ctx, vp,
	    cnp, fsname);
	if (error != 0)
		goto out;
#endif

	vnode_lock_spin(vp);
	SET(vp->v_flag, VMOUNT);
	vnode_unlock(vp);

out:
	return error;
}