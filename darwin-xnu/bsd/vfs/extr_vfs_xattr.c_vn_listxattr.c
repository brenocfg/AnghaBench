#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int /*<<< orphan*/  uio_t ;
struct TYPE_8__ {int v_flag; } ;

/* Variables and functions */
 int ENOTSUP ; 
 int EPERM ; 
 int /*<<< orphan*/  KAUTH_VNODE_READ_EXTATTRIBUTES ; 
 int VISNAMEDSTREAM ; 
 int VNOP_LISTXATTR (TYPE_1__*,int /*<<< orphan*/ ,size_t*,int,int /*<<< orphan*/ ) ; 
 int XATTR_NODEFAULT ; 
 int XATTR_NOSECURITY ; 
 int /*<<< orphan*/  XATTR_VNODE_SUPPORTED (TYPE_1__*) ; 
 int default_listxattr (TYPE_1__*,int /*<<< orphan*/ ,size_t*,int,int /*<<< orphan*/ ) ; 
 int mac_vnode_check_listextattr (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int vnode_authorize (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
vn_listxattr(vnode_t vp, uio_t uio, size_t *size, int options, vfs_context_t context)
{
	int error;

	if (!XATTR_VNODE_SUPPORTED(vp)) {
		return (EPERM);
	}
#if NAMEDSTREAMS
	/* listxattr calls are not allowed for streams. */
	if (vp->v_flag & VISNAMEDSTREAM) {
		return (EPERM);
	}
#endif

	if (!(options & XATTR_NOSECURITY)) {
#if CONFIG_MACF
		error = mac_vnode_check_listextattr(context, vp);
		if (error)
			goto out;
#endif /* MAC */

		error = vnode_authorize(vp, NULL, KAUTH_VNODE_READ_EXTATTRIBUTES, context);
		if (error)
			goto out;
	}

	error = VNOP_LISTXATTR(vp, uio, size, options, context);
	if (error == ENOTSUP && !(options & XATTR_NODEFAULT)) {
		/*
		 * A filesystem may keep some but not all EAs natively, in which case
		 * the native EA names will have been uiomove-d out (or *size updated)
		 * and the default_listxattr here will finish the job.  
		 */
		error = default_listxattr(vp, uio, size, options, context);
	}
out:
	return (error);
}