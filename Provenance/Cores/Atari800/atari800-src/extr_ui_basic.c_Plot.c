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
 int /*<<< orphan*/  ANTIC_VideoPutByte (int /*<<< orphan*/ ,int) ; 
 int Screen_WIDTH ; 
 scalar_t__ Screen_atari ; 
 int* charset ; 
 scalar_t__* colour_translation_table ; 
 int /*<<< orphan*/  curses_putch (int,int,int,int,int) ; 

__attribute__((used)) static void Plot(int fg, int bg, int ch, int x, int y)
{
#ifdef USE_CURSES
	curses_putch(x, y, ch, (UBYTE) fg, (UBYTE) bg);
#else /* USE_CURSES */
	const UBYTE *font_ptr = charset + (ch & 0x7f) * 8;
	UBYTE *ptr = (UBYTE *) Screen_atari + 24 * Screen_WIDTH + 32 + y * (8 * Screen_WIDTH) + x * 8;
	int i;
	int j;

	for (i = 0; i < 8; i++) {
		UBYTE data = *font_ptr++;
		for (j = 0; j < 8; j++) {
#ifdef USE_COLOUR_TRANSLATION_TABLE
			ANTIC_VideoPutByte(ptr++, (UBYTE) colour_translation_table[data & 0x80 ? fg : bg]);
#else
			ANTIC_VideoPutByte(ptr++, (UBYTE) (data & 0x80 ? fg : bg));
#endif
			data <<= 1;
		}
		ptr += Screen_WIDTH - 8;
	}
#endif /* USE_CURSES */
}