#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
struct nameidata {TYPE_1__* ni_vp; } ;
struct TYPE_5__ {scalar_t__ v_type; } ;

/* Variables and functions */
 int ENOTDIR ; 
 int /*<<< orphan*/  KAUTH_VNODE_SEARCH ; 
 scalar_t__ VDIR ; 
 int mac_vnode_check_chdir (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int namei (struct nameidata*) ; 
 int /*<<< orphan*/  nameidone (struct nameidata*) ; 
 int vnode_authorize (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_put (TYPE_1__*) ; 

__attribute__((used)) static int
change_dir(struct nameidata *ndp, vfs_context_t ctx)
{
	vnode_t vp;
	int error;

	if ((error = namei(ndp)))
		return (error);
	nameidone(ndp);
	vp = ndp->ni_vp;

	if (vp->v_type != VDIR) {
		vnode_put(vp);
		return (ENOTDIR);
	}

#if CONFIG_MACF
	error = mac_vnode_check_chdir(ctx, vp);
	if (error) {
		vnode_put(vp);
		return (error);
	}
#endif

	error = vnode_authorize(vp, NULL, KAUTH_VNODE_SEARCH, ctx);
	if (error) {
		vnode_put(vp);
		return (error);
	}

	return (error);
}