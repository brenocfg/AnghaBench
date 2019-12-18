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
struct radeon_framebuffer {scalar_t__ obj; } ;
struct drm_framebuffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_framebuffer_cleanup (struct drm_framebuffer*) ; 
 int /*<<< orphan*/  drm_gem_object_unreference_unlocked (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct radeon_framebuffer*) ; 
 struct radeon_framebuffer* to_radeon_framebuffer (struct drm_framebuffer*) ; 

__attribute__((used)) static void radeon_user_framebuffer_destroy(struct drm_framebuffer *fb)
{
	struct radeon_framebuffer *radeon_fb = to_radeon_framebuffer(fb);

	if (radeon_fb->obj) {
		drm_gem_object_unreference_unlocked(radeon_fb->obj);
	}
	drm_framebuffer_cleanup(fb);
	kfree(radeon_fb);
}