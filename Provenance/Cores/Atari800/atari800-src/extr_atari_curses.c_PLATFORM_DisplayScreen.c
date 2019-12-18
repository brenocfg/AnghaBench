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
 int A_REVERSE ; 
#define  CURSES_CENTRAL 132 
#define  CURSES_LEFT 131 
#define  CURSES_RIGHT 130 
#define  CURSES_WIDE_1 129 
#define  CURSES_WIDE_2 128 
 int /*<<< orphan*/  addch (int) ; 
 int curses_mode ; 
 int** curses_screen ; 
 int /*<<< orphan*/  move (int,int) ; 
 int /*<<< orphan*/  refresh () ; 

void PLATFORM_DisplayScreen(void)
{
	int x;
	int y;
	for (y = 0; y < 24; y++) {
		for (x = 0; x < 40; x++) {
			int ch = curses_screen[y][x];
			switch (curses_mode) {
			default:
			case CURSES_LEFT:
				move(y, x);
				break;
			case CURSES_CENTRAL:
				move(y, 20 + x);
				break;
			case CURSES_RIGHT:
				move(y, 40 + x);
				break;
			case CURSES_WIDE_1:
				move(y, x + x);
				break;
			case CURSES_WIDE_2:
				move(y, x + x);
				addch(ch);
				ch = ' ' + (ch & A_REVERSE);
				break;
			}
			addch(ch);
		}
	}
	refresh();
}