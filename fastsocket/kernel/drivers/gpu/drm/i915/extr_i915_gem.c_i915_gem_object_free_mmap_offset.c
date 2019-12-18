#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  map; } ;
struct TYPE_4__ {TYPE_1__ map_list; } ;
struct drm_i915_gem_object {TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_free_mmap_offset (TYPE_2__*) ; 

__attribute__((used)) static void i915_gem_object_free_mmap_offset(struct drm_i915_gem_object *obj)
{
	if (!obj->base.map_list.map)
		return;

	drm_gem_free_mmap_offset(&obj->base);
}