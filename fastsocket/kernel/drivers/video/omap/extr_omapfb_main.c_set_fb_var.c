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
struct omapfb_plane_struct {scalar_t__ color_mode; size_t idx; struct omapfb_device* fbdev; } ;
struct TYPE_10__ {TYPE_4__* region; } ;
struct omapfb_device {TYPE_5__ mem_desc; struct lcd_panel* panel; } ;
struct lcd_panel {int x_res; int y_res; int pixel_clock; int /*<<< orphan*/  vsw; int /*<<< orphan*/  hsw; int /*<<< orphan*/  vbp; int /*<<< orphan*/  vfp; int /*<<< orphan*/  hbp; int /*<<< orphan*/  hfp; } ;
struct TYPE_8__ {int length; scalar_t__ msb_right; scalar_t__ offset; } ;
struct TYPE_7__ {int offset; int length; scalar_t__ msb_right; } ;
struct TYPE_6__ {int offset; int length; scalar_t__ msb_right; } ;
struct fb_var_screeninfo {int bits_per_pixel; int rotate; int xres; int yres; int xres_virtual; int yres_virtual; int xoffset; int yoffset; int height; int width; int pixclock; scalar_t__ sync; int /*<<< orphan*/  vmode; int /*<<< orphan*/  vsync_len; int /*<<< orphan*/  hsync_len; int /*<<< orphan*/  lower_margin; int /*<<< orphan*/  upper_margin; int /*<<< orphan*/  right_margin; int /*<<< orphan*/  left_margin; scalar_t__ grayscale; TYPE_3__ blue; TYPE_2__ green; TYPE_1__ red; } ;
struct fb_info {struct omapfb_plane_struct* par; } ;
struct TYPE_9__ {unsigned long size; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FB_VMODE_NONINTERLACED ; 
 scalar_t__ OMAPFB_COLOR_RGB444 ; 
 int OMAPFB_PLANE_XRES_MIN ; 
 int OMAPFB_PLANE_YRES_MIN ; 
 int /*<<< orphan*/  cpu_is_omap15xx () ; 
 scalar_t__ set_color_mode (struct omapfb_plane_struct*,struct fb_var_screeninfo*) ; 

__attribute__((used)) static int set_fb_var(struct fb_info *fbi,
		      struct fb_var_screeninfo *var)
{
	int		bpp;
	unsigned long	max_frame_size;
	unsigned long	line_size;
	int		xres_min, xres_max;
	int		yres_min, yres_max;
	struct omapfb_plane_struct *plane = fbi->par;
	struct omapfb_device *fbdev = plane->fbdev;
	struct lcd_panel *panel = fbdev->panel;

	if (set_color_mode(plane, var) < 0)
		return -EINVAL;

	bpp = var->bits_per_pixel;
	if (plane->color_mode == OMAPFB_COLOR_RGB444)
		bpp = 16;

	switch (var->rotate) {
	case 0:
	case 180:
		xres_min = OMAPFB_PLANE_XRES_MIN;
		xres_max = panel->x_res;
		yres_min = OMAPFB_PLANE_YRES_MIN;
		yres_max = panel->y_res;
		if (cpu_is_omap15xx()) {
			var->xres = panel->x_res;
			var->yres = panel->y_res;
		}
		break;
	case 90:
	case 270:
		xres_min = OMAPFB_PLANE_YRES_MIN;
		xres_max = panel->y_res;
		yres_min = OMAPFB_PLANE_XRES_MIN;
		yres_max = panel->x_res;
		if (cpu_is_omap15xx()) {
			var->xres = panel->y_res;
			var->yres = panel->x_res;
		}
		break;
	default:
		return -EINVAL;
	}

	if (var->xres < xres_min)
		var->xres = xres_min;
	if (var->yres < yres_min)
		var->yres = yres_min;
	if (var->xres > xres_max)
		var->xres = xres_max;
	if (var->yres > yres_max)
		var->yres = yres_max;

	if (var->xres_virtual < var->xres)
		var->xres_virtual = var->xres;
	if (var->yres_virtual < var->yres)
		var->yres_virtual = var->yres;
	max_frame_size = fbdev->mem_desc.region[plane->idx].size;
	line_size = var->xres_virtual * bpp / 8;
	if (line_size * var->yres_virtual > max_frame_size) {
		/* Try to keep yres_virtual first */
		line_size = max_frame_size / var->yres_virtual;
		var->xres_virtual = line_size * 8 / bpp;
		if (var->xres_virtual < var->xres) {
			/* Still doesn't fit. Shrink yres_virtual too */
			var->xres_virtual = var->xres;
			line_size = var->xres * bpp / 8;
			var->yres_virtual = max_frame_size / line_size;
		}
		/* Recheck this, as the virtual size changed. */
		if (var->xres_virtual < var->xres)
			var->xres = var->xres_virtual;
		if (var->yres_virtual < var->yres)
			var->yres = var->yres_virtual;
		if (var->xres < xres_min || var->yres < yres_min)
			return -EINVAL;
	}
	if (var->xres + var->xoffset > var->xres_virtual)
		var->xoffset = var->xres_virtual - var->xres;
	if (var->yres + var->yoffset > var->yres_virtual)
		var->yoffset = var->yres_virtual - var->yres;

	if (plane->color_mode == OMAPFB_COLOR_RGB444) {
		var->red.offset	  = 8; var->red.length	 = 4;
						var->red.msb_right   = 0;
		var->green.offset = 4; var->green.length = 4;
						var->green.msb_right = 0;
		var->blue.offset  = 0; var->blue.length  = 4;
						var->blue.msb_right  = 0;
	} else {
		var->red.offset	 = 11; var->red.length	 = 5;
						var->red.msb_right   = 0;
		var->green.offset = 5;  var->green.length = 6;
						var->green.msb_right = 0;
		var->blue.offset = 0;  var->blue.length  = 5;
						var->blue.msb_right  = 0;
	}

	var->height		= -1;
	var->width		= -1;
	var->grayscale		= 0;

	/* pixclock in ps, the rest in pixclock */
	var->pixclock		= 10000000 / (panel->pixel_clock / 100);
	var->left_margin	= panel->hfp;
	var->right_margin	= panel->hbp;
	var->upper_margin	= panel->vfp;
	var->lower_margin	= panel->vbp;
	var->hsync_len		= panel->hsw;
	var->vsync_len		= panel->vsw;

	/* TODO: get these from panel->config */
	var->vmode		= FB_VMODE_NONINTERLACED;
	var->sync		= 0;

	return 0;
}