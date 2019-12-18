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
typedef  unsigned int u32 ;
struct fb_info {scalar_t__ pseudo_palette; } ;

/* Variables and functions */

__attribute__((used)) static int q40fb_setcolreg(unsigned regno, unsigned red, unsigned green,
			   unsigned blue, unsigned transp,
			   struct fb_info *info)
{
    /*
     *  Set a single color register. The values supplied have a 16 bit
     *  magnitude.
     *  Return != 0 for invalid regno.
     */

    if (regno > 255)
	    return 1;
    red>>=11;
    green>>=11;
    blue>>=10;

    if (regno < 16) {
	((u32 *)info->pseudo_palette)[regno] = ((red & 31) <<6) |
					       ((green & 31) << 11) |
					       (blue & 63);
    }
    return 0;
}