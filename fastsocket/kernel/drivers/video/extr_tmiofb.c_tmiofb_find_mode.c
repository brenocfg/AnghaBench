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
struct tmio_fb_data {int num_modes; struct fb_videomode* modes; } ;
struct mfd_cell {struct tmio_fb_data* driver_data; } ;
struct fb_videomode {scalar_t__ xres; scalar_t__ yres; } ;
struct fb_var_screeninfo {scalar_t__ xres; scalar_t__ yres; } ;
struct fb_info {TYPE_1__* device; } ;
struct TYPE_2__ {struct mfd_cell* platform_data; } ;

/* Variables and functions */

__attribute__((used)) static struct fb_videomode *
tmiofb_find_mode(struct fb_info *info, struct fb_var_screeninfo *var)
{
	struct mfd_cell *cell =
		info->device->platform_data;
	struct tmio_fb_data *data = cell->driver_data;
	struct fb_videomode *best = NULL;
	int i;

	for (i = 0; i < data->num_modes; i++) {
		struct fb_videomode *mode = data->modes + i;

		if (mode->xres >= var->xres && mode->yres >= var->yres
				&& (!best || (mode->xres < best->xres
					   && mode->yres < best->yres)))
			best = mode;
	}

	return best;
}