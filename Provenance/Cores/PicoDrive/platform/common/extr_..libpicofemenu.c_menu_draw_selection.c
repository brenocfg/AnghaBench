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
 scalar_t__ g_menuscreen_ptr ; 
 int g_menuscreen_w ; 
 int me_mfont_h ; 
 int me_mfont_w ; 
 int /*<<< orphan*/  menu_sel_color ; 
 int /*<<< orphan*/  menu_text_color ; 
 int /*<<< orphan*/  text_out16_ (int,int,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void menu_draw_selection(int x, int y, int w)
{
	int i, h;
	unsigned short *dst, *dest;

	text_out16_(x, y, (void *)1, (menu_sel_color < 0) ? menu_text_color : menu_sel_color);

	if (menu_sel_color < 0) return; // no selection hilight

	if (y > 0) y--;
	dest = (unsigned short *)g_menuscreen_ptr + x + y * g_menuscreen_w + me_mfont_w * 2 - 2;
	for (h = me_mfont_h + 1; h > 0; h--)
	{
		dst = dest;
		for (i = w - (me_mfont_w * 2 - 2); i > 0; i--)
			*dst++ = menu_sel_color;
		dest += g_menuscreen_w;
	}
}