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
struct TYPE_4__ {int xres; int bits_per_pixel; } ;
struct TYPE_3__ {int line_length; } ;
struct fb_info {TYPE_2__ var; TYPE_1__ fix; struct carmine_fb* par; } ;
struct carmine_fb {int new_mode; int cur_mode; int /*<<< orphan*/ * res; } ;

/* Variables and functions */
 int /*<<< orphan*/ * car_modes ; 
 int carmine_find_mode (TYPE_2__*) ; 
 int /*<<< orphan*/  carmine_init_display_param (struct carmine_fb*) ; 
 int /*<<< orphan*/  set_display_parameters (struct carmine_fb*) ; 

__attribute__((used)) static int carmine_set_par(struct fb_info *info)
{
	struct carmine_fb *par = info->par;
	int ret;

	ret = carmine_find_mode(&info->var);
	if (ret < 0)
		return ret;

	par->new_mode = ret;
	if (par->cur_mode != par->new_mode) {

		par->cur_mode = par->new_mode;
		par->res = &car_modes[par->new_mode];

		carmine_init_display_param(par);
		set_display_parameters(par);
	}

	info->fix.line_length = info->var.xres * info->var.bits_per_pixel / 8;
	return 0;
}