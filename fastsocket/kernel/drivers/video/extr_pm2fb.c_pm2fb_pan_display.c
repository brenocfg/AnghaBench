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
typedef  int u32 ;
struct pm2fb_par {int dummy; } ;
struct fb_var_screeninfo {int bits_per_pixel; int xres; int yoffset; scalar_t__ xoffset; } ;
struct fb_info {struct pm2fb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM2R_SCREEN_BASE ; 
 int /*<<< orphan*/  WAIT_FIFO (struct pm2fb_par*,int) ; 
 int /*<<< orphan*/  pm2_WR (struct pm2fb_par*,int /*<<< orphan*/ ,int) ; 
 int to3264 (scalar_t__,int,int) ; 

__attribute__((used)) static int pm2fb_pan_display(struct fb_var_screeninfo *var,
			     struct fb_info *info)
{
	struct pm2fb_par *p = info->par;
	u32 base;
	u32 depth = (var->bits_per_pixel + 7) & ~7;
	u32 xres = (var->xres + 31) & ~31;

	depth = (depth > 32) ? 32 : depth;
	base = to3264(var->yoffset * xres + var->xoffset, depth, 1);
	WAIT_FIFO(p, 1);
	pm2_WR(p, PM2R_SCREEN_BASE, base);
	return 0;
}