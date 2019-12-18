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
struct vnop_fsync_args {int /*<<< orphan*/  a_context; int /*<<< orphan*/  a_waitfor; int /*<<< orphan*/  a_vp; } ;

/* Variables and functions */
 int /*<<< orphan*/  VTONFS (int /*<<< orphan*/ ) ; 
 int nfs_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_thread (int /*<<< orphan*/ ) ; 

int
nfs_vnop_fsync(
	struct vnop_fsync_args /* {
		struct vnodeop_desc *a_desc;
		vnode_t a_vp;
		int a_waitfor;
		vfs_context_t a_context;
	} */ *ap)
{
	return (nfs_flush(VTONFS(ap->a_vp), ap->a_waitfor, vfs_context_thread(ap->a_context), 0));
}