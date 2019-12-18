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
 char** curses_screen ; 

void curses_clear_screen(void)
{
	int x;
	int y;
	for (y = 0; y < 24; y++)
		for (x = 0; x < 40; x++)
			curses_screen[y][x] = ' ';
}