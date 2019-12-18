#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int shrinker_no_lock_stealing; } ;
struct drm_i915_private {TYPE_2__ mm; } ;
struct TYPE_5__ {scalar_t__ map; } ;
struct TYPE_8__ {int size; TYPE_1__ map_list; TYPE_3__* dev; } ;
struct drm_i915_gem_object {TYPE_4__ base; } ;
struct TYPE_7__ {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int ENOSPC ; 
 int PAGE_SHIFT ; 
 int drm_gem_create_mmap_offset (TYPE_4__*) ; 
 int /*<<< orphan*/  i915_gem_purge (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  i915_gem_shrink_all (struct drm_i915_private*) ; 

__attribute__((used)) static int i915_gem_object_create_mmap_offset(struct drm_i915_gem_object *obj)
{
	struct drm_i915_private *dev_priv = obj->base.dev->dev_private;
	int ret;

	if (obj->base.map_list.map)
		return 0;

	dev_priv->mm.shrinker_no_lock_stealing = true;

	ret = drm_gem_create_mmap_offset(&obj->base);
	if (ret != -ENOSPC)
		goto out;

	/* Badly fragmented mmap space? The only way we can recover
	 * space is by destroying unwanted objects. We can't randomly release
	 * mmap_offsets as userspace expects them to be persistent for the
	 * lifetime of the objects. The closest we can is to release the
	 * offsets on purgeable objects by truncating it and marking it purged,
	 * which prevents userspace from ever using that object again.
	 */
	i915_gem_purge(dev_priv, obj->base.size >> PAGE_SHIFT);
	ret = drm_gem_create_mmap_offset(&obj->base);
	if (ret != -ENOSPC)
		goto out;

	i915_gem_shrink_all(dev_priv);
	ret = drm_gem_create_mmap_offset(&obj->base);
out:
	dev_priv->mm.shrinker_no_lock_stealing = false;

	return ret;
}