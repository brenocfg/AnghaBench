#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
struct vnode_attr {scalar_t__ va_parentid; } ;
typedef  TYPE_1__* mount_t ;
typedef  int /*<<< orphan*/  ino64_t ;
struct TYPE_4__ {int mnt_kern_flag; } ;

/* Variables and functions */
 int ENOENT ; 
 int MNTK_PATH_FROM_ID ; 
 int /*<<< orphan*/  VATTR_INIT (struct vnode_attr*) ; 
 int /*<<< orphan*/  VATTR_IS_SUPPORTED (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VATTR_WANTED (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int VFS_VGET (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va_parentid ; 
 int vnode_get (scalar_t__) ; 
 int vnode_getattr (scalar_t__,struct vnode_attr*,int /*<<< orphan*/ ) ; 
 TYPE_1__* vnode_mount (scalar_t__) ; 
 scalar_t__ vnode_parent (scalar_t__) ; 

__attribute__((used)) static int
null_get_lowerparent(vnode_t lvp, vnode_t * dvpp, vfs_context_t ctx)
{
	int error = 0;
	struct vnode_attr va;
	mount_t mp  = vnode_mount(lvp);
	vnode_t dvp = vnode_parent(lvp);

	if (dvp) {
		error = vnode_get(dvp);
		goto end;
	}

	error = ENOENT;
	if (!(mp->mnt_kern_flag & MNTK_PATH_FROM_ID)) {
		goto end;
	}

	VATTR_INIT(&va);
	VATTR_WANTED(&va, va_parentid);

	error = vnode_getattr(lvp, &va, ctx);

	if (error || !VATTR_IS_SUPPORTED(&va, va_parentid)) {
		goto end;
	}

	error = VFS_VGET(mp, (ino64_t)va.va_parentid, &dvp, ctx);

end:
	if (error == 0) {
		*dvpp = dvp;
	}
	return error;
}