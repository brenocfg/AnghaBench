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
typedef  int u8 ;
typedef  size_t u32 ;
struct pm2fb_par {scalar_t__ type; } ;
struct TYPE_5__ {int* red; int* green; int* blue; } ;
struct TYPE_4__ {int xoffset; int yoffset; } ;
struct fb_info {TYPE_2__ cmap; TYPE_1__ var; struct pm2fb_par* par; } ;
struct TYPE_6__ {int width; int height; int depth; int dx; int dy; size_t fg_color; size_t bg_color; scalar_t__ data; } ;
struct fb_cursor {int set; scalar_t__ rop; TYPE_3__ image; scalar_t__ mask; scalar_t__ enable; } ;

/* Variables and functions */
 int EINVAL ; 
 int FB_CUR_SETCMAP ; 
 int FB_CUR_SETIMAGE ; 
 int FB_CUR_SETPOS ; 
 int FB_CUR_SETSHAPE ; 
 int /*<<< orphan*/  PM2I_RD_CURSOR_CONTROL ; 
 int /*<<< orphan*/  PM2R_RD_CURSOR_COLOR_ADDRESS ; 
 int /*<<< orphan*/  PM2R_RD_CURSOR_COLOR_DATA ; 
 int /*<<< orphan*/  PM2R_RD_CURSOR_DATA ; 
 int /*<<< orphan*/  PM2R_RD_CURSOR_X_LSB ; 
 int /*<<< orphan*/  PM2R_RD_CURSOR_X_MSB ; 
 int /*<<< orphan*/  PM2R_RD_CURSOR_Y_LSB ; 
 int /*<<< orphan*/  PM2R_RD_CURSOR_Y_MSB ; 
 int /*<<< orphan*/  PM2R_RD_PALETTE_WRITE_ADDRESS ; 
 scalar_t__ PM2_TYPE_PERMEDIA2V ; 
 scalar_t__ ROP_COPY ; 
 int /*<<< orphan*/  WAIT_FIFO (struct pm2fb_par*,int) ; 
 int /*<<< orphan*/  hwcursor ; 
 int /*<<< orphan*/  pm2_RDAC_WR (struct pm2fb_par*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm2_WR (struct pm2fb_par*,int /*<<< orphan*/ ,int) ; 
 int pm2vfb_cursor (struct fb_info*,struct fb_cursor*) ; 

__attribute__((used)) static int pm2fb_cursor(struct fb_info *info, struct fb_cursor *cursor)
{
	struct pm2fb_par *par = info->par;
	u8 mode;

	if (!hwcursor)
		return -EINVAL;	/* just to force soft_cursor() call */

	/* Too large of a cursor or wrong bpp :-( */
	if (cursor->image.width > 64 ||
	    cursor->image.height > 64 ||
	    cursor->image.depth > 1)
		return -EINVAL;

	if (par->type == PM2_TYPE_PERMEDIA2V)
		return pm2vfb_cursor(info, cursor);

	mode = 0x40;
	if (cursor->enable)
		 mode = 0x43;

	pm2_RDAC_WR(par, PM2I_RD_CURSOR_CONTROL, mode);

	/*
	 * If the cursor is not be changed this means either we want the
	 * current cursor state (if enable is set) or we want to query what
	 * we can do with the cursor (if enable is not set)
	 */
	if (!cursor->set)
		return 0;

	if (cursor->set & FB_CUR_SETPOS) {
		int x = cursor->image.dx - info->var.xoffset + 63;
		int y = cursor->image.dy - info->var.yoffset + 63;

		WAIT_FIFO(par, 4);
		pm2_WR(par, PM2R_RD_CURSOR_X_LSB, x & 0xff);
		pm2_WR(par, PM2R_RD_CURSOR_X_MSB, (x >> 8) & 0x7);
		pm2_WR(par, PM2R_RD_CURSOR_Y_LSB, y & 0xff);
		pm2_WR(par, PM2R_RD_CURSOR_Y_MSB, (y >> 8) & 0x7);
	}

	if (cursor->set & FB_CUR_SETCMAP) {
		u32 fg_idx = cursor->image.fg_color;
		u32 bg_idx = cursor->image.bg_color;

		WAIT_FIFO(par, 7);
		pm2_WR(par, PM2R_RD_CURSOR_COLOR_ADDRESS, 1);
		pm2_WR(par, PM2R_RD_CURSOR_COLOR_DATA,
			info->cmap.red[bg_idx] >> 8);
		pm2_WR(par, PM2R_RD_CURSOR_COLOR_DATA,
			info->cmap.green[bg_idx] >> 8);
		pm2_WR(par, PM2R_RD_CURSOR_COLOR_DATA,
			info->cmap.blue[bg_idx] >> 8);

		pm2_WR(par, PM2R_RD_CURSOR_COLOR_DATA,
			info->cmap.red[fg_idx] >> 8);
		pm2_WR(par, PM2R_RD_CURSOR_COLOR_DATA,
			info->cmap.green[fg_idx] >> 8);
		pm2_WR(par, PM2R_RD_CURSOR_COLOR_DATA,
			info->cmap.blue[fg_idx] >> 8);
	}

	if (cursor->set & (FB_CUR_SETSHAPE | FB_CUR_SETIMAGE)) {
		u8 *bitmap = (u8 *)cursor->image.data;
		u8 *mask = (u8 *)cursor->mask;
		int i;

		WAIT_FIFO(par, 1);
		pm2_WR(par, PM2R_RD_PALETTE_WRITE_ADDRESS, 0);

		for (i = 0; i < cursor->image.height; i++) {
			int j = (cursor->image.width + 7) >> 3;
			int k = 8 - j;

			WAIT_FIFO(par, 8);
			for (; j > 0; j--) {
				u8 data = *bitmap ^ *mask;

				if (cursor->rop == ROP_COPY)
					data = *mask & *bitmap;
				/* bitmap data */
				pm2_WR(par, PM2R_RD_CURSOR_DATA, data);
				bitmap++;
				mask++;
			}
			for (; k > 0; k--)
				pm2_WR(par, PM2R_RD_CURSOR_DATA, 0);
		}
		for (; i < 64; i++) {
			int j = 8;
			WAIT_FIFO(par, 8);
			while (j-- > 0)
				pm2_WR(par, PM2R_RD_CURSOR_DATA, 0);
		}

		mask = (u8 *)cursor->mask;
		for (i = 0; i < cursor->image.height; i++) {
			int j = (cursor->image.width + 7) >> 3;
			int k = 8 - j;

			WAIT_FIFO(par, 8);
			for (; j > 0; j--) {
				/* mask */
				pm2_WR(par, PM2R_RD_CURSOR_DATA, *mask);
				mask++;
			}
			for (; k > 0; k--)
				pm2_WR(par, PM2R_RD_CURSOR_DATA, 0);
		}
		for (; i < 64; i++) {
			int j = 8;
			WAIT_FIFO(par, 8);
			while (j-- > 0)
				pm2_WR(par, PM2R_RD_CURSOR_DATA, 0);
		}
	}
	return 0;
}