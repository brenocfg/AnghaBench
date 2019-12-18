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
struct null_mount {struct vnode* nullm_secondvp; struct vnode* nullm_rootvp; } ;

/* Variables and functions */
 struct null_mount* MOUNTTONULLMOUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_mount (struct vnode*) ; 

__attribute__((used)) static int
nullfs_isspecialvp(struct vnode * vp)
{
	struct null_mount * null_mp;

	null_mp = MOUNTTONULLMOUNT(vnode_mount(vp));

	/* only check for root and second here, third is special in a different way,
	 * related only to lookup and readdir */
	if (vp && (vp == null_mp->nullm_rootvp || vp == null_mp->nullm_secondvp)) {
		return 1;
	}
	return 0;
}