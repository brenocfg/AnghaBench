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
struct savagefb_par {int dummy; } ;
struct fb_var_screeninfo {int dummy; } ;
struct fb_info {struct savagefb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  savagefb_update_start (struct savagefb_par*,struct fb_var_screeninfo*) ; 

__attribute__((used)) static int savagefb_pan_display(struct fb_var_screeninfo *var,
				struct fb_info           *info)
{
	struct savagefb_par *par = info->par;

	savagefb_update_start(par, var);
	return 0;
}