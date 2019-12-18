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
typedef  int UBYTE ;

/* Variables and functions */
 int A_REVERSE ; 
 int** curses_screen ; 

void curses_putch(int x, int y, int ascii, UBYTE fg, UBYTE bg)
{
	/* handle line drawing chars */
	switch (ascii) {
	case 18:
		ascii = '-';
		break;
	case 17:
	case 3:
		ascii = '/';
		break;
	case 26:
	case 5:
		ascii = '\\';
		break;
	case 124:
		ascii = '|';
		break;
	default:
		break;
	}
	if ((bg & 0xf) > (fg & 0xf))
		curses_screen[y][x] = ascii + A_REVERSE;
	else
		curses_screen[y][x] = ascii;
}