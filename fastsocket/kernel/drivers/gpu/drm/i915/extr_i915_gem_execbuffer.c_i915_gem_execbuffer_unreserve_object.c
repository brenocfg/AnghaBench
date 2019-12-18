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
struct drm_i915_gem_object {struct drm_i915_gem_exec_object2* exec_entry; int /*<<< orphan*/  gtt_space; } ;
struct drm_i915_gem_exec_object2 {int flags; } ;

/* Variables and functions */
 int __EXEC_OBJECT_HAS_FENCE ; 
 int __EXEC_OBJECT_HAS_PIN ; 
 int /*<<< orphan*/  i915_gem_object_unpin (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_fence (struct drm_i915_gem_object*) ; 

__attribute__((used)) static void
i915_gem_execbuffer_unreserve_object(struct drm_i915_gem_object *obj)
{
	struct drm_i915_gem_exec_object2 *entry;

	if (!obj->gtt_space)
		return;

	entry = obj->exec_entry;

	if (entry->flags & __EXEC_OBJECT_HAS_FENCE)
		i915_gem_object_unpin_fence(obj);

	if (entry->flags & __EXEC_OBJECT_HAS_PIN)
		i915_gem_object_unpin(obj);

	entry->flags &= ~(__EXEC_OBJECT_HAS_FENCE | __EXEC_OBJECT_HAS_PIN);
}