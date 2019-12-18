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
struct nouveau_framebuffer {int /*<<< orphan*/  nvbo; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_crtc {struct drm_framebuffer* fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTM_PL_FLAG_VRAM ; 
 int nouveau_bo_pin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_bo_unpin (int /*<<< orphan*/ ) ; 
 struct nouveau_framebuffer* nouveau_framebuffer (struct drm_framebuffer*) ; 

__attribute__((used)) static int
nv50_crtc_swap_fbs(struct drm_crtc *crtc, struct drm_framebuffer *old_fb)
{
	struct nouveau_framebuffer *nvfb = nouveau_framebuffer(crtc->fb);
	int ret;

	ret = nouveau_bo_pin(nvfb->nvbo, TTM_PL_FLAG_VRAM);
	if (ret)
		return ret;

	if (old_fb) {
		nvfb = nouveau_framebuffer(old_fb);
		nouveau_bo_unpin(nvfb->nvbo);
	}

	return 0;
}