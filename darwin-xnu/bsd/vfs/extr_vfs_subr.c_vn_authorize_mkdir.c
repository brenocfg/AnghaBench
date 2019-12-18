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
struct componentname {int /*<<< orphan*/ * cn_ndp; } ;

/* Variables and functions */
 int /*<<< orphan*/  KAUTH_VNODE_ADD_SUBDIRECTORY ; 
 int lookup_validate_creation_path (int /*<<< orphan*/ *) ; 
 int mac_vnode_check_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct componentname*,struct vnode_attr*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int vnode_authorize (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vnode_compound_mkdir_available (int /*<<< orphan*/ ) ; 

int
vn_authorize_mkdir(vnode_t dvp, struct componentname *cnp, struct vnode_attr *vap, vfs_context_t ctx, void *reserved)
{
#if !CONFIG_MACF
#pragma unused(vap)
#endif
	int error;

	if (reserved != NULL) {
		panic("reserved not NULL in vn_authorize_mkdir()");	
	}

	/* XXX A hack for now, to make shadow files work */
	if (cnp->cn_ndp == NULL) {
		return 0;
	}

	if (vnode_compound_mkdir_available(dvp)) {
		error = lookup_validate_creation_path(cnp->cn_ndp);
		if (error)
			goto out;
	}

#if CONFIG_MACF
	error = mac_vnode_check_create(ctx,
	    dvp, cnp, vap);
	if (error)
		goto out;
#endif

  	/* authorize addition of a directory to the parent */
  	if ((error = vnode_authorize(dvp, NULL, KAUTH_VNODE_ADD_SUBDIRECTORY, ctx)) != 0)
  		goto out;
 	
out:
	return error;
}