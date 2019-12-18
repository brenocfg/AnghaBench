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
 int border_bottom ; 
 int border_left ; 
 int border_right ; 
 int border_top ; 
 int g_menuscreen_h ; 
 unsigned short* g_menuscreen_ptr ; 
 int g_menuscreen_w ; 
 unsigned int menu_text_color ; 

__attribute__((used)) static void menu_darken_text_bg(void)
{
	int x, y, xmin, xmax, ymax, ls;
	unsigned short *screen = g_menuscreen_ptr;

	xmin = border_left - 3;
	if (xmin < 0)
		xmin = 0;
	xmax = border_right + 2;
	if (xmax > g_menuscreen_w - 1)
		xmax = g_menuscreen_w - 1;

	y = border_top - 3;
	if (y < 0)
		y = 0;
	ymax = border_bottom + 2;
	if (ymax > g_menuscreen_h - 1)
		ymax = g_menuscreen_h - 1;

	for (x = xmin; x <= xmax; x++)
		screen[y * g_menuscreen_w + x] = 0xa514;
	for (y++; y < ymax; y++)
	{
		ls = y * g_menuscreen_w;
		screen[ls + xmin] = 0xffff;
		for (x = xmin + 1; x < xmax; x++)
		{
			unsigned int p = screen[ls + x];
			if (p != menu_text_color)
				screen[ls + x] = ((p&0xf79e)>>1) - ((p&0xc618)>>3);
		}
		screen[ls + xmax] = 0xffff;
	}
	ls = y * g_menuscreen_w;
	for (x = xmin; x <= xmax; x++)
		screen[ls + x] = 0xffff;
}