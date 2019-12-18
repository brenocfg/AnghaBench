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
struct TYPE_2__ {scalar_t__ write_domain; } ;
struct drm_i915_gem_object {scalar_t__ cache_level; int /*<<< orphan*/  map_and_fenceable; TYPE_1__ base; } ;

/* Variables and functions */
 scalar_t__ I915_CACHE_NONE ; 
 scalar_t__ I915_GEM_DOMAIN_CPU ; 

__attribute__((used)) static inline int use_cpu_reloc(struct drm_i915_gem_object *obj)
{
	return (obj->base.write_domain == I915_GEM_DOMAIN_CPU ||
		!obj->map_and_fenceable ||
		obj->cache_level != I915_CACHE_NONE);
}