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
struct proc {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK (int /*<<< orphan*/ ,struct proc*,struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_proc_enforce ; 
 int /*<<< orphan*/  mac_vnode_enforce ; 
 int /*<<< orphan*/  vnode_find_sigs ; 

int
mac_vnode_find_sigs(struct proc *p, struct vnode *vp, off_t offset)
{
	int error;

#if SECURITY_MAC_CHECK_ENFORCE
	/* 21167099 - only check if we allow write */
	if (!mac_proc_enforce || !mac_vnode_enforce)
		return 0;
#endif

	MAC_CHECK(vnode_find_sigs, p, vp, offset, vp->v_label);

	return (error);
}