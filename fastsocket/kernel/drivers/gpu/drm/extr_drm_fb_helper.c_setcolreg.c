#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_12__ {int length; int offset; } ;
struct TYPE_11__ {int length; int offset; } ;
struct TYPE_10__ {int length; int offset; } ;
struct TYPE_9__ {int length; int offset; } ;
struct TYPE_13__ {TYPE_5__ transp; TYPE_4__ blue; TYPE_3__ green; TYPE_2__ red; } ;
struct TYPE_8__ {scalar_t__ visual; } ;
struct fb_info {TYPE_6__ var; scalar_t__ pseudo_palette; TYPE_1__ fix; struct drm_fb_helper* par; } ;
struct drm_framebuffer {int bits_per_pixel; int depth; } ;
struct drm_fb_helper {TYPE_7__* funcs; struct drm_framebuffer* fb; } ;
struct drm_crtc {int dummy; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* gamma_set ) (struct drm_crtc*,int,int,int,int) ;int /*<<< orphan*/  (* gamma_get ) (struct drm_crtc*,int*,int*,int*,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FB_VISUAL_TRUECOLOR ; 
 int /*<<< orphan*/  stub1 (struct drm_crtc*,int,int,int,int) ; 
 int /*<<< orphan*/  stub2 (struct drm_crtc*,int*,int*,int*,int) ; 
 int /*<<< orphan*/  stub3 (struct drm_crtc*,int,int,int,int) ; 
 int /*<<< orphan*/  stub4 (struct drm_crtc*,int,int,int,int) ; 

__attribute__((used)) static int setcolreg(struct drm_crtc *crtc, u16 red, u16 green,
		     u16 blue, u16 regno, struct fb_info *info)
{
	struct drm_fb_helper *fb_helper = info->par;
	struct drm_framebuffer *fb = fb_helper->fb;
	int pindex;

	if (info->fix.visual == FB_VISUAL_TRUECOLOR) {
		u32 *palette;
		u32 value;
		/* place color in psuedopalette */
		if (regno > 16)
			return -EINVAL;
		palette = (u32 *)info->pseudo_palette;
		red >>= (16 - info->var.red.length);
		green >>= (16 - info->var.green.length);
		blue >>= (16 - info->var.blue.length);
		value = (red << info->var.red.offset) |
			(green << info->var.green.offset) |
			(blue << info->var.blue.offset);
		if (info->var.transp.length > 0) {
			u32 mask = (1 << info->var.transp.length) - 1;
			mask <<= info->var.transp.offset;
			value |= mask;
		}
		palette[regno] = value;
		return 0;
	}

	pindex = regno;

	if (fb->bits_per_pixel == 16) {
		pindex = regno << 3;

		if (fb->depth == 16 && regno > 63)
			return -EINVAL;
		if (fb->depth == 15 && regno > 31)
			return -EINVAL;

		if (fb->depth == 16) {
			u16 r, g, b;
			int i;
			if (regno < 32) {
				for (i = 0; i < 8; i++)
					fb_helper->funcs->gamma_set(crtc, red,
						green, blue, pindex + i);
			}

			fb_helper->funcs->gamma_get(crtc, &r,
						    &g, &b,
						    pindex >> 1);

			for (i = 0; i < 4; i++)
				fb_helper->funcs->gamma_set(crtc, r,
							    green, b,
							    (pindex >> 1) + i);
		}
	}

	if (fb->depth != 16)
		fb_helper->funcs->gamma_set(crtc, red, green, blue, pindex);
	return 0;
}