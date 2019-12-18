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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct msmfb_info {int xres; int yres; TYPE_3__* panel; struct fb_info* fb; } ;
struct TYPE_13__ {int length; scalar_t__ msb_right; scalar_t__ offset; } ;
struct TYPE_12__ {int offset; int length; scalar_t__ msb_right; } ;
struct TYPE_11__ {int offset; int length; scalar_t__ msb_right; } ;
struct TYPE_14__ {int xres; int yres; int xres_virtual; int yres_virtual; int* reserved; TYPE_6__ blue; TYPE_5__ green; TYPE_4__ red; scalar_t__ yoffset; scalar_t__ accel_flags; int /*<<< orphan*/  bits_per_pixel; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_8__ {int ypanstep; int line_length; int /*<<< orphan*/  visual; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
struct fb_info {int* pseudo_palette; int /*<<< orphan*/  cmap; TYPE_7__ var; TYPE_1__ fix; int /*<<< orphan*/  flags; int /*<<< orphan*/ * fbops; } ;
struct TYPE_10__ {int caps; TYPE_2__* fb_data; } ;
struct TYPE_9__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_PER_PIXEL ; 
 int /*<<< orphan*/  FBINFO_DEFAULT ; 
 int /*<<< orphan*/  FB_TYPE_PACKED_PIXELS ; 
 int /*<<< orphan*/  FB_VISUAL_TRUECOLOR ; 
 int MSMFB_CAP_PARTIAL_UPDATES ; 
 int* PP ; 
 int fb_alloc_cmap (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msmfb_ops ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void setup_fb_info(struct msmfb_info *msmfb)
{
	struct fb_info *fb_info = msmfb->fb;
	int r;

	/* finish setting up the fb_info struct */
	strncpy(fb_info->fix.id, "msmfb", 16);
	fb_info->fix.ypanstep = 1;

	fb_info->fbops = &msmfb_ops;
	fb_info->flags = FBINFO_DEFAULT;

	fb_info->fix.type = FB_TYPE_PACKED_PIXELS;
	fb_info->fix.visual = FB_VISUAL_TRUECOLOR;
	fb_info->fix.line_length = msmfb->xres * 2;

	fb_info->var.xres = msmfb->xres;
	fb_info->var.yres = msmfb->yres;
	fb_info->var.width = msmfb->panel->fb_data->width;
	fb_info->var.height = msmfb->panel->fb_data->height;
	fb_info->var.xres_virtual = msmfb->xres;
	fb_info->var.yres_virtual = msmfb->yres * 2;
	fb_info->var.bits_per_pixel = BITS_PER_PIXEL;
	fb_info->var.accel_flags = 0;

	fb_info->var.yoffset = 0;

	if (msmfb->panel->caps & MSMFB_CAP_PARTIAL_UPDATES) {
		fb_info->var.reserved[0] = 0x54445055;
		fb_info->var.reserved[1] = 0;
		fb_info->var.reserved[2] = (uint16_t)msmfb->xres |
					   ((uint32_t)msmfb->yres << 16);
	}

	fb_info->var.red.offset = 11;
	fb_info->var.red.length = 5;
	fb_info->var.red.msb_right = 0;
	fb_info->var.green.offset = 5;
	fb_info->var.green.length = 6;
	fb_info->var.green.msb_right = 0;
	fb_info->var.blue.offset = 0;
	fb_info->var.blue.length = 5;
	fb_info->var.blue.msb_right = 0;

	r = fb_alloc_cmap(&fb_info->cmap, 16, 0);
	fb_info->pseudo_palette = PP;

	PP[0] = 0;
	for (r = 1; r < 16; r++)
		PP[r] = 0xffffffff;
}