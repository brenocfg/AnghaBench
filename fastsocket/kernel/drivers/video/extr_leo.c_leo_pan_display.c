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
struct fb_var_screeninfo {scalar_t__ vmode; scalar_t__ yoffset; scalar_t__ xoffset; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  leo_switch_from_graph (struct fb_info*) ; 

__attribute__((used)) static int leo_pan_display(struct fb_var_screeninfo *var, struct fb_info *info)
{
	/* We just use this to catch switches out of
	 * graphics mode.
	 */
	leo_switch_from_graph(info);

	if (var->xoffset || var->yoffset || var->vmode)
		return -EINVAL;
	return 0;
}