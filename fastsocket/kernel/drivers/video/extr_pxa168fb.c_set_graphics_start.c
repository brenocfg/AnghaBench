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
struct pxa168fb_info {int fb_start_dma; scalar_t__ reg_base; } ;
struct fb_var_screeninfo {int xres_virtual; int bits_per_pixel; } ;
struct fb_info {struct fb_var_screeninfo var; struct pxa168fb_info* par; } ;

/* Variables and functions */
 scalar_t__ LCD_CFG_GRA_START_ADDR0 ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static void set_graphics_start(struct fb_info *info, int xoffset, int yoffset)
{
	struct pxa168fb_info *fbi = info->par;
	struct fb_var_screeninfo *var = &info->var;
	int pixel_offset;
	unsigned long addr;

	pixel_offset = (yoffset * var->xres_virtual) + xoffset;

	addr = fbi->fb_start_dma + (pixel_offset * (var->bits_per_pixel >> 3));
	writel(addr, fbi->reg_base + LCD_CFG_GRA_START_ADDR0);
}