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
struct fb_var_screeninfo {int dummy; } ;
struct fb_info {int /*<<< orphan*/  par; } ;

/* Variables and functions */
 int platinum_var_to_par (struct fb_var_screeninfo*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int platinumfb_check_var (struct fb_var_screeninfo *var, struct fb_info *info)
{
	return platinum_var_to_par(var, info->par, 1);
}