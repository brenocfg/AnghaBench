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
typedef  int u_int ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ CLR_PAL_REG ; 

__attribute__((used)) static int g364fb_setcolreg(u_int regno, u_int red, u_int green,
			    u_int blue, u_int transp, struct fb_info *info)
{
	volatile unsigned int *ptr = (volatile unsigned int *) CLR_PAL_REG;

	if (regno > 255)
		return 1;

	red >>= 8;
	green >>= 8;
	blue >>= 8;

	ptr[regno << 1] = (red << 16) | (green << 8) | blue;

	return 0;
}