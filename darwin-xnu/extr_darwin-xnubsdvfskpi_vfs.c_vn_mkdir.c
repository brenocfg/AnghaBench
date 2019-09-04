#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vfs_context_t ;
struct vnode_attr {int dummy; } ;
struct vnode {int dummy; } ;
struct TYPE_2__ {scalar_t__ cn_nameiop; } ;
struct nameidata {TYPE_1__ ni_cnd; } ;

/* Variables and functions */
 scalar_t__ CREATE ; 
 int VNOP_COMPOUND_MKDIR (struct vnode*,struct vnode**,struct nameidata*,struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int VNOP_MKDIR (struct vnode*,struct vnode**,TYPE_1__*,struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ vnode_compound_mkdir_available (struct vnode*) ; 

int
vn_mkdir(struct vnode *dvp, struct vnode **vpp, struct nameidata *ndp,
           struct vnode_attr *vap, vfs_context_t ctx)
{
	if (ndp->ni_cnd.cn_nameiop != CREATE) {
		panic("Non-CREATE nameiop in vn_mkdir()?");
	}

	if (vnode_compound_mkdir_available(dvp)) {
		return VNOP_COMPOUND_MKDIR(dvp, vpp, ndp, vap, ctx);
	} else {
		return VNOP_MKDIR(dvp, vpp, &ndp->ni_cnd, vap, ctx);
	}
}