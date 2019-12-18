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
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int /*<<< orphan*/  uid_t ;
struct vnode_attr {int dummy; } ;
struct nameidata {int /*<<< orphan*/  ni_vp; } ;
typedef  scalar_t__ kauth_action_t ;
typedef  int /*<<< orphan*/  gid_t ;
typedef  enum uio_seg { ____Placeholder_uio_seg } uio_seg ;

/* Variables and functions */
 int AT_SYMLINK_NOFOLLOW ; 
 int AUDITVNPATH1 ; 
 int /*<<< orphan*/  AUDIT_ARG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EACCES ; 
 int EPERM ; 
 int FOLLOW ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NOFOLLOW ; 
 int /*<<< orphan*/  OP_SETATTR ; 
 int /*<<< orphan*/  VATTR_INIT (struct vnode_attr*) ; 
 int /*<<< orphan*/  VATTR_SET (struct vnode_attr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VNOVAL ; 
 int mac_vnode_check_setowner (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_vnode_notify_setowner (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nameiat (struct nameidata*,int) ; 
 int /*<<< orphan*/  nameidone (struct nameidata*) ; 
 int /*<<< orphan*/  owner ; 
 int /*<<< orphan*/  va_gid ; 
 int /*<<< orphan*/  va_uid ; 
 int vnode_authattr (int /*<<< orphan*/ ,struct vnode_attr*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int vnode_authorize (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_put (int /*<<< orphan*/ ) ; 
 int vnode_setattr (int /*<<< orphan*/ ,struct vnode_attr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fchownat_internal(vfs_context_t ctx, int fd, user_addr_t path, uid_t uid,
   gid_t gid, int flag, enum uio_seg segflg)
{
	vnode_t vp;
	struct vnode_attr va;
	int error;
	struct nameidata nd;
	int follow;
	kauth_action_t action;

	AUDIT_ARG(owner, uid, gid);

	follow = (flag & AT_SYMLINK_NOFOLLOW) ? NOFOLLOW : FOLLOW;
	NDINIT(&nd, LOOKUP, OP_SETATTR, follow | AUDITVNPATH1, segflg,
	    path, ctx);
	error = nameiat(&nd, fd);
	if (error)
		return (error);
	vp = nd.ni_vp;

	nameidone(&nd);

	VATTR_INIT(&va);
	if (uid != (uid_t)VNOVAL)
		VATTR_SET(&va, va_uid, uid);
	if (gid != (gid_t)VNOVAL)
		VATTR_SET(&va, va_gid, gid);

#if CONFIG_MACF
	error = mac_vnode_check_setowner(ctx, vp, uid, gid);
	if (error)
		goto out;
#endif

	/* preflight and authorize attribute changes */
	if ((error = vnode_authattr(vp, &va, &action, ctx)) != 0)
		goto out;
	if (action && ((error = vnode_authorize(vp, NULL, action, ctx)) != 0))
		goto out;
	error = vnode_setattr(vp, &va, ctx);

#if CONFIG_MACF
	if (error == 0)
		mac_vnode_notify_setowner(ctx, vp, uid, gid);
#endif

out:
	/*
	 * EACCES is only allowed from namei(); permissions failure should
	 * return EPERM, so we need to translate the error code.
	 */
	if (error == EACCES)
		error = EPERM;

	vnode_put(vp);
	return (error);
}