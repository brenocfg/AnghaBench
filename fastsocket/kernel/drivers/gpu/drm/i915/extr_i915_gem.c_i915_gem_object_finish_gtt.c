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
typedef  int u32 ;
struct TYPE_2__ {int read_domains; int write_domain; } ;
struct drm_i915_gem_object {TYPE_1__ base; } ;

/* Variables and functions */
 int I915_GEM_DOMAIN_GTT ; 
 int /*<<< orphan*/  i915_gem_release_mmap (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  trace_i915_gem_object_change_domain (struct drm_i915_gem_object*,int,int) ; 

__attribute__((used)) static void i915_gem_object_finish_gtt(struct drm_i915_gem_object *obj)
{
	u32 old_write_domain, old_read_domains;

	/* Force a pagefault for domain tracking on next user access */
	i915_gem_release_mmap(obj);

	if ((obj->base.read_domains & I915_GEM_DOMAIN_GTT) == 0)
		return;

	/* Wait for any direct GTT access to complete */
	mb();

	old_read_domains = obj->base.read_domains;
	old_write_domain = obj->base.write_domain;

	obj->base.read_domains &= ~I915_GEM_DOMAIN_GTT;
	obj->base.write_domain &= ~I915_GEM_DOMAIN_GTT;

	trace_i915_gem_object_change_domain(obj,
					    old_read_domains,
					    old_write_domain);
}