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
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
struct vnode_attr {int dummy; } ;
struct componentname {TYPE_1__* cn_ndp; } ;
struct TYPE_2__ {int ni_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  KAUTH_VNODE_ADD_FILE ; 
 int NAMEI_UNFINISHED ; 
 int lookup_validate_creation_path (TYPE_1__*) ; 
 int mac_vnode_check_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct componentname*,struct vnode_attr*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int vnode_authorize (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
vn_authorize_create(vnode_t dvp, struct componentname *cnp, struct vnode_attr *vap, vfs_context_t ctx, void *reserved)
{
#if !CONFIG_MACF
#pragma unused(vap)
#endif
	/* Creation case */
	int error;

	if (cnp->cn_ndp == NULL) {
		panic("NULL cn_ndp");
	}
	if (reserved != NULL) {
		panic("reserved not NULL.");
	}

	/* Only validate path for creation if we didn't do a complete lookup */
	if (cnp->cn_ndp->ni_flag & NAMEI_UNFINISHED) {
		error = lookup_validate_creation_path(cnp->cn_ndp);
		if (error)
			return (error);
	}

#if CONFIG_MACF
	error = mac_vnode_check_create(ctx, dvp, cnp, vap);
	if (error)
		return (error);
#endif /* CONFIG_MACF */

	return (vnode_authorize(dvp, NULL, KAUTH_VNODE_ADD_FILE, ctx));
}