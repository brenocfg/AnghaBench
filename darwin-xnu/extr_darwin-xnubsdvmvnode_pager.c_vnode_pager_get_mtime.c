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
struct timespec {int dummy; } ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  ubc_get_cs_mtime (struct vnode*,struct timespec*) ; 
 int /*<<< orphan*/  vfs_context_current () ; 
 int /*<<< orphan*/  vnode_mtime (struct vnode*,struct timespec*,int /*<<< orphan*/ ) ; 

kern_return_t
vnode_pager_get_mtime(
	struct vnode	*vp,
	struct timespec	*current_mtime,
	struct timespec	*cs_mtime)
{
	vnode_mtime(vp, current_mtime, vfs_context_current());
	if (cs_mtime != NULL) {
		ubc_get_cs_mtime(vp, cs_mtime);
	}
	return KERN_SUCCESS;
}