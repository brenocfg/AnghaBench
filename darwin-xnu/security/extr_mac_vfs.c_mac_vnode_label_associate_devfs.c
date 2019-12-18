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
struct vnode {int /*<<< orphan*/  v_label; } ;
struct mount {int /*<<< orphan*/ * mnt_mntlabel; } ;
struct devnode {int /*<<< orphan*/  dn_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_PERFORM (int /*<<< orphan*/ ,struct mount*,int /*<<< orphan*/ *,struct devnode*,int /*<<< orphan*/ ,struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_device_enforce ; 
 int /*<<< orphan*/  vnode_label_associate_devfs ; 

void
mac_vnode_label_associate_devfs(struct mount *mp, struct devnode *de,
    struct vnode *vp)
{
#if SECURITY_MAC_CHECK_ENFORCE
	/* 21167099 - only check if we allow write */
	if (!mac_device_enforce)
		return;
#endif

	MAC_PERFORM(vnode_label_associate_devfs,
	    mp, mp ? mp->mnt_mntlabel : NULL,
	    de, de->dn_label,
	    vp, vp->v_label);
}