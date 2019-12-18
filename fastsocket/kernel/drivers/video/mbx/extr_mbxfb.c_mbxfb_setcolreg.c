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
typedef  scalar_t__ u_int ;
typedef  int u32 ;
struct fb_info {int* pseudo_palette; } ;

/* Variables and functions */
 scalar_t__ MAX_PALETTES ; 

__attribute__((used)) static int mbxfb_setcolreg(u_int regno, u_int red, u_int green, u_int blue,
			   u_int trans, struct fb_info *info)
{
	u32 val, ret = 1;

	if (regno < MAX_PALETTES) {
		u32 *pal = info->pseudo_palette;

		val = (red & 0xf800) | ((green & 0xfc00) >> 5) |
			((blue & 0xf800) >> 11);
		pal[regno] = val;
		ret = 0;
	}

	return ret;
}