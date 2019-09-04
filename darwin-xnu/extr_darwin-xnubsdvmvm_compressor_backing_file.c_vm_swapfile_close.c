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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_USER_ADDR_T (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULLVP ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int unlink1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_kernel () ; 
 int /*<<< orphan*/  vnode_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_getwithref (int /*<<< orphan*/ ) ; 

void
vm_swapfile_close(uint64_t path_addr, vnode_t vp)
{
	vfs_context_t context = vfs_context_kernel();
	int error;

	vnode_getwithref(vp);
	vnode_close(vp, 0, context);
	
	error = unlink1(context, NULLVP, CAST_USER_ADDR_T(path_addr),
	    UIO_SYSSPACE, 0);

#if DEVELOPMENT || DEBUG
	if (error)
		printf("%s : unlink of %s failed with error %d", __FUNCTION__,
		    (char *)path_addr, error);
#endif
}