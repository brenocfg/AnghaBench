#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u_short ;
struct TYPE_9__ {int length; unsigned int offset; } ;
struct TYPE_8__ {int length; unsigned int offset; } ;
struct TYPE_7__ {int length; unsigned int offset; } ;
struct TYPE_10__ {int bits_per_pixel; TYPE_4__ blue; TYPE_3__ green; TYPE_2__ red; } ;
struct TYPE_6__ {scalar_t__ visual; } ;
struct fb_info {TYPE_5__ var; TYPE_1__ fix; struct da8xx_fb_par* par; } ;
struct da8xx_fb_par {unsigned int* pseudo_palette; scalar_t__ v_palette_base; } ;

/* Variables and functions */
 scalar_t__ FB_VISUAL_DIRECTCOLOR ; 

__attribute__((used)) static int fb_setcolreg(unsigned regno, unsigned red, unsigned green,
			      unsigned blue, unsigned transp,
			      struct fb_info *info)
{
	struct da8xx_fb_par *par = info->par;
	unsigned short *palette = (unsigned short *)par->v_palette_base;
	u_short pal;

	if (regno > 255)
		return 1;

	if (info->fix.visual == FB_VISUAL_DIRECTCOLOR)
		return 1;

	if (info->var.bits_per_pixel == 8) {
		red >>= 4;
		green >>= 8;
		blue >>= 12;

		pal = (red & 0x0f00);
		pal |= (green & 0x00f0);
		pal |= (blue & 0x000f);

		palette[regno] = pal;

	} else if ((info->var.bits_per_pixel == 16) && regno < 16) {
		red >>= (16 - info->var.red.length);
		red <<= info->var.red.offset;

		green >>= (16 - info->var.green.length);
		green <<= info->var.green.offset;

		blue >>= (16 - info->var.blue.length);
		blue <<= info->var.blue.offset;

		par->pseudo_palette[regno] = red | green | blue;

		palette[0] = 0x4000;
	}

	return 0;
}