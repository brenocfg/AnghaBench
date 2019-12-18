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
struct gxt4500_par {int dummy; } ;
struct fb_var_screeninfo {int xoffset; scalar_t__ xres; scalar_t__ xres_virtual; int yoffset; scalar_t__ yres; scalar_t__ yres_virtual; } ;
struct fb_info {struct gxt4500_par* par; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  REFRESH_START ; 
 int /*<<< orphan*/  writereg (struct gxt4500_par*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gxt4500_pan_display(struct fb_var_screeninfo *var,
			       struct fb_info *info)
{
	struct gxt4500_par *par = info->par;

	if (var->xoffset & 7)
		return -EINVAL;
	if (var->xoffset + var->xres > var->xres_virtual ||
	    var->yoffset + var->yres > var->yres_virtual)
		return -EINVAL;

	writereg(par, REFRESH_START, (var->xoffset << 16) | var->yoffset);
	return 0;
}