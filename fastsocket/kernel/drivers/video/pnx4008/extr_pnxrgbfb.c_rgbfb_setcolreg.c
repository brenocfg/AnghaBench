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
 int* colreg ; 

__attribute__((used)) static int rgbfb_setcolreg(u_int regno, u_int red, u_int green, u_int blue,
			   u_int transp, struct fb_info *info)
{
	if (regno > 15)
		return 1;

	colreg[regno] = ((red & 0xff00) << 8) | (green & 0xff00) |
	    ((blue & 0xff00) >> 8);
	return 0;
}