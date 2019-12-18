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
 unsigned char** fontdata6x8 ; 
 scalar_t__ g_menuscreen_ptr ; 
 int g_menuscreen_w ; 
 int me_sfont_w ; 

__attribute__((used)) static void smalltext_out16_(int x, int y, const char *texto, int color)
{
	unsigned char  *src;
	unsigned short *dst;
	int multiplier = me_sfont_w / 6;
	int i;

	for (i = 0;; i++, x += me_sfont_w)
	{
		unsigned char c = (unsigned char) texto[i];
		int h = 8;

		if (!c || c == '\n')
			break;

		src = fontdata6x8[c];
		dst = (unsigned short *)g_menuscreen_ptr + x + y * g_menuscreen_w;

		while (h--)
		{
			int m, w2, h2;
			for (h2 = multiplier; h2 > 0; h2--)
			{
				for (m = 0x20; m; m >>= 1) {
					if (*src & m)
						for (w2 = multiplier; w2 > 0; w2--)
							*dst++ = color;
					else
						dst += multiplier;
				}

				dst += g_menuscreen_w - me_sfont_w;
			}
			src++;
		}
	}
}