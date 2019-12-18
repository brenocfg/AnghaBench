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
struct fb_var_screeninfo {int /*<<< orphan*/  activate; } ;
struct fb_info {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FBINFO_MISC_USEREVENT ; 
 int /*<<< orphan*/  FB_ACTIVATE_FORCE ; 
 int /*<<< orphan*/  acquire_console_sem () ; 
 int fb_set_var (struct fb_info*,struct fb_var_screeninfo*) ; 
 int /*<<< orphan*/  release_console_sem () ; 

__attribute__((used)) static int activate(struct fb_info *fb_info, struct fb_var_screeninfo *var)
{
	int err;

	var->activate |= FB_ACTIVATE_FORCE;
	acquire_console_sem();
	fb_info->flags |= FBINFO_MISC_USEREVENT;
	err = fb_set_var(fb_info, var);
	fb_info->flags &= ~FBINFO_MISC_USEREVENT;
	release_console_sem();
	if (err)
		return err;
	return 0;
}