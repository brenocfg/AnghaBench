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
struct fb_var_screeninfo {int xoffset; int yoffset; } ;
struct TYPE_2__ {int line_length; } ;
struct fb_info {TYPE_1__ fix; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HD64461_LCDCBAR ; 
 int /*<<< orphan*/  fb_writew (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hitfb_pan_display(struct fb_var_screeninfo *var,
			     struct fb_info *info)
{
	int xoffset = var->xoffset;
	int yoffset = var->yoffset;

	if (xoffset != 0)
		return -EINVAL;

	fb_writew((yoffset*info->fix.line_length)>>10, HD64461_LCDCBAR);

	return 0;
}