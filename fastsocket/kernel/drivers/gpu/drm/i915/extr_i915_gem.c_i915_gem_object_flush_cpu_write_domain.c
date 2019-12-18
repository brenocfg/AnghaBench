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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ write_domain; int /*<<< orphan*/  read_domains; int /*<<< orphan*/  dev; } ;
struct drm_i915_gem_object {TYPE_1__ base; } ;

/* Variables and functions */
 scalar_t__ I915_GEM_DOMAIN_CPU ; 
 int /*<<< orphan*/  i915_gem_chipset_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_clflush_object (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  trace_i915_gem_object_change_domain (struct drm_i915_gem_object*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
i915_gem_object_flush_cpu_write_domain(struct drm_i915_gem_object *obj)
{
	uint32_t old_write_domain;

	if (obj->base.write_domain != I915_GEM_DOMAIN_CPU)
		return;

	i915_gem_clflush_object(obj);
	i915_gem_chipset_flush(obj->base.dev);
	old_write_domain = obj->base.write_domain;
	obj->base.write_domain = 0;

	trace_i915_gem_object_change_domain(obj,
					    obj->base.read_domains,
					    old_write_domain);
}