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
struct drm_i915_gem_object {scalar_t__ pin_count; int pin_mappable; int /*<<< orphan*/ * gtt_space; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 

void
i915_gem_object_unpin(struct drm_i915_gem_object *obj)
{
	BUG_ON(obj->pin_count == 0);
	BUG_ON(obj->gtt_space == NULL);

	if (--obj->pin_count == 0)
		obj->pin_mappable = false;
}