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
 scalar_t__ Atari800_keyboard_leds ; 
 int PIA_PORTB ; 
 int PIA_PORTB_mask ; 
 int SMALLFONT_HEIGHT ; 
 int SMALLFONT_L ; 
 int SMALLFONT_WIDTH ; 
 int Screen_WIDTH ; 
 scalar_t__ Screen_atari ; 
 scalar_t__ Screen_show_1200_leds ; 
 int Screen_visible_x1 ; 
 int Screen_visible_y2 ; 
 int /*<<< orphan*/  SmallFont_DrawChar (int*,int,int,int) ; 

void Screen_Draw1200LED(void)
{
	if (Screen_show_1200_leds && Atari800_keyboard_leds) {
		UBYTE *screen = (UBYTE *) Screen_atari + Screen_visible_x1 + SMALLFONT_WIDTH * 10
			+ (Screen_visible_y2 - SMALLFONT_HEIGHT) * Screen_WIDTH;
		UBYTE portb = PIA_PORTB | PIA_PORTB_mask;
		if ((portb & 0x04) == 0) {
			SmallFont_DrawChar(screen, SMALLFONT_L, 0x00, 0x36);
			SmallFont_DrawChar(screen + SMALLFONT_WIDTH, 1, 0x00, 0x36);
		}
		screen += SMALLFONT_WIDTH * 3;
		if ((portb & 0x08) == 0) {
			SmallFont_DrawChar(screen, SMALLFONT_L, 0x00, 0x36);
			SmallFont_DrawChar(screen + SMALLFONT_WIDTH, 2, 0x00, 0x36);
		}
	}
}