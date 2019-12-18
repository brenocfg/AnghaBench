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
struct componentname {int dummy; } ;
struct TYPE_8__ {scalar_t__ v_type; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTDIR ; 
 int /*<<< orphan*/  KAUTH_VNODE_DELETE ; 
 scalar_t__ VDIR ; 
 int mac_vnode_check_unlink (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,struct componentname*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int vnode_authorize (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
vn_authorize_rmdir(vnode_t dvp, vnode_t vp, struct componentname *cnp, vfs_context_t ctx, void *reserved)
{
#if CONFIG_MACF
	int error;
#else
#pragma unused(cnp)
#endif
	if (reserved != NULL) {
		panic("Non-NULL reserved argument to vn_authorize_rmdir()");
	}

	if (vp->v_type != VDIR) {
		/*
		 * rmdir only deals with directories
		 */
		return ENOTDIR;
	} 
	
	if (dvp == vp) {
		/*
		 * No rmdir "." please.
		 */
		return EINVAL;
	} 
	
#if CONFIG_MACF
	error = mac_vnode_check_unlink(ctx, dvp,
			vp, cnp);
	if (error)
		return error;
#endif

	return vnode_authorize(vp, dvp, KAUTH_VNODE_DELETE, ctx);
}