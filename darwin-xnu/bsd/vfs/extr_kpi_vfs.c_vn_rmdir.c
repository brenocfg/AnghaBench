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
typedef  scalar_t__ vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
struct vnode_attr {int dummy; } ;
struct nameidata {int /*<<< orphan*/  ni_cnd; } ;

/* Variables and functions */
 scalar_t__ NULLVP ; 
 int VNOP_COMPOUND_RMDIR (scalar_t__,scalar_t__*,struct nameidata*,struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int VNOP_RMDIR (scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ vnode_compound_rmdir_available (scalar_t__) ; 

int
vn_rmdir(vnode_t dvp, vnode_t *vpp, struct nameidata *ndp, struct vnode_attr *vap, vfs_context_t ctx)
{
	if (vnode_compound_rmdir_available(dvp)) {
		return VNOP_COMPOUND_RMDIR(dvp, vpp, ndp, vap, ctx);
	} else {
		if (*vpp == NULLVP) {
			panic("NULL vp, but not a compound VNOP?");
		}
		if (vap != NULL) {
			panic("Non-NULL vap, but not a compound VNOP?");
		}
		return VNOP_RMDIR(dvp, *vpp, &ndp->ni_cnd, ctx);
	}
}