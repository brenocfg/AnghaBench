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
struct fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vga16fb_pan_var (struct fb_info*,struct fb_var_screeninfo*) ; 

__attribute__((used)) static int vga16fb_pan_display(struct fb_var_screeninfo *var,
			       struct fb_info *info) 
{
	vga16fb_pan_var(info, var);
	return 0;
}