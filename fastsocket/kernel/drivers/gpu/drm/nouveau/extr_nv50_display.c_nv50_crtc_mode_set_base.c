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
struct nouveau_drm {int dummy; } ;
struct nouveau_crtc {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_crtc {int /*<<< orphan*/  fb; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV_DEBUG (struct nouveau_drm*,char*) ; 
 struct nouveau_crtc* nouveau_crtc (struct drm_crtc*) ; 
 struct nouveau_drm* nouveau_drm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv50_crtc_set_image (struct nouveau_crtc*,int /*<<< orphan*/ ,int,int,int) ; 
 int nv50_crtc_swap_fbs (struct drm_crtc*,struct drm_framebuffer*) ; 
 int /*<<< orphan*/  nv50_display_flip_next (struct drm_crtc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nv50_display_flip_stop (struct drm_crtc*) ; 

__attribute__((used)) static int
nv50_crtc_mode_set_base(struct drm_crtc *crtc, int x, int y,
			struct drm_framebuffer *old_fb)
{
	struct nouveau_drm *drm = nouveau_drm(crtc->dev);
	struct nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
	int ret;

	if (!crtc->fb) {
		NV_DEBUG(drm, "No FB bound\n");
		return 0;
	}

	ret = nv50_crtc_swap_fbs(crtc, old_fb);
	if (ret)
		return ret;

	nv50_display_flip_stop(crtc);
	nv50_crtc_set_image(nv_crtc, crtc->fb, x, y, true);
	nv50_display_flip_next(crtc, crtc->fb, NULL, 1);
	return 0;
}