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
 int /*<<< orphan*/  memset (unsigned short*,int,int) ; 
 int /*<<< orphan*/  menu_draw_begin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_draw_end () ; 
 scalar_t__ menu_screen ; 

__attribute__((used)) static void load_progress_cb(int percent)
{
	int ln, len = percent * 320 / 100;
	unsigned short *dst;

	menu_draw_begin(0);
	dst = (unsigned short *)menu_screen + 321*20;

	if (len > 320) len = 320;
	for (ln = 10; ln > 0; ln--, dst += 321)
		memset(dst, 0xff, len*2);
	menu_draw_end();
}