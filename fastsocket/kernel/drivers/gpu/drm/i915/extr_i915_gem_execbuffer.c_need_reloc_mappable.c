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
struct drm_i915_gem_object {struct drm_i915_gem_exec_object2* exec_entry; } ;
struct drm_i915_gem_exec_object2 {scalar_t__ relocation_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  use_cpu_reloc (struct drm_i915_gem_object*) ; 

__attribute__((used)) static int
need_reloc_mappable(struct drm_i915_gem_object *obj)
{
	struct drm_i915_gem_exec_object2 *entry = obj->exec_entry;
	return entry->relocation_count && !use_cpu_reloc(obj);
}