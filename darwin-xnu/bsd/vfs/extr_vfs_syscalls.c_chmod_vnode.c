#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
struct vnode_attr {int va_uid; int va_gid; int /*<<< orphan*/  va_acl; scalar_t__ va_mode; } ;
typedef  int /*<<< orphan*/  mode_t ;
typedef  int /*<<< orphan*/  kauth_action_t ;
struct TYPE_12__ {int v_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG (int /*<<< orphan*/ ,scalar_t__) ; 
 int EACCES ; 
 int EPERM ; 
 scalar_t__ VATTR_IS_ACTIVE (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int VISNAMEDSTREAM ; 
 int mac_vnode_check_setacl (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int mac_vnode_check_setmode (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int mac_vnode_check_setowner (int /*<<< orphan*/ ,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  mac_vnode_notify_setacl (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_vnode_notify_setmode (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_vnode_notify_setowner (int /*<<< orphan*/ ,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  mode ; 
 int /*<<< orphan*/  va_acl ; 
 int /*<<< orphan*/  va_gid ; 
 int /*<<< orphan*/  va_mode ; 
 int /*<<< orphan*/  va_uid ; 
 int vnode_authattr (TYPE_1__*,struct vnode_attr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vnode_authorize (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vnode_setattr (TYPE_1__*,struct vnode_attr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
chmod_vnode(vfs_context_t ctx, vnode_t vp, struct vnode_attr *vap)
{
	kauth_action_t action;
	int error;

	AUDIT_ARG(mode, vap->va_mode);
	/* XXX audit new args */

#if NAMEDSTREAMS
	/* chmod calls are not allowed for resource forks. */
	if (vp->v_flag & VISNAMEDSTREAM) {
		return (EPERM);
	}
#endif

#if CONFIG_MACF
	if (VATTR_IS_ACTIVE(vap, va_mode) &&
	    (error = mac_vnode_check_setmode(ctx, vp, (mode_t)vap->va_mode)) != 0)
		return (error);

	if (VATTR_IS_ACTIVE(vap, va_uid) || VATTR_IS_ACTIVE(vap, va_gid)) {
		if ((error = mac_vnode_check_setowner(ctx, vp,
		    VATTR_IS_ACTIVE(vap, va_uid) ? vap->va_uid : -1,
		    VATTR_IS_ACTIVE(vap, va_gid) ? vap->va_gid : -1)))
			return (error);
	}

	if (VATTR_IS_ACTIVE(vap, va_acl) &&
	    (error = mac_vnode_check_setacl(ctx, vp, vap->va_acl)))
		return (error);
#endif

 	/* make sure that the caller is allowed to set this security information */
	if (((error = vnode_authattr(vp, vap, &action, ctx)) != 0) ||
	    ((error = vnode_authorize(vp, NULL, action, ctx)) != 0)) {
		if (error == EACCES)
			error = EPERM;
		return(error);
	}

	if ((error = vnode_setattr(vp, vap, ctx)) != 0)
		return (error);

#if CONFIG_MACF
	if (VATTR_IS_ACTIVE(vap, va_mode))
		mac_vnode_notify_setmode(ctx, vp, (mode_t)vap->va_mode);

	if (VATTR_IS_ACTIVE(vap, va_uid) || VATTR_IS_ACTIVE(vap, va_gid))
		mac_vnode_notify_setowner(ctx, vp,
			VATTR_IS_ACTIVE(vap, va_uid) ? vap->va_uid : -1,
			VATTR_IS_ACTIVE(vap, va_gid) ? vap->va_gid : -1);

	if (VATTR_IS_ACTIVE(vap, va_acl))
		mac_vnode_notify_setacl(ctx, vp, vap->va_acl);
#endif

	return (error);
}