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
typedef  size_t u32 ;
struct TYPE_4__ {scalar_t__ visual; int /*<<< orphan*/  line_length; } ;
struct TYPE_3__ {int bits_per_pixel; int xres_virtual; int yres_virtual; } ;
struct fb_info {scalar_t__ state; int flags; TYPE_2__ fix; TYPE_1__ var; struct cirrusfb_info* par; } ;
struct fb_fillrect {size_t color; int width; int height; int dx; int dy; } ;
struct cirrusfb_info {size_t* pseudo_palette; int /*<<< orphan*/  regbase; } ;

/* Variables and functions */
 int FBINFO_HWACCEL_DISABLED ; 
 scalar_t__ FBINFO_STATE_RUNNING ; 
 scalar_t__ FB_VISUAL_TRUECOLOR ; 
 int /*<<< orphan*/  cfb_fillrect (struct fb_info*,struct fb_fillrect const*) ; 
 int /*<<< orphan*/  cirrusfb_RectFill (int /*<<< orphan*/ ,int,int,int,int,int,size_t,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (struct fb_fillrect*,struct fb_fillrect const*,int) ; 

__attribute__((used)) static void cirrusfb_fillrect(struct fb_info *info,
			      const struct fb_fillrect *region)
{
	struct fb_fillrect modded;
	int vxres, vyres;
	struct cirrusfb_info *cinfo = info->par;
	int m = info->var.bits_per_pixel;
	u32 color = (info->fix.visual == FB_VISUAL_TRUECOLOR) ?
		cinfo->pseudo_palette[region->color] : region->color;

	if (info->state != FBINFO_STATE_RUNNING)
		return;
	if (info->flags & FBINFO_HWACCEL_DISABLED) {
		cfb_fillrect(info, region);
		return;
	}

	vxres = info->var.xres_virtual;
	vyres = info->var.yres_virtual;

	memcpy(&modded, region, sizeof(struct fb_fillrect));

	if (!modded.width || !modded.height ||
	   modded.dx >= vxres || modded.dy >= vyres)
		return;

	if (modded.dx + modded.width  > vxres)
		modded.width  = vxres - modded.dx;
	if (modded.dy + modded.height > vyres)
		modded.height = vyres - modded.dy;

	cirrusfb_RectFill(cinfo->regbase,
			  info->var.bits_per_pixel,
			  (region->dx * m) / 8, region->dy,
			  (region->width * m) / 8, region->height,
			  color, color,
			  info->fix.line_length, 0x40);
}