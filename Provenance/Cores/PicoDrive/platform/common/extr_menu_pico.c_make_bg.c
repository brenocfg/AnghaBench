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
 unsigned int* g_menubg_ptr ; 
 scalar_t__ g_menubg_src_ptr ; 
 int g_menuscreen_h ; 
 int g_menuscreen_w ; 
 int g_screen_height ; 
 int g_screen_width ; 
 int /*<<< orphan*/  memset (unsigned int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  menu_darken_bg (short*,unsigned short*,int,int) ; 

__attribute__((used)) static void make_bg(int no_scale)
{
	unsigned short *src = (void *)g_menubg_src_ptr;
	int w = g_screen_width, h = g_screen_height;
	short *dst;
	int x, y;

	if (src == NULL) {
		memset(g_menubg_ptr, 0, g_menuscreen_w * g_menuscreen_h * 2);
		return;
	}

	if (!no_scale && g_menuscreen_w / w >= 2 && g_menuscreen_h / h >= 2)
	{
		unsigned int t, *d = g_menubg_ptr;
		d += (g_menuscreen_h / 2 - h * 2 / 2)
			* g_menuscreen_w / 2;
		d += (g_menuscreen_w / 2 - w * 2 / 2) / 2;
		for (y = 0; y < h; y++, src += w, d += g_menuscreen_w*2/2) {
			for (x = 0; x < w; x++) {
				t = src[x];
				t = ((t & 0xf79e)>>1) - ((t & 0xc618)>>3);
				t |= t << 16;
				d[x] = d[x + g_menuscreen_w / 2] = t;
			}
		}
		return;
	}

	if (w > g_menuscreen_w)
		w = g_menuscreen_w;
	if (h > g_menuscreen_h)
		h = g_menuscreen_h;
	dst = (short *)g_menubg_ptr +
		(g_menuscreen_h / 2 - h / 2) * g_menuscreen_w +
		(g_menuscreen_w / 2 - w / 2);

	// darken the active framebuffer
	for (; h > 0; dst += g_menuscreen_w, src += g_screen_width, h--)
		menu_darken_bg(dst, src, w, 1);
}