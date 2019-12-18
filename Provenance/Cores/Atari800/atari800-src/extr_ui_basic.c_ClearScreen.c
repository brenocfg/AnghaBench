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
typedef  int /*<<< orphan*/  UBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ANTIC_VideoMemset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ClearRectangle (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int Screen_HEIGHT ; 
 int Screen_WIDTH ; 
 scalar_t__ Screen_atari ; 
 int* colour_translation_table ; 
 int /*<<< orphan*/  curses_clear_screen () ; 

__attribute__((used)) static void ClearScreen(void)
{
#ifdef USE_CURSES
	curses_clear_screen();
#else
#ifdef USE_COLOUR_TRANSLATION_TABLE
	ANTIC_VideoMemset((UBYTE *) Screen_atari, colour_translation_table[0x00], Screen_HEIGHT * Screen_WIDTH);
#else
	ANTIC_VideoMemset((UBYTE *) Screen_atari, 0x00, Screen_HEIGHT * Screen_WIDTH);
#endif
	ClearRectangle(0x94, 0, 0, 39, 23);
#endif /* USE_CURSES */
}