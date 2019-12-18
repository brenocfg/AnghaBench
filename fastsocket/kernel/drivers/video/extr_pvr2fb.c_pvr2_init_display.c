#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pvr2fb_par {int vsync_total; int hsync_total; int is_interlaced; int disp_start; int borderstart_h; int borderstop_h; int borderstart_v; int borderstop_v; int diwstart_h; int diwstart_v; int is_lowres; int is_doublescan; } ;
struct fb_var_screeninfo {int bits_per_pixel; int yres; scalar_t__ xres; scalar_t__ xoffset; } ;
struct TYPE_2__ {int line_length; } ;
struct fb_info {TYPE_1__ fix; struct fb_var_screeninfo var; scalar_t__ par; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISP_BRDRCOLR ; 
 int /*<<< orphan*/  DISP_BRDRHORZ ; 
 int /*<<< orphan*/  DISP_BRDRVERT ; 
 int /*<<< orphan*/  DISP_DIWADDRL ; 
 int /*<<< orphan*/  DISP_DIWADDRS ; 
 int /*<<< orphan*/  DISP_DIWCONF ; 
 int /*<<< orphan*/  DISP_DIWHSTRT ; 
 int /*<<< orphan*/  DISP_DIWMODE ; 
 int /*<<< orphan*/  DISP_DIWSIZE ; 
 int /*<<< orphan*/  DISP_DIWVSTRT ; 
 int /*<<< orphan*/  DISP_PIXDEPTH ; 
 int /*<<< orphan*/  DISP_SYNCCONF ; 
 int /*<<< orphan*/  DISP_SYNCSIZE ; 
 scalar_t__ VO_VGA ; 
 unsigned int fb_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_writel (int,int /*<<< orphan*/ ) ; 
 int get_line_length (scalar_t__,int) ; 
 scalar_t__ video_output ; 

__attribute__((used)) static void pvr2_init_display(struct fb_info *info)
{
	struct pvr2fb_par *par = (struct pvr2fb_par *) info->par;
	struct fb_var_screeninfo *var = &info->var;
	unsigned int diw_height, diw_width, diw_modulo = 1;
	unsigned int bytesperpixel = var->bits_per_pixel >> 3;

	/* hsync and vsync totals */
	fb_writel((par->vsync_total << 16) | par->hsync_total, DISP_SYNCSIZE);

	/* column height, modulo, row width */
	/* since we're "panning" within vram, we need to offset things based
	 * on the offset from the virtual x start to our real gfx. */
	if (video_output != VO_VGA && par->is_interlaced)
		diw_modulo += info->fix.line_length / 4;
	diw_height = (par->is_interlaced ? var->yres / 2 : var->yres);
	diw_width = get_line_length(var->xres, var->bits_per_pixel) / 4;
	fb_writel((diw_modulo << 20) | (--diw_height << 10) | --diw_width,
	          DISP_DIWSIZE);

	/* display address, long and short fields */
	fb_writel(par->disp_start, DISP_DIWADDRL);
	fb_writel(par->disp_start +
	          get_line_length(var->xoffset+var->xres, var->bits_per_pixel),
	          DISP_DIWADDRS);

	/* border horizontal, border vertical, border color */
	fb_writel((par->borderstart_h << 16) | par->borderstop_h, DISP_BRDRHORZ);
	fb_writel((par->borderstart_v << 16) | par->borderstop_v, DISP_BRDRVERT);
	fb_writel(0, DISP_BRDRCOLR);

	/* display window start position */
	fb_writel(par->diwstart_h, DISP_DIWHSTRT);
	fb_writel((par->diwstart_v << 16) | par->diwstart_v, DISP_DIWVSTRT);

	/* misc. settings */
	fb_writel((0x16 << 16) | par->is_lowres, DISP_DIWCONF);

	/* clock doubler (for VGA), scan doubler, display enable */
	fb_writel(((video_output == VO_VGA) << 23) |
	          (par->is_doublescan << 1) | 1, DISP_DIWMODE);

	/* bits per pixel */
	fb_writel(fb_readl(DISP_DIWMODE) | (--bytesperpixel << 2), DISP_DIWMODE);
	fb_writel(bytesperpixel << 2, DISP_PIXDEPTH);

	/* video enable, color sync, interlace,
	 * hsync and vsync polarity (currently unused) */
	fb_writel(0x100 | ((par->is_interlaced /*|4*/) << 4), DISP_SYNCCONF);
}