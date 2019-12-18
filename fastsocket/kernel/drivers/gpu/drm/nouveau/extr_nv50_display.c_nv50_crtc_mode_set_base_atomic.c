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
struct nouveau_crtc {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_crtc {int dummy; } ;
typedef  enum mode_set_atomic { ____Placeholder_mode_set_atomic } mode_set_atomic ;

/* Variables and functions */
 struct nouveau_crtc* nouveau_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  nv50_crtc_set_image (struct nouveau_crtc*,struct drm_framebuffer*,int,int,int) ; 
 int /*<<< orphan*/  nv50_display_flip_stop (struct drm_crtc*) ; 

__attribute__((used)) static int
nv50_crtc_mode_set_base_atomic(struct drm_crtc *crtc,
			       struct drm_framebuffer *fb, int x, int y,
			       enum mode_set_atomic state)
{
	struct nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
	nv50_display_flip_stop(crtc);
	nv50_crtc_set_image(nv_crtc, fb, x, y, true);
	return 0;
}