#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct fb_info {struct drm_fb_helper* par; } ;
struct fb_cmap {int* red; int* green; int* blue; int* transp; int start; int len; } ;
struct drm_fb_helper {int crtc_count; TYPE_2__* crtc_info; } ;
struct drm_crtc_helper_funcs {int /*<<< orphan*/  (* load_lut ) (struct drm_crtc*) ;} ;
struct drm_crtc {struct drm_crtc_helper_funcs* helper_private; } ;
struct TYPE_3__ {struct drm_crtc* crtc; } ;
struct TYPE_4__ {TYPE_1__ mode_set; } ;

/* Variables and functions */
 int setcolreg (struct drm_crtc*,int,int,int,int /*<<< orphan*/ ,struct fb_info*) ; 
 int /*<<< orphan*/  stub1 (struct drm_crtc*) ; 

int drm_fb_helper_setcmap(struct fb_cmap *cmap, struct fb_info *info)
{
	struct drm_fb_helper *fb_helper = info->par;
	struct drm_crtc_helper_funcs *crtc_funcs;
	u16 *red, *green, *blue, *transp;
	struct drm_crtc *crtc;
	int i, j, rc = 0;
	int start;

	for (i = 0; i < fb_helper->crtc_count; i++) {
		crtc = fb_helper->crtc_info[i].mode_set.crtc;
		crtc_funcs = crtc->helper_private;

		red = cmap->red;
		green = cmap->green;
		blue = cmap->blue;
		transp = cmap->transp;
		start = cmap->start;

		for (j = 0; j < cmap->len; j++) {
			u16 hred, hgreen, hblue, htransp = 0xffff;

			hred = *red++;
			hgreen = *green++;
			hblue = *blue++;

			if (transp)
				htransp = *transp++;

			rc = setcolreg(crtc, hred, hgreen, hblue, start++, info);
			if (rc)
				return rc;
		}
		crtc_funcs->load_lut(crtc);
	}
	return rc;
}