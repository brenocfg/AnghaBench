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
struct vnode_attr {int dummy; } ;
struct nameidata {int /*<<< orphan*/  ni_cnd; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int VNOP_COMPOUND_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct nameidata*,int /*<<< orphan*/ ,struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int VNOP_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vnode_compound_remove_available (int /*<<< orphan*/ ) ; 

int
vn_remove(vnode_t dvp, vnode_t *vpp, struct nameidata *ndp, int32_t flags, struct vnode_attr *vap, vfs_context_t ctx)
{
	if (vnode_compound_remove_available(dvp)) {
		return VNOP_COMPOUND_REMOVE(dvp, vpp, ndp, flags, vap, ctx);
	} else {
		return VNOP_REMOVE(dvp, *vpp, &ndp->ni_cnd, flags, ctx);
	}
}