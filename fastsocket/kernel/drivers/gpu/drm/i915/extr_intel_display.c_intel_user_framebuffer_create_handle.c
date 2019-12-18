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
struct intel_framebuffer {struct drm_i915_gem_object* obj; } ;
struct drm_i915_gem_object {int /*<<< orphan*/  base; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_file {int dummy; } ;

/* Variables and functions */
 int drm_gem_handle_create (struct drm_file*,int /*<<< orphan*/ *,unsigned int*) ; 
 struct intel_framebuffer* to_intel_framebuffer (struct drm_framebuffer*) ; 

__attribute__((used)) static int intel_user_framebuffer_create_handle(struct drm_framebuffer *fb,
						struct drm_file *file,
						unsigned int *handle)
{
	struct intel_framebuffer *intel_fb = to_intel_framebuffer(fb);
	struct drm_i915_gem_object *obj = intel_fb->obj;

	return drm_gem_handle_create(file, &obj->base, handle);
}