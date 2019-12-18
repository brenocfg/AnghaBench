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
typedef  int u32 ;
struct pm3_par {int dummy; } ;
struct TYPE_4__ {int xres_virtual; int yres_virtual; int bits_per_pixel; } ;
struct TYPE_3__ {scalar_t__ visual; } ;
struct fb_info {scalar_t__ state; int flags; TYPE_2__ var; scalar_t__ pseudo_palette; TYPE_1__ fix; struct pm3_par* par; } ;
struct fb_fillrect {size_t color; scalar_t__ rop; int width; int height; int dx; int dy; } ;

/* Variables and functions */
 int FBINFO_HWACCEL_DISABLED ; 
 scalar_t__ FBINFO_STATE_RUNNING ; 
 scalar_t__ FB_VISUAL_TRUECOLOR ; 
 int /*<<< orphan*/  PM3Config2D ; 
 int PM3Config2D_FBDestReadEnable ; 
 int PM3Config2D_FBWriteEnable ; 
 int PM3Config2D_ForegroundROP (int) ; 
 int PM3Config2D_ForegroundROPEnable ; 
 int PM3Config2D_UseConstantSource ; 
 int /*<<< orphan*/  PM3ForegroundColor ; 
 int /*<<< orphan*/  PM3RectanglePosition ; 
 int PM3RectanglePosition_XOffset (int) ; 
 int PM3RectanglePosition_YOffset (int) ; 
 int /*<<< orphan*/  PM3Render2D ; 
 int PM3Render2D_Height (int) ; 
 int PM3Render2D_Operation_Normal ; 
 int PM3Render2D_SpanOperation ; 
 int PM3Render2D_Width (int) ; 
 int PM3Render2D_XPositive ; 
 int PM3Render2D_YPositive ; 
 int /*<<< orphan*/  PM3_WAIT (struct pm3_par*,int) ; 
 int /*<<< orphan*/  PM3_WRITE_REG (struct pm3_par*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ROP_COPY ; 
 int /*<<< orphan*/  cfb_fillrect (struct fb_info*,struct fb_fillrect const*) ; 
 int /*<<< orphan*/  memcpy (struct fb_fillrect*,struct fb_fillrect const*,int) ; 

__attribute__((used)) static void pm3fb_fillrect(struct fb_info *info,
				const struct fb_fillrect *region)
{
	struct pm3_par *par = info->par;
	struct fb_fillrect modded;
	int vxres, vyres;
	int rop;
	u32 color = (info->fix.visual == FB_VISUAL_TRUECOLOR) ?
		((u32 *)info->pseudo_palette)[region->color] : region->color;

	if (info->state != FBINFO_STATE_RUNNING)
		return;
	if (info->flags & FBINFO_HWACCEL_DISABLED) {
		cfb_fillrect(info, region);
		return;
	}
	if (region->rop == ROP_COPY )
		rop = PM3Config2D_ForegroundROP(0x3); /* GXcopy */
	else
		rop = PM3Config2D_ForegroundROP(0x6) | /* GXxor */
			PM3Config2D_FBDestReadEnable;

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

	if (info->var.bits_per_pixel == 8)
		color |= color << 8;
	if (info->var.bits_per_pixel <= 16)
		color |= color << 16;

	PM3_WAIT(par, 4);
	/* ROP Ox3 is GXcopy */
	PM3_WRITE_REG(par, PM3Config2D,
			PM3Config2D_UseConstantSource |
			PM3Config2D_ForegroundROPEnable |
			rop |
			PM3Config2D_FBWriteEnable);

	PM3_WRITE_REG(par, PM3ForegroundColor, color);

	PM3_WRITE_REG(par, PM3RectanglePosition,
			PM3RectanglePosition_XOffset(modded.dx) |
			PM3RectanglePosition_YOffset(modded.dy));

	PM3_WRITE_REG(par, PM3Render2D,
		      PM3Render2D_XPositive |
		      PM3Render2D_YPositive |
		      PM3Render2D_Operation_Normal |
		      PM3Render2D_SpanOperation |
		      PM3Render2D_Width(modded.width) |
		      PM3Render2D_Height(modded.height));
}