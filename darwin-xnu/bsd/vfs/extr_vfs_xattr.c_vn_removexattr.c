#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
struct TYPE_11__ {int v_flag; } ;

/* Variables and functions */
 int EJUSTRETURN ; 
 int ENOATTR ; 
 int ENOTSUP ; 
 int EPERM ; 
 int /*<<< orphan*/  KAUTH_VNODE_WRITE_EXTATTRIBUTES ; 
 int MNT_MULTILABEL ; 
 int VISNAMEDSTREAM ; 
 int VNOP_REMOVEXATTR (TYPE_1__*,char const*,int,int /*<<< orphan*/ ) ; 
 int XATTR_NODEFAULT ; 
 int XATTR_NOSECURITY ; 
 int /*<<< orphan*/  XATTR_VNODE_SUPPORTED (TYPE_1__*) ; 
 int default_removexattr (TYPE_1__*,char const*,int,int /*<<< orphan*/ ) ; 
 int mac_vnode_check_deleteextattr (int /*<<< orphan*/ ,TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  mac_vnode_label_update_extattr (int /*<<< orphan*/ ,TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  mac_vnode_notify_deleteextattr (int /*<<< orphan*/ ,TYPE_1__*,char const*) ; 
 int vfs_flags (int /*<<< orphan*/ ) ; 
 int vnode_authorize (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_mount (TYPE_1__*) ; 
 int xattr_validatename (char const*) ; 

int
vn_removexattr(vnode_t vp, const char * name, int options, vfs_context_t context)
{
	int error;

	if (!XATTR_VNODE_SUPPORTED(vp)) {
		return (EPERM);
	}
#if NAMEDSTREAMS
	/* removexattr calls are not allowed for streams. */
	if (vp->v_flag & VISNAMEDSTREAM) {
		error = EPERM;
		goto out;
	}
#endif
	if ((error = xattr_validatename(name))) {
		return (error);
	}
	if (!(options & XATTR_NOSECURITY)) {
#if CONFIG_MACF
		error = mac_vnode_check_deleteextattr(context, vp, name);
		if (error)
			goto out;
#endif /* MAC */
		error = vnode_authorize(vp, NULL, KAUTH_VNODE_WRITE_EXTATTRIBUTES, context);
		if (error)
			goto out;
	}
	error = VNOP_REMOVEXATTR(vp, name, options, context);
	if (error == ENOTSUP && !(options & XATTR_NODEFAULT)) {
		/*
		 * A filesystem may keep some EAs natively and return ENOTSUP for others.
		 */
		error = default_removexattr(vp, name, options, context);
#ifdef DUAL_EAS
	} else if (error == EJUSTRETURN) {
		/*
		 * EJUSTRETURN is from a filesystem which keeps this xattr natively as well
		 * as in a dot-underscore file.  EJUSTRETURN means the filesytem did remove
		 * a native xattr, so failure to find it in a DU file during
		 * default_removexattr should not be considered an error.
		 */
		error = default_removexattr(vp, name, options, context);
		if (error == ENOATTR)
			error = 0;
#endif /* DUAL_EAS */
	}
#if CONFIG_MACF
	if ((error == 0) && !(options & XATTR_NOSECURITY)) {
		mac_vnode_notify_deleteextattr(context, vp, name);
		if (vfs_flags(vnode_mount(vp)) & MNT_MULTILABEL)
			mac_vnode_label_update_extattr(vnode_mount(vp), vp, name);
	}
#endif
out:
	return (error);
}