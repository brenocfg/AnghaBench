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
struct null_mount {int /*<<< orphan*/  nullm_lock; } ;

/* Variables and functions */
 struct null_mount* MOUNTTONULLMOUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int nullfs_isspecialvp (struct vnode*) ; 
 int /*<<< orphan*/  vnode_mount (struct vnode*) ; 

__attribute__((used)) static int
nullfs_checkspecialvp(struct vnode* vp)
{
	int result = 0;
	struct null_mount * null_mp;

	null_mp = MOUNTTONULLMOUNT(vnode_mount(vp));

	lck_mtx_lock(&null_mp->nullm_lock);
	result = (nullfs_isspecialvp(vp));
	lck_mtx_unlock(&null_mp->nullm_lock);

	return result;
}