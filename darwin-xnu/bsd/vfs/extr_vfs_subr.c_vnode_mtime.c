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
struct timespec {int dummy; } ;
struct vnode_attr {struct timespec va_modify_time; } ;
typedef  int errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  VATTR_INIT (struct vnode_attr*) ; 
 int /*<<< orphan*/  VATTR_WANTED (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va_modify_time ; 
 int vnode_getattr (int /*<<< orphan*/ ,struct vnode_attr*,int /*<<< orphan*/ ) ; 

errno_t
vnode_mtime(vnode_t vp, struct timespec *mtime, vfs_context_t ctx)
{
	struct vnode_attr	va;
	int			error;

	VATTR_INIT(&va);
	VATTR_WANTED(&va, va_modify_time);
	error = vnode_getattr(vp, &va, ctx);
	if (!error)
		*mtime = va.va_modify_time;
	return error;
}