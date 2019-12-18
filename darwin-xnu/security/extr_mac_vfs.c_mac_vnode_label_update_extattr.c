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
struct mount {int /*<<< orphan*/  mnt_mntlabel; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_PERFORM (int /*<<< orphan*/ ,struct mount*,int /*<<< orphan*/ ,struct vnode*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  mac_label_vnodes ; 
 int /*<<< orphan*/  mac_vnode_enforce ; 
 int /*<<< orphan*/  vnode_label_update_extattr ; 
 int /*<<< orphan*/  vnode_lock (struct vnode*) ; 
 int /*<<< orphan*/  vnode_relabel (struct vnode*) ; 
 int /*<<< orphan*/  vnode_unlock (struct vnode*) ; 

void
mac_vnode_label_update_extattr(struct mount *mp, struct vnode *vp,
    const char *name)
{
	int error = 0;

#if SECURITY_MAC_CHECK_ENFORCE
	/* 21167099 - only check if we allow write */
	if (!mac_vnode_enforce)
		return;
#endif
	if (!mac_label_vnodes)
		return;

	MAC_PERFORM(vnode_label_update_extattr, mp, mp->mnt_mntlabel, vp,
		    vp->v_label, name);
	if (error == 0)
		return;

	vnode_lock(vp);
	vnode_relabel(vp);
	vnode_unlock(vp);
	return;
}