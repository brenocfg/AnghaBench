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
struct vnode_fsparam {int vnfs_vtype; char* vnfs_str; int vnfs_markroot; int /*<<< orphan*/  vnfs_flags; struct componentname* vnfs_cnp; scalar_t__ vnfs_filesize; scalar_t__ vnfs_rdev; scalar_t__ vnfs_marksystem; int /*<<< orphan*/  vnfs_vops; void* vnfs_fsnode; struct vnode* vnfs_dvp; struct mount* vnfs_mp; } ;
struct vnode {int dummy; } ;
struct null_node {int /*<<< orphan*/  null_myvid; struct vnode* null_vnode; } ;
struct mount {int dummy; } ;
struct componentname {int dummy; } ;
typedef  enum vtype { ____Placeholder_vtype } vtype ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FREE (struct null_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  VCREATESIZE ; 
 int VDIR ; 
 int /*<<< orphan*/  VNCREATE_FLAVOR ; 
 int /*<<< orphan*/  VNFS_ADDFSREF ; 
 int /*<<< orphan*/  VT_NULL ; 
 struct null_node* null_nodecreate (struct vnode*) ; 
 int /*<<< orphan*/  nullfs_vnodeop_p ; 
 int vnode_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vnode_fsparam*,struct vnode**) ; 
 int /*<<< orphan*/  vnode_settag (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_vid (struct vnode*) ; 
 int vnode_vtype (struct vnode*) ; 

int
null_getnewvnode(
    struct mount * mp, struct vnode * lowervp, struct vnode * dvp, struct vnode ** vpp, struct componentname * cnp, int root)
{
	struct vnode_fsparam vnfs_param;
	int error             = 0;
	enum vtype type       = VDIR;
	struct null_node * xp = null_nodecreate(lowervp);

	if (xp == NULL) {
		return ENOMEM;
	}

	if (lowervp) {
		type = vnode_vtype(lowervp);
	}

	vnfs_param.vnfs_mp         = mp;
	vnfs_param.vnfs_vtype      = type;
	vnfs_param.vnfs_str        = "nullfs";
	vnfs_param.vnfs_dvp        = dvp;
	vnfs_param.vnfs_fsnode     = (void *)xp;
	vnfs_param.vnfs_vops       = nullfs_vnodeop_p;
	vnfs_param.vnfs_markroot   = root;
	vnfs_param.vnfs_marksystem = 0;
	vnfs_param.vnfs_rdev       = 0;
	vnfs_param.vnfs_filesize   = 0; // set this to 0 since we should only be shadowing non-regular files
	vnfs_param.vnfs_cnp        = cnp;
	vnfs_param.vnfs_flags      = VNFS_ADDFSREF;

	error = vnode_create(VNCREATE_FLAVOR, VCREATESIZE, &vnfs_param, vpp);
	if (error == 0) {
		xp->null_vnode = *vpp;
		xp->null_myvid = vnode_vid(*vpp);
		vnode_settag(*vpp, VT_NULL);
	} else {
		FREE(xp, M_TEMP);
	}
	return error;
}