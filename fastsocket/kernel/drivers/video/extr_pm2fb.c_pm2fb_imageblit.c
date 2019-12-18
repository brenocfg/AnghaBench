#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pm2fb_par {int* palette; } ;
struct TYPE_6__ {int scan_align; } ;
struct TYPE_5__ {int xres; int bits_per_pixel; } ;
struct TYPE_4__ {int visual; } ;
struct fb_info {scalar_t__ state; int flags; TYPE_3__ pixmap; TYPE_2__ var; TYPE_1__ fix; struct pm2fb_par* par; } ;
struct fb_image {int height; int depth; int fg_color; int bg_color; int dy; int dx; int width; scalar_t__ data; } ;

/* Variables and functions */
 int FBINFO_HWACCEL_DISABLED ; 
 scalar_t__ FBINFO_STATE_RUNNING ; 
#define  FB_VISUAL_PSEUDOCOLOR 129 
#define  FB_VISUAL_TRUECOLOR 128 
 int const PM2F_INCREASE_X ; 
 int const PM2F_INCREASE_Y ; 
 int const PM2F_RENDER_FASTFILL ; 
 int const PM2F_RENDER_RECTANGLE ; 
 int const PM2F_RENDER_SYNC_ON_BIT_MASK ; 
 int /*<<< orphan*/  PM2R_BIT_MASK_PATTERN ; 
 int /*<<< orphan*/  PM2R_COLOR_DDA_MODE ; 
 int /*<<< orphan*/  PM2R_CONSTANT_COLOR ; 
 int /*<<< orphan*/  PM2R_FB_BLOCK_COLOR ; 
 int /*<<< orphan*/  PM2R_FB_READ_MODE ; 
 int /*<<< orphan*/  PM2R_LOGICAL_OP_MODE ; 
 int /*<<< orphan*/  PM2R_RASTERIZER_MODE ; 
 int /*<<< orphan*/  PM2R_RECTANGLE_ORIGIN ; 
 int /*<<< orphan*/  PM2R_RECTANGLE_SIZE ; 
 int /*<<< orphan*/  PM2R_RENDER ; 
 int /*<<< orphan*/  PM2R_SCISSOR_MAX_XY ; 
 int /*<<< orphan*/  PM2R_SCISSOR_MIN_XY ; 
 int /*<<< orphan*/  PM2R_SCISSOR_MODE ; 
 int /*<<< orphan*/  WAIT_FIFO (struct pm2fb_par*,int) ; 
 int /*<<< orphan*/  cfb_imageblit (struct fb_info*,struct fb_image const*) ; 
 int const partprod (int) ; 
 int /*<<< orphan*/  pm2_WR (struct pm2fb_par*,int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static void pm2fb_imageblit(struct fb_info *info, const struct fb_image *image)
{
	struct pm2fb_par *par = info->par;
	u32 height = image->height;
	u32 fgx, bgx;
	const u32 *src = (const u32 *)image->data;
	u32 xres = (info->var.xres + 31) & ~31;
	int raster_mode = 1; /* invert bits */

#ifdef __LITTLE_ENDIAN
	raster_mode |= 3 << 7; /* reverse byte order */
#endif

	if (info->state != FBINFO_STATE_RUNNING)
		return;
	if (info->flags & FBINFO_HWACCEL_DISABLED || image->depth != 1) {
		cfb_imageblit(info, image);
		return;
	}
	switch (info->fix.visual) {
	case FB_VISUAL_PSEUDOCOLOR:
		fgx = image->fg_color;
		bgx = image->bg_color;
		break;
	case FB_VISUAL_TRUECOLOR:
	default:
		fgx = par->palette[image->fg_color];
		bgx = par->palette[image->bg_color];
		break;
	}
	if (info->var.bits_per_pixel == 8) {
		fgx |= fgx << 8;
		bgx |= bgx << 8;
	}
	if (info->var.bits_per_pixel <= 16) {
		fgx |= fgx << 16;
		bgx |= bgx << 16;
	}

	WAIT_FIFO(par, 13);
	pm2_WR(par, PM2R_FB_READ_MODE, partprod(xres));
	pm2_WR(par, PM2R_SCISSOR_MIN_XY,
			((image->dy & 0xfff) << 16) | (image->dx & 0x0fff));
	pm2_WR(par, PM2R_SCISSOR_MAX_XY,
			(((image->dy + image->height) & 0x0fff) << 16) |
			((image->dx + image->width) & 0x0fff));
	pm2_WR(par, PM2R_SCISSOR_MODE, 1);
	/* GXcopy & UNIT_ENABLE */
	pm2_WR(par, PM2R_LOGICAL_OP_MODE, (0x3 << 1) | 1);
	pm2_WR(par, PM2R_RECTANGLE_ORIGIN,
			((image->dy & 0xfff) << 16) | (image->dx & 0x0fff));
	pm2_WR(par, PM2R_RECTANGLE_SIZE,
			((image->height & 0x0fff) << 16) |
			((image->width) & 0x0fff));
	if (info->var.bits_per_pixel == 24) {
		pm2_WR(par, PM2R_COLOR_DDA_MODE, 1);
		/* clear area */
		pm2_WR(par, PM2R_CONSTANT_COLOR, bgx);
		pm2_WR(par, PM2R_RENDER,
			PM2F_RENDER_RECTANGLE |
			PM2F_INCREASE_X | PM2F_INCREASE_Y);
		/* BitMapPackEachScanline */
		pm2_WR(par, PM2R_RASTERIZER_MODE, raster_mode | (1 << 9));
		pm2_WR(par, PM2R_CONSTANT_COLOR, fgx);
		pm2_WR(par, PM2R_RENDER,
			PM2F_RENDER_RECTANGLE |
			PM2F_INCREASE_X | PM2F_INCREASE_Y |
			PM2F_RENDER_SYNC_ON_BIT_MASK);
	} else {
		pm2_WR(par, PM2R_COLOR_DDA_MODE, 0);
		/* clear area */
		pm2_WR(par, PM2R_FB_BLOCK_COLOR, bgx);
		pm2_WR(par, PM2R_RENDER,
			PM2F_RENDER_RECTANGLE |
			PM2F_RENDER_FASTFILL |
			PM2F_INCREASE_X | PM2F_INCREASE_Y);
		pm2_WR(par, PM2R_RASTERIZER_MODE, raster_mode);
		pm2_WR(par, PM2R_FB_BLOCK_COLOR, fgx);
		pm2_WR(par, PM2R_RENDER,
			PM2F_RENDER_RECTANGLE |
			PM2F_INCREASE_X | PM2F_INCREASE_Y |
			PM2F_RENDER_FASTFILL |
			PM2F_RENDER_SYNC_ON_BIT_MASK);
	}

	while (height--) {
		int width = ((image->width + 7) >> 3)
				+ info->pixmap.scan_align - 1;
		width >>= 2;
		WAIT_FIFO(par, width);
		while (width--) {
			pm2_WR(par, PM2R_BIT_MASK_PATTERN, *src);
			src++;
		}
	}
	WAIT_FIFO(par, 3);
	pm2_WR(par, PM2R_RASTERIZER_MODE, 0);
	pm2_WR(par, PM2R_COLOR_DDA_MODE, 0);
	pm2_WR(par, PM2R_SCISSOR_MODE, 0);
}