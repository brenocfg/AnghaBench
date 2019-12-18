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
 int /*<<< orphan*/  emu_text_out16_rot (int,int,char const*) ; 
 scalar_t__ g_screen_ptr ; 
 int /*<<< orphan*/  memset (short*,int /*<<< orphan*/ ,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void osd_text16_rot(int x, int y, const char *text)
{
	int len = strlen(text) * 8;
	short *p = (short *)g_screen_ptr + 240*(320-x) + y;

	while (len--) {
		memset(p, 0, 8*2);
		p -= 240;
	}

	emu_text_out16_rot(x, y, text);
}