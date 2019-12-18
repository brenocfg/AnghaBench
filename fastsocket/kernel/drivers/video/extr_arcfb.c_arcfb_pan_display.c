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
struct fb_var_screeninfo {int vmode; int yoffset; } ;
struct TYPE_2__ {int yres; int yoffset; } ;
struct fb_info {TYPE_1__ var; struct arcfb_par* par; } ;
struct arcfb_par {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int FB_VMODE_YWRAP ; 
 int /*<<< orphan*/  ks108_set_start_line (struct arcfb_par*,int,int) ; 
 int num_cols ; 

__attribute__((used)) static int arcfb_pan_display(struct fb_var_screeninfo *var,
				struct fb_info *info)
{
	int i;
	struct arcfb_par *par = info->par;

	if ((var->vmode & FB_VMODE_YWRAP) && (var->yoffset < 64)
		&& (info->var.yres <= 64)) {
		for (i = 0; i < num_cols; i++) {
			ks108_set_start_line(par, i, var->yoffset);
		}
		info->var.yoffset = var->yoffset;
		return 0;
	}

	return -EINVAL;
}