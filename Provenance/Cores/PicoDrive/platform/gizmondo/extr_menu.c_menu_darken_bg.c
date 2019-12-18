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

/* Variables and functions */

void menu_darken_bg(void *dst, const void *src, int pixels, int darker)
{
	unsigned int *dest = dst;
	const unsigned int *srce = src;
	pixels /= 2;
	if (darker)
	{
		while (pixels--)
		{
			unsigned int p = *srce++;
			*dest++ = ((p&0xf79ef79e)>>1) - ((p&0xc618c618)>>3);
		}
	}
	else
	{
		while (pixels--)
		{
			unsigned int p = *srce++;
			*dest++ = (p&0xf79ef79e)>>1;
		}
	}
}