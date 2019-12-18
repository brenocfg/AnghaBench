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
 int /*<<< orphan*/  ANTIC_VideoMemset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int Screen_WIDTH ; 
 scalar_t__ Screen_atari ; 
 scalar_t__* colour_translation_table ; 
 int /*<<< orphan*/  curses_clear_rectangle (int,int,int,int) ; 

__attribute__((used)) static void ClearRectangle(int bg, int x1, int y1, int x2, int y2)
{
#ifdef USE_CURSES
	curses_clear_rectangle(x1, y1, x2, y2);
#else
	UBYTE *ptr = (UBYTE *) Screen_atari + Screen_WIDTH * 24 + 32 + x1 * 8 + y1 * (Screen_WIDTH * 8);
	int bytesperline = (x2 - x1 + 1) << 3;
	UBYTE *end_ptr = (UBYTE *) Screen_atari + Screen_WIDTH * 32 + 32 + y2 * (Screen_WIDTH * 8);
	while (ptr < end_ptr) {
#ifdef USE_COLOUR_TRANSLATION_TABLE
		ANTIC_VideoMemset(ptr, (UBYTE) colour_translation_table[bg], bytesperline);
#else
		ANTIC_VideoMemset(ptr, (UBYTE) bg, bytesperline);
#endif
		ptr += Screen_WIDTH;
	}
#endif /* USE_CURSES */
}