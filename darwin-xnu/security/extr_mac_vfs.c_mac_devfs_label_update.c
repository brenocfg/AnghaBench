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
struct mount {int dummy; } ;
struct devnode {int /*<<< orphan*/  dn_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_PERFORM (int /*<<< orphan*/ ,struct mount*,struct devnode*,int /*<<< orphan*/ ,struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devfs_label_update ; 
 int /*<<< orphan*/  mac_device_enforce ; 

void
mac_devfs_label_update(struct mount *mp, struct devnode *de,
    struct vnode *vp)
{
#if SECURITY_MAC_CHECK_ENFORCE
	/* 21167099 - only check if we allow write */
	if (!mac_device_enforce)
		return;
#endif

	MAC_PERFORM(devfs_label_update, mp, de, de->dn_label, vp,
	    vp->v_label);
}