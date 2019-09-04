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
struct vnode {int dummy; } ;
struct proc {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK (int /*<<< orphan*/ ,struct proc*,struct vnode*,int /*<<< orphan*/ ,struct vnode*,int /*<<< orphan*/ ,struct vnode*) ; 
 int /*<<< orphan*/  proc_check_inherit_ipc_ports ; 

int
mac_proc_check_inherit_ipc_ports(struct proc *p, struct vnode *cur_vp, off_t cur_offset, struct vnode *img_vp, off_t img_offset, struct vnode *scriptvp)
{
	int error;

	MAC_CHECK(proc_check_inherit_ipc_ports, p, cur_vp, cur_offset, img_vp, img_offset, scriptvp);

	return (error);
}