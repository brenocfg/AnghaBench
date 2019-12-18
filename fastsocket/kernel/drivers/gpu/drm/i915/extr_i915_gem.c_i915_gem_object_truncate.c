#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * filp; } ;
struct drm_i915_gem_object {int /*<<< orphan*/  madv; TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  __I915_MADV_PURGED ; 
 struct inode* file_inode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_object_free_mmap_offset (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  shmem_truncate_range (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
i915_gem_object_truncate(struct drm_i915_gem_object *obj)
{
	struct inode *inode;

	i915_gem_object_free_mmap_offset(obj);

	if (obj->base.filp == NULL)
		return;

	/* Our goal here is to return as much of the memory as
	 * is possible back to the system as we are called from OOM.
	 * To do this we must instruct the shmfs to drop all of its
	 * backing pages, *now*.
	 */
	inode = file_inode(obj->base.filp);
	shmem_truncate_range(inode, 0, (loff_t)-1);

	obj->madv = __I915_MADV_PURGED;
}