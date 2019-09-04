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
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  enum uio_seg { ____Placeholder_uio_seg } uio_seg ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int unlinkat_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

int
unlink1(vfs_context_t ctx, vnode_t start_dvp, user_addr_t path_arg,
    enum uio_seg segflg, int unlink_flags)
{
	return (unlinkat_internal(ctx, AT_FDCWD, start_dvp, path_arg, segflg,
	    unlink_flags));
}