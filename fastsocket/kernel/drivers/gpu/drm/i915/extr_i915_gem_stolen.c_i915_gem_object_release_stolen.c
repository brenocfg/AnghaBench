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
struct drm_i915_gem_object {int /*<<< orphan*/ * stolen; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mm_put_block (int /*<<< orphan*/ *) ; 

void
i915_gem_object_release_stolen(struct drm_i915_gem_object *obj)
{
	if (obj->stolen) {
		drm_mm_put_block(obj->stolen);
		obj->stolen = NULL;
	}
}