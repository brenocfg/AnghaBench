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
struct vnop_rmdir_args {int /*<<< orphan*/  a_context; int /*<<< orphan*/  a_cnp; int /*<<< orphan*/  a_vp; int /*<<< orphan*/  a_dvp; } ;
struct vnop_remove_args {int /*<<< orphan*/  a_context; scalar_t__ a_flags; int /*<<< orphan*/  a_cnp; int /*<<< orphan*/  a_vp; int /*<<< orphan*/  a_dvp; } ;

/* Variables and functions */
 int devfs_vnop_remove (struct vnop_remove_args*) ; 

__attribute__((used)) static int
devfs_rmdir(struct vnop_rmdir_args *ap)
	/* struct vnop_rmdir_args {
		struct vnode *a_dvp;
		struct vnode *a_vp;
		struct componentname *a_cnp;
		vfs_context_t a_context;
	} */
{
	struct vnop_remove_args ra;

	ra.a_dvp = ap->a_dvp;
	ra.a_vp = ap->a_vp;
	ra.a_cnp = ap->a_cnp;
	ra.a_flags = 0;		/* XXX */
	ra.a_context = ap->a_context;

	return devfs_vnop_remove(&ra);
}