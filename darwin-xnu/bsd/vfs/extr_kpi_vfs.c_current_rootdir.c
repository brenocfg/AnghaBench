#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  struct vnode* vnode_t ;
struct vnode {int dummy; } ;
typedef  TYPE_2__* proc_t ;
struct TYPE_5__ {TYPE_1__* p_fd; } ;
struct TYPE_4__ {struct vnode* fd_rdir; } ;

/* Variables and functions */
 TYPE_2__* current_proc () ; 
 scalar_t__ vnode_getwithref (struct vnode*) ; 

vnode_t 
current_rootdir(void)
{
	proc_t proc = current_proc();
	struct vnode * vp ;

	if ( (vp = proc->p_fd->fd_rdir) ) {
	        if ( (vnode_getwithref(vp)) )
		        return (NULL);
	}
	return vp;
}