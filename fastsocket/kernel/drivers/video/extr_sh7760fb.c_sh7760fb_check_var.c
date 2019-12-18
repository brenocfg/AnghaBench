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
struct sh7760fb_par {TYPE_1__* pd; } ;
struct fb_var_screeninfo {int bits_per_pixel; scalar_t__ grayscale; } ;
struct fb_fix_screeninfo {int /*<<< orphan*/  visual; } ;
struct fb_info {int /*<<< orphan*/  dev; struct sh7760fb_par* par; struct fb_fix_screeninfo fix; } ;
struct TYPE_2__ {int /*<<< orphan*/  lddfr; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_VISUAL_MONO10 ; 
 int /*<<< orphan*/  FB_VISUAL_PSEUDOCOLOR ; 
 int /*<<< orphan*/  FB_VISUAL_TRUECOLOR ; 
 int sh7760fb_get_color_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sh7760fb_check_var(struct fb_var_screeninfo *var,
			      struct fb_info *info)
{
	struct fb_fix_screeninfo *fix = &info->fix;
	struct sh7760fb_par *par = info->par;
	int ret, bpp;

	/* get color info from register value */
	ret = sh7760fb_get_color_info(info->dev, par->pd->lddfr, &bpp, NULL);
	if (ret)
		return ret;

	var->bits_per_pixel = bpp;

	if ((var->grayscale) && (var->bits_per_pixel == 1))
		fix->visual = FB_VISUAL_MONO10;
	else if (var->bits_per_pixel >= 15)
		fix->visual = FB_VISUAL_TRUECOLOR;
	else
		fix->visual = FB_VISUAL_PSEUDOCOLOR;

	/* TODO: add some more validation here */
	return 0;
}