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
struct vnode_attr {int va_vaflags; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  VATTR_INIT (struct vnode_attr*) ; 
 int /*<<< orphan*/  VATTR_SET (struct vnode_attr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va_data_size ; 
 int /*<<< orphan*/  vnode_setattr (int /*<<< orphan*/ ,struct vnode_attr*,int /*<<< orphan*/ ) ; 

errno_t
vnode_setsize(vnode_t vp, off_t size, int ioflag, vfs_context_t ctx)
{
	struct vnode_attr	va;

	VATTR_INIT(&va);
	VATTR_SET(&va, va_data_size, size);
	va.va_vaflags = ioflag & 0xffff;
	return(vnode_setattr(vp, &va, ctx));
}