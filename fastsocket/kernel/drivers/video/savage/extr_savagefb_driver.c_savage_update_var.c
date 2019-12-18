#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct fb_videomode {scalar_t__ yres; int /*<<< orphan*/  vmode; int /*<<< orphan*/  sync; int /*<<< orphan*/  vsync_len; int /*<<< orphan*/  hsync_len; int /*<<< orphan*/  lower_margin; int /*<<< orphan*/  upper_margin; int /*<<< orphan*/  right_margin; int /*<<< orphan*/  left_margin; int /*<<< orphan*/  pixclock; int /*<<< orphan*/  xres; } ;
struct fb_var_screeninfo {scalar_t__ yres; scalar_t__ yres_virtual; int /*<<< orphan*/  vmode; int /*<<< orphan*/  sync; int /*<<< orphan*/  vsync_len; int /*<<< orphan*/  hsync_len; int /*<<< orphan*/  lower_margin; int /*<<< orphan*/  upper_margin; int /*<<< orphan*/  right_margin; int /*<<< orphan*/  left_margin; int /*<<< orphan*/  pixclock; scalar_t__ yoffset; scalar_t__ xoffset; int /*<<< orphan*/  xres_virtual; int /*<<< orphan*/  xres; } ;

/* Variables and functions */

__attribute__((used)) static void savage_update_var(struct fb_var_screeninfo *var,
			      const struct fb_videomode *modedb)
{
	var->xres = var->xres_virtual = modedb->xres;
	var->yres = modedb->yres;
        if (var->yres_virtual < var->yres)
	    var->yres_virtual = var->yres;
        var->xoffset = var->yoffset = 0;
        var->pixclock = modedb->pixclock;
        var->left_margin = modedb->left_margin;
        var->right_margin = modedb->right_margin;
        var->upper_margin = modedb->upper_margin;
        var->lower_margin = modedb->lower_margin;
        var->hsync_len = modedb->hsync_len;
        var->vsync_len = modedb->vsync_len;
        var->sync = modedb->sync;
        var->vmode = modedb->vmode;
}