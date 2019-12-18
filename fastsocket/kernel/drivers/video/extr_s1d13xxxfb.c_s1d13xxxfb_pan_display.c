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
struct s1d13xxxfb_par {int display; } ;
struct fb_var_screeninfo {scalar_t__ xoffset; int yoffset; } ;
struct TYPE_4__ {int line_length; } ;
struct TYPE_3__ {scalar_t__ yres; scalar_t__ yres_virtual; } ;
struct fb_info {TYPE_2__ fix; TYPE_1__ var; struct s1d13xxxfb_par* par; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  S1DREG_CRT_DISP_START0 ; 
 int /*<<< orphan*/  S1DREG_CRT_DISP_START1 ; 
 int /*<<< orphan*/  S1DREG_CRT_DISP_START2 ; 
 int /*<<< orphan*/  S1DREG_LCD_DISP_START0 ; 
 int /*<<< orphan*/  S1DREG_LCD_DISP_START1 ; 
 int /*<<< orphan*/  S1DREG_LCD_DISP_START2 ; 
 int /*<<< orphan*/  s1d13xxxfb_writereg (struct s1d13xxxfb_par*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
s1d13xxxfb_pan_display(struct fb_var_screeninfo *var, struct fb_info *info)
{
	struct s1d13xxxfb_par *par = info->par;
	u32 start;

	if (var->xoffset != 0)	/* not yet ... */
		return -EINVAL;

	if (var->yoffset + info->var.yres > info->var.yres_virtual)
		return -EINVAL;

	start = (info->fix.line_length >> 1) * var->yoffset;

	if ((par->display & 0x01)) {
		/* LCD */
		s1d13xxxfb_writereg(par, S1DREG_LCD_DISP_START0, (start & 0xff));
		s1d13xxxfb_writereg(par, S1DREG_LCD_DISP_START1, ((start >> 8) & 0xff));
		s1d13xxxfb_writereg(par, S1DREG_LCD_DISP_START2, ((start >> 16) & 0x0f));
	} else {
		/* CRT */
		s1d13xxxfb_writereg(par, S1DREG_CRT_DISP_START0, (start & 0xff));
		s1d13xxxfb_writereg(par, S1DREG_CRT_DISP_START1, ((start >> 8) & 0xff));
		s1d13xxxfb_writereg(par, S1DREG_CRT_DISP_START2, ((start >> 16) & 0x0f));
	}

	return 0;
}