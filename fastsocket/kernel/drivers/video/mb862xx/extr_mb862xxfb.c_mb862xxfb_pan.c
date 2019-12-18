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
struct mb862xxfb_par {int dummy; } ;
struct fb_var_screeninfo {int /*<<< orphan*/  xres_virtual; int /*<<< orphan*/  yres_virtual; int /*<<< orphan*/  xoffset; int /*<<< orphan*/  yoffset; } ;
struct fb_info {struct mb862xxfb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  GC_L0WH_L0WW ; 
 int /*<<< orphan*/  GC_L0WY_L0WX ; 
 int /*<<< orphan*/  disp ; 
 int /*<<< orphan*/  outreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long pack (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mb862xxfb_pan(struct fb_var_screeninfo *var,
			 struct fb_info *info)
{
	struct mb862xxfb_par *par = info->par;
	unsigned long reg;

	reg = pack(var->yoffset, var->xoffset);
	outreg(disp, GC_L0WY_L0WX, reg);

	reg = pack(var->yres_virtual, var->xres_virtual);
	outreg(disp, GC_L0WH_L0WW, reg);
	return 0;
}