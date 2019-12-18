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
typedef  int u32 ;
struct fb_var_screeninfo {scalar_t__ xoffset; int yoffset; } ;
struct TYPE_4__ {int line_length; } ;
struct TYPE_3__ {scalar_t__ yres; scalar_t__ yres_virtual; } ;
struct fb_info {TYPE_2__ fix; TYPE_1__ var; struct epson1355_par* par; } ;
struct epson1355_par {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  REG_SCRN1_DISP_START_ADDR0 ; 
 int /*<<< orphan*/  epson1355_write_reg20 (struct epson1355_par*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int epson1355fb_pan_display(struct fb_var_screeninfo *var,
				   struct fb_info *info)
{
	struct epson1355_par *par = info->par;
	u32 start;

	if (var->xoffset != 0)	/* not yet ... */
		return -EINVAL;

	if (var->yoffset + info->var.yres > info->var.yres_virtual)
		return -EINVAL;

	start = (info->fix.line_length >> 1) * var->yoffset;

	epson1355_write_reg20(par, start, REG_SCRN1_DISP_START_ADDR0);

	return 0;
}