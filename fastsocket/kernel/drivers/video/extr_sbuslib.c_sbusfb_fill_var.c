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
struct fb_var_screeninfo {int bits_per_pixel; void* yres; void* yres_virtual; void* xres; void* xres_virtual; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct fb_var_screeninfo*,int /*<<< orphan*/ ,int) ; 
 void* of_getintprop_default (struct device_node*,char*,int) ; 

void sbusfb_fill_var(struct fb_var_screeninfo *var, struct device_node *dp,
		     int bpp)
{
	memset(var, 0, sizeof(*var));

	var->xres = of_getintprop_default(dp, "width", 1152);
	var->yres = of_getintprop_default(dp, "height", 900);
	var->xres_virtual = var->xres;
	var->yres_virtual = var->yres;
	var->bits_per_pixel = bpp;
}