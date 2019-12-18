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
struct pm2fb_par {int type; int video; scalar_t__ memclock; } ;
struct TYPE_5__ {int xres_virtual; int yres_virtual; int bits_per_pixel; int xres; int right_margin; int hsync_len; int left_margin; int lower_margin; int vsync_len; int upper_margin; int yres; int yoffset; int xoffset; int sync; int vmode; int activate; int /*<<< orphan*/  pixclock; } ;
struct TYPE_4__ {int len; } ;
struct TYPE_6__ {int line_length; int /*<<< orphan*/  visual; } ;
struct fb_info {TYPE_2__ var; TYPE_1__ cmap; TYPE_3__ fix; struct pm2fb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,...) ; 
 int EINVAL ; 
 int FB_ACTIVATE_MASK ; 
 int FB_ACTIVATE_NOW ; 
 int FB_SYNC_HOR_HIGH_ACT ; 
 int FB_SYNC_VERT_HIGH_ACT ; 
 int /*<<< orphan*/  FB_VISUAL_PSEUDOCOLOR ; 
 int /*<<< orphan*/  FB_VISUAL_TRUECOLOR ; 
 int FB_VMODE_DOUBLE ; 
 int FB_VMODE_INTERLACED ; 
 int FB_VMODE_MASK ; 
 int PICOS2KHZ (int /*<<< orphan*/ ) ; 
 int PM2F_COLOR_KEY_TEST_OFF ; 
 int PM2F_DATA_64_ENABLE ; 
 int PM2F_FB_WRITE_ENABLE ; 
 int PM2F_HSYNC_ACT_HIGH ; 
 int PM2F_HSYNC_ACT_LOW ; 
 int PM2F_LINE_DOUBLE ; 
 int PM2F_RD_COLOR_MODE_RGB ; 
 int PM2F_RD_GUI_ACTIVE ; 
 int PM2F_RD_PIXELFORMAT_RGB565 ; 
 int PM2F_RD_PIXELFORMAT_RGB888 ; 
 int PM2F_RD_PIXELFORMAT_RGBA8888 ; 
 int PM2F_RD_TRUECOLOR ; 
 int PM2F_SCREEN_SCISSOR_ENABLE ; 
 int PM2F_TEXTEL_SIZE_16 ; 
 int PM2F_TEXTEL_SIZE_24 ; 
 int PM2F_TEXTEL_SIZE_32 ; 
 int PM2F_VIDEO_ENABLE ; 
 int PM2F_VSYNC_ACT_HIGH ; 
 int PM2F_VSYNC_ACT_LOW ; 
 int /*<<< orphan*/  PM2I_RD_COLOR_KEY_CONTROL ; 
 int /*<<< orphan*/  PM2I_RD_COLOR_MODE ; 
 int /*<<< orphan*/  PM2R_FB_READ_MODE ; 
 int /*<<< orphan*/  PM2R_FB_READ_PIXEL ; 
 int /*<<< orphan*/  PM2R_FB_WRITE_MODE ; 
 int /*<<< orphan*/  PM2R_HB_END ; 
 int /*<<< orphan*/  PM2R_HG_END ; 
 int /*<<< orphan*/  PM2R_HS_END ; 
 int /*<<< orphan*/  PM2R_HS_START ; 
 int /*<<< orphan*/  PM2R_H_TOTAL ; 
 int /*<<< orphan*/  PM2R_LB_READ_MODE ; 
 int /*<<< orphan*/  PM2R_SCISSOR_MODE ; 
 int /*<<< orphan*/  PM2R_SCREEN_BASE ; 
 int /*<<< orphan*/  PM2R_SCREEN_SIZE ; 
 int /*<<< orphan*/  PM2R_SCREEN_STRIDE ; 
 int /*<<< orphan*/  PM2R_TEXTURE_MAP_FORMAT ; 
 int /*<<< orphan*/  PM2R_VB_END ; 
 int /*<<< orphan*/  PM2R_VS_END ; 
 int /*<<< orphan*/  PM2R_VS_START ; 
 int /*<<< orphan*/  PM2R_V_TOTAL ; 
 int /*<<< orphan*/  PM2R_WINDOW_ORIGIN ; 
 int /*<<< orphan*/  PM2VI_RD_COLOR_FORMAT ; 
 int /*<<< orphan*/  PM2VI_RD_DAC_CONTROL ; 
 int /*<<< orphan*/  PM2VI_RD_MISC_CONTROL ; 
 int /*<<< orphan*/  PM2VI_RD_OVERLAY_KEY ; 
 int /*<<< orphan*/  PM2VI_RD_PIXEL_SIZE ; 
 int /*<<< orphan*/  PM2VR_RD_INDEX_HIGH ; 
 int PM2_MAX_PIXCLOCK ; 
#define  PM2_TYPE_PERMEDIA2 129 
#define  PM2_TYPE_PERMEDIA2V 128 
 int /*<<< orphan*/  WAIT_FIFO (struct pm2fb_par*,int) ; 
 int /*<<< orphan*/  clear_palette (struct pm2fb_par*) ; 
 scalar_t__ lowhsync ; 
 scalar_t__ lowvsync ; 
 int /*<<< orphan*/  mb () ; 
 int partprod (int) ; 
 int /*<<< orphan*/  pm2_RDAC_WR (struct pm2fb_par*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm2_WR (struct pm2fb_par*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm2v_RDAC_WR (struct pm2fb_par*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reset_card (struct pm2fb_par*) ; 
 int /*<<< orphan*/  reset_config (struct pm2fb_par*) ; 
 int /*<<< orphan*/  set_aperture (struct pm2fb_par*,int) ; 
 int /*<<< orphan*/  set_memclock (struct pm2fb_par*,scalar_t__) ; 
 int /*<<< orphan*/  set_pixclock (struct pm2fb_par*,int) ; 
 int /*<<< orphan*/  set_video (struct pm2fb_par*,int) ; 
 int to3264 (int,int,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int pm2fb_set_par(struct fb_info *info)
{
	struct pm2fb_par *par = info->par;
	u32 pixclock;
	u32 width = (info->var.xres_virtual + 7) & ~7;
	u32 height = info->var.yres_virtual;
	u32 depth = (info->var.bits_per_pixel + 7) & ~7;
	u32 hsstart, hsend, hbend, htotal;
	u32 vsstart, vsend, vbend, vtotal;
	u32 stride;
	u32 base;
	u32 video = 0;
	u32 clrmode = PM2F_RD_COLOR_MODE_RGB | PM2F_RD_GUI_ACTIVE;
	u32 txtmap = 0;
	u32 pixsize = 0;
	u32 clrformat = 0;
	u32 misc = 1; /* 8-bit DAC */
	u32 xres = (info->var.xres + 31) & ~31;
	int data64;

	reset_card(par);
	reset_config(par);
	clear_palette(par);
	if (par->memclock)
		set_memclock(par, par->memclock);

	depth = (depth > 32) ? 32 : depth;
	data64 = depth > 8 || par->type == PM2_TYPE_PERMEDIA2V;

	pixclock = PICOS2KHZ(info->var.pixclock);
	if (pixclock > PM2_MAX_PIXCLOCK) {
		DPRINTK("pixclock too high (%uKHz)\n", pixclock);
		return -EINVAL;
	}

	hsstart = to3264(info->var.right_margin, depth, data64);
	hsend = hsstart + to3264(info->var.hsync_len, depth, data64);
	hbend = hsend + to3264(info->var.left_margin, depth, data64);
	htotal = to3264(xres, depth, data64) + hbend - 1;
	vsstart = (info->var.lower_margin)
		? info->var.lower_margin - 1
		: 0;	/* FIXME! */
	vsend = info->var.lower_margin + info->var.vsync_len - 1;
	vbend = info->var.lower_margin + info->var.vsync_len +
		info->var.upper_margin;
	vtotal = info->var.yres + vbend - 1;
	stride = to3264(width, depth, 1);
	base = to3264(info->var.yoffset * xres + info->var.xoffset, depth, 1);
	if (data64)
		video |= PM2F_DATA_64_ENABLE;

	if (info->var.sync & FB_SYNC_HOR_HIGH_ACT) {
		if (lowhsync) {
			DPRINTK("ignoring +hsync, using -hsync.\n");
			video |= PM2F_HSYNC_ACT_LOW;
		} else
			video |= PM2F_HSYNC_ACT_HIGH;
	} else
		video |= PM2F_HSYNC_ACT_LOW;

	if (info->var.sync & FB_SYNC_VERT_HIGH_ACT) {
		if (lowvsync) {
			DPRINTK("ignoring +vsync, using -vsync.\n");
			video |= PM2F_VSYNC_ACT_LOW;
		} else
			video |= PM2F_VSYNC_ACT_HIGH;
	} else
		video |= PM2F_VSYNC_ACT_LOW;

	if ((info->var.vmode & FB_VMODE_MASK) == FB_VMODE_INTERLACED) {
		DPRINTK("interlaced not supported\n");
		return -EINVAL;
	}
	if ((info->var.vmode & FB_VMODE_MASK) == FB_VMODE_DOUBLE)
		video |= PM2F_LINE_DOUBLE;
	if ((info->var.activate & FB_ACTIVATE_MASK) == FB_ACTIVATE_NOW)
		video |= PM2F_VIDEO_ENABLE;
	par->video = video;

	info->fix.visual =
		(depth == 8) ? FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_TRUECOLOR;
	info->fix.line_length = info->var.xres * depth / 8;
	info->cmap.len = 256;

	/*
	 * Settings calculated. Now write them out.
	 */
	if (par->type == PM2_TYPE_PERMEDIA2V) {
		WAIT_FIFO(par, 1);
		pm2_WR(par, PM2VR_RD_INDEX_HIGH, 0);
	}

	set_aperture(par, depth);

	mb();
	WAIT_FIFO(par, 19);
	switch (depth) {
	case 8:
		pm2_WR(par, PM2R_FB_READ_PIXEL, 0);
		clrformat = 0x2e;
		break;
	case 16:
		pm2_WR(par, PM2R_FB_READ_PIXEL, 1);
		clrmode |= PM2F_RD_TRUECOLOR | PM2F_RD_PIXELFORMAT_RGB565;
		txtmap = PM2F_TEXTEL_SIZE_16;
		pixsize = 1;
		clrformat = 0x70;
		misc |= 8;
		break;
	case 32:
		pm2_WR(par, PM2R_FB_READ_PIXEL, 2);
		clrmode |= PM2F_RD_TRUECOLOR | PM2F_RD_PIXELFORMAT_RGBA8888;
		txtmap = PM2F_TEXTEL_SIZE_32;
		pixsize = 2;
		clrformat = 0x20;
		misc |= 8;
		break;
	case 24:
		pm2_WR(par, PM2R_FB_READ_PIXEL, 4);
		clrmode |= PM2F_RD_TRUECOLOR | PM2F_RD_PIXELFORMAT_RGB888;
		txtmap = PM2F_TEXTEL_SIZE_24;
		pixsize = 4;
		clrformat = 0x20;
		misc |= 8;
		break;
	}
	pm2_WR(par, PM2R_FB_WRITE_MODE, PM2F_FB_WRITE_ENABLE);
	pm2_WR(par, PM2R_FB_READ_MODE, partprod(xres));
	pm2_WR(par, PM2R_LB_READ_MODE, partprod(xres));
	pm2_WR(par, PM2R_TEXTURE_MAP_FORMAT, txtmap | partprod(xres));
	pm2_WR(par, PM2R_H_TOTAL, htotal);
	pm2_WR(par, PM2R_HS_START, hsstart);
	pm2_WR(par, PM2R_HS_END, hsend);
	pm2_WR(par, PM2R_HG_END, hbend);
	pm2_WR(par, PM2R_HB_END, hbend);
	pm2_WR(par, PM2R_V_TOTAL, vtotal);
	pm2_WR(par, PM2R_VS_START, vsstart);
	pm2_WR(par, PM2R_VS_END, vsend);
	pm2_WR(par, PM2R_VB_END, vbend);
	pm2_WR(par, PM2R_SCREEN_STRIDE, stride);
	wmb();
	pm2_WR(par, PM2R_WINDOW_ORIGIN, 0);
	pm2_WR(par, PM2R_SCREEN_SIZE, (height << 16) | width);
	pm2_WR(par, PM2R_SCISSOR_MODE, PM2F_SCREEN_SCISSOR_ENABLE);
	wmb();
	pm2_WR(par, PM2R_SCREEN_BASE, base);
	wmb();
	set_video(par, video);
	WAIT_FIFO(par, 10);
	switch (par->type) {
	case PM2_TYPE_PERMEDIA2:
		pm2_RDAC_WR(par, PM2I_RD_COLOR_MODE, clrmode);
		pm2_RDAC_WR(par, PM2I_RD_COLOR_KEY_CONTROL,
				(depth == 8) ? 0 : PM2F_COLOR_KEY_TEST_OFF);
		break;
	case PM2_TYPE_PERMEDIA2V:
		pm2v_RDAC_WR(par, PM2VI_RD_DAC_CONTROL, 0);
		pm2v_RDAC_WR(par, PM2VI_RD_PIXEL_SIZE, pixsize);
		pm2v_RDAC_WR(par, PM2VI_RD_COLOR_FORMAT, clrformat);
		pm2v_RDAC_WR(par, PM2VI_RD_MISC_CONTROL, misc);
		pm2v_RDAC_WR(par, PM2VI_RD_OVERLAY_KEY, 0);
		break;
	}
	set_pixclock(par, pixclock);
	DPRINTK("Setting graphics mode at %dx%d depth %d\n",
		info->var.xres, info->var.yres, info->var.bits_per_pixel);
	return 0;
}