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
struct drm_i915_gem_object_ops {int /*<<< orphan*/  (* put_pages ) (struct drm_i915_gem_object*) ;} ;
struct drm_i915_gem_object {int /*<<< orphan*/ * pages; int /*<<< orphan*/  gtt_list; scalar_t__ pages_pin_count; int /*<<< orphan*/  gtt_space; struct drm_i915_gem_object_ops* ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 scalar_t__ i915_gem_object_is_purgeable (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_truncate (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct drm_i915_gem_object*) ; 

int
i915_gem_object_put_pages(struct drm_i915_gem_object *obj)
{
	const struct drm_i915_gem_object_ops *ops = obj->ops;

	if (obj->pages == NULL)
		return 0;

	BUG_ON(obj->gtt_space);

	if (obj->pages_pin_count)
		return -EBUSY;

	/* ->put_pages might need to allocate memory for the bit17 swizzle
	 * array, hence protect them from being reaped by removing them from gtt
	 * lists early. */
	list_del(&obj->gtt_list);

	ops->put_pages(obj);
	obj->pages = NULL;

	if (i915_gem_object_is_purgeable(obj))
		i915_gem_object_truncate(obj);

	return 0;
}