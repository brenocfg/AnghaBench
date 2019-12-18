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
typedef  int /*<<< orphan*/  vfs_context_t ;
struct vnode {int v_tag; } ;
struct mount {int dummy; } ;
struct fdescnode {int dummy; } ;
struct devnode {int dummy; } ;

/* Variables and functions */
 struct devnode* VTODN (struct vnode*) ; 
 struct fdescnode* VTOFDESC (struct vnode*) ; 
#define  VT_DEVFS 129 
#define  VT_FDESC 128 
 int /*<<< orphan*/  mac_vnode_enforce ; 
 int /*<<< orphan*/  mac_vnode_label_associate_devfs (struct mount*,struct devnode*,struct vnode*) ; 
 int mac_vnode_label_associate_extattr (struct mount*,struct vnode*) ; 
 int mac_vnode_label_associate_fdesc (struct mount*,struct fdescnode*,struct vnode*,int /*<<< orphan*/ ) ; 

int
mac_vnode_label_associate(struct mount *mp, struct vnode *vp, vfs_context_t ctx)
{
	struct devnode *dnp;
	struct fdescnode *fnp;
	int error = 0;

#if SECURITY_MAC_CHECK_ENFORCE
	/* 21167099 - only check if we allow write */
	if (!mac_vnode_enforce)
		return (error);
#endif

	/* XXX: should not inspect v_tag in kernel! */
	switch (vp->v_tag) {
	case VT_DEVFS:
		dnp = VTODN(vp);
		mac_vnode_label_associate_devfs(mp, dnp, vp);
		break;
	case VT_FDESC:
		fnp = VTOFDESC(vp);
		error = mac_vnode_label_associate_fdesc(mp, fnp, vp, ctx);
		break;
	default:
		error = mac_vnode_label_associate_extattr(mp, vp);
		break;
	}

	return (error);
}