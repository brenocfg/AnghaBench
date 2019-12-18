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
 int g_menuscreen_h ; 
 int me_sfont_h ; 
 int /*<<< orphan*/  smalltext_out16 (int,int,char const*,int) ; 

__attribute__((used)) static void draw_text_debug(const char *str, int skip, int from)
{
	const char *p;
	int line;

	p = str;
	while (skip-- > 0)
	{
		while (*p && *p != '\n')
			p++;
		if (*p == 0 || p[1] == 0)
			return;
		p++;
	}

	str = p;
	for (line = from; line < g_menuscreen_h / me_sfont_h; line++)
	{
		smalltext_out16(1, line * me_sfont_h, str, 0xffff);
		while (*p && *p != '\n')
			p++;
		if (*p == 0)
			break;
		p++; str = p;
	}
}