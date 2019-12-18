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
typedef  int u32 ;
struct nv50_mast {int dummy; } ;
struct nouveau_crtc {int index; } ;
struct nouveau_connector {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_display_mode {int flags; int htotal; int hsync_end; int hsync_start; int hdisplay; int vtotal; int vsync_end; int vsync_start; int vdisplay; int clock; } ;
struct drm_crtc {int /*<<< orphan*/  fb; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_DBLSCAN ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 scalar_t__ NVD0_DISP_MAST_CLASS ; 
 int /*<<< orphan*/  evo_data (int*,int) ; 
 int /*<<< orphan*/  evo_kick (int*,struct nv50_mast*) ; 
 int /*<<< orphan*/  evo_mthd (int*,int,int) ; 
 int* evo_wait (struct nv50_mast*,int) ; 
 struct nouveau_crtc* nouveau_crtc (struct drm_crtc*) ; 
 struct nouveau_connector* nouveau_crtc_connector_get (struct nouveau_crtc*) ; 
 int /*<<< orphan*/  nv50_crtc_set_color_vibrance (struct nouveau_crtc*,int) ; 
 int /*<<< orphan*/  nv50_crtc_set_dither (struct nouveau_crtc*,int) ; 
 int /*<<< orphan*/  nv50_crtc_set_image (struct nouveau_crtc*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  nv50_crtc_set_scale (struct nouveau_crtc*,int) ; 
 int nv50_crtc_swap_fbs (struct drm_crtc*,struct drm_framebuffer*) ; 
 struct nv50_mast* nv50_mast (int /*<<< orphan*/ ) ; 
 scalar_t__ nv50_vers (struct nv50_mast*) ; 

__attribute__((used)) static int
nv50_crtc_mode_set(struct drm_crtc *crtc, struct drm_display_mode *umode,
		   struct drm_display_mode *mode, int x, int y,
		   struct drm_framebuffer *old_fb)
{
	struct nv50_mast *mast = nv50_mast(crtc->dev);
	struct nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
	struct nouveau_connector *nv_connector;
	u32 ilace = (mode->flags & DRM_MODE_FLAG_INTERLACE) ? 2 : 1;
	u32 vscan = (mode->flags & DRM_MODE_FLAG_DBLSCAN) ? 2 : 1;
	u32 hactive, hsynce, hbackp, hfrontp, hblanke, hblanks;
	u32 vactive, vsynce, vbackp, vfrontp, vblanke, vblanks;
	u32 vblan2e = 0, vblan2s = 1;
	u32 *push;
	int ret;

	hactive = mode->htotal;
	hsynce  = mode->hsync_end - mode->hsync_start - 1;
	hbackp  = mode->htotal - mode->hsync_end;
	hblanke = hsynce + hbackp;
	hfrontp = mode->hsync_start - mode->hdisplay;
	hblanks = mode->htotal - hfrontp - 1;

	vactive = mode->vtotal * vscan / ilace;
	vsynce  = ((mode->vsync_end - mode->vsync_start) * vscan / ilace) - 1;
	vbackp  = (mode->vtotal - mode->vsync_end) * vscan / ilace;
	vblanke = vsynce + vbackp;
	vfrontp = (mode->vsync_start - mode->vdisplay) * vscan / ilace;
	vblanks = vactive - vfrontp - 1;
	if (mode->flags & DRM_MODE_FLAG_INTERLACE) {
		vblan2e = vactive + vsynce + vbackp;
		vblan2s = vblan2e + (mode->vdisplay * vscan / ilace);
		vactive = (vactive * 2) + 1;
	}

	ret = nv50_crtc_swap_fbs(crtc, old_fb);
	if (ret)
		return ret;

	push = evo_wait(mast, 64);
	if (push) {
		if (nv50_vers(mast) < NVD0_DISP_MAST_CLASS) {
			evo_mthd(push, 0x0804 + (nv_crtc->index * 0x400), 2);
			evo_data(push, 0x00800000 | mode->clock);
			evo_data(push, (ilace == 2) ? 2 : 0);
			evo_mthd(push, 0x0810 + (nv_crtc->index * 0x400), 6);
			evo_data(push, 0x00000000);
			evo_data(push, (vactive << 16) | hactive);
			evo_data(push, ( vsynce << 16) | hsynce);
			evo_data(push, (vblanke << 16) | hblanke);
			evo_data(push, (vblanks << 16) | hblanks);
			evo_data(push, (vblan2e << 16) | vblan2s);
			evo_mthd(push, 0x082c + (nv_crtc->index * 0x400), 1);
			evo_data(push, 0x00000000);
			evo_mthd(push, 0x0900 + (nv_crtc->index * 0x400), 2);
			evo_data(push, 0x00000311);
			evo_data(push, 0x00000100);
		} else {
			evo_mthd(push, 0x0410 + (nv_crtc->index * 0x300), 6);
			evo_data(push, 0x00000000);
			evo_data(push, (vactive << 16) | hactive);
			evo_data(push, ( vsynce << 16) | hsynce);
			evo_data(push, (vblanke << 16) | hblanke);
			evo_data(push, (vblanks << 16) | hblanks);
			evo_data(push, (vblan2e << 16) | vblan2s);
			evo_mthd(push, 0x042c + (nv_crtc->index * 0x300), 1);
			evo_data(push, 0x00000000); /* ??? */
			evo_mthd(push, 0x0450 + (nv_crtc->index * 0x300), 3);
			evo_data(push, mode->clock * 1000);
			evo_data(push, 0x00200000); /* ??? */
			evo_data(push, mode->clock * 1000);
			evo_mthd(push, 0x04d0 + (nv_crtc->index * 0x300), 2);
			evo_data(push, 0x00000311);
			evo_data(push, 0x00000100);
		}

		evo_kick(push, mast);
	}

	nv_connector = nouveau_crtc_connector_get(nv_crtc);
	nv50_crtc_set_dither(nv_crtc, false);
	nv50_crtc_set_scale(nv_crtc, false);
	nv50_crtc_set_color_vibrance(nv_crtc, false);
	nv50_crtc_set_image(nv_crtc, crtc->fb, x, y, false);
	return 0;
}