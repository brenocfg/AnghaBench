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
struct fb_videomode {int dummy; } ;
struct fb_var_screeninfo {int dummy; } ;
struct fb_info {int /*<<< orphan*/  modelist; } ;

/* Variables and functions */
 struct fb_videomode* fb_find_nearest_mode (struct fb_videomode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fb_var_to_videomode (struct fb_videomode*,struct fb_var_screeninfo*) ; 
 int /*<<< orphan*/  fb_videomode_to_var (struct fb_var_screeninfo*,struct fb_videomode const*) ; 

__attribute__((used)) static const struct fb_videomode *atmel_lcdfb_choose_mode(struct fb_var_screeninfo *var,
						     struct fb_info *info)
{
	struct fb_videomode varfbmode;
	const struct fb_videomode *fbmode = NULL;

	fb_var_to_videomode(&varfbmode, var);
	fbmode = fb_find_nearest_mode(&varfbmode, &info->modelist);
	if (fbmode)
		fb_videomode_to_var(var, fbmode);
	return fbmode;
}