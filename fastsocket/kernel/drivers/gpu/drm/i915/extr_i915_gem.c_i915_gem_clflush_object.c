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
struct drm_i915_gem_object {scalar_t__ cache_level; int /*<<< orphan*/ * pages; scalar_t__ stolen; } ;

/* Variables and functions */
 scalar_t__ I915_CACHE_NONE ; 
 int /*<<< orphan*/  drm_clflush_sg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_i915_gem_object_clflush (struct drm_i915_gem_object*) ; 

void
i915_gem_clflush_object(struct drm_i915_gem_object *obj)
{
	/* If we don't have a page list set up, then we're not pinned
	 * to GPU, and we can ignore the cache flush because it'll happen
	 * again at bind time.
	 */
	if (obj->pages == NULL)
		return;

	/*
	 * Stolen memory is always coherent with the GPU as it is explicitly
	 * marked as wc by the system, or the system is cache-coherent.
	 */
	if (obj->stolen)
		return;

	/* If the GPU is snooping the contents of the CPU cache,
	 * we do not need to manually clear the CPU cache lines.  However,
	 * the caches are only snooped when the render cache is
	 * flushed/invalidated.  As we always have to emit invalidations
	 * and flushes when moving into and out of the RENDER domain, correct
	 * snooping behaviour occurs naturally as the result of our domain
	 * tracking.
	 */
	if (obj->cache_level != I915_CACHE_NONE)
		return;

	trace_i915_gem_object_clflush(obj);

	drm_clflush_sg(obj->pages);
}