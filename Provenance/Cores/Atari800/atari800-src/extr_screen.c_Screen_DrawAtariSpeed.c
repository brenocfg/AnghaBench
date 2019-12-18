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
 scalar_t__ Atari800_TV_PAL ; 
 int Atari800_nframes ; 
 scalar_t__ Atari800_tv_mode ; 
 int SMALLFONT_HEIGHT ; 
 int /*<<< orphan*/  SMALLFONT_PERCENT ; 
 int SMALLFONT_WIDTH ; 
 int Screen_WIDTH ; 
 scalar_t__ Screen_atari ; 
 scalar_t__ Screen_show_atari_speed ; 
 int Screen_visible_x1 ; 
 int Screen_visible_y2 ; 
 int /*<<< orphan*/  SmallFont_DrawChar (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SmallFont_DrawInt (int /*<<< orphan*/ *,int,int,int) ; 

void Screen_DrawAtariSpeed(double cur_time)
{
	if (Screen_show_atari_speed) {
		static int percent_display = 100;
		static int last_updated = 0;
		static double last_time = 0;
		if ((cur_time - last_time) >= 0.5) {
			percent_display = (int) (100 * (Atari800_nframes - last_updated) / (cur_time - last_time) / (Atari800_tv_mode == Atari800_TV_PAL ? 50 : 60));
			last_updated = Atari800_nframes;
			last_time = cur_time;
		}
		/* if (percent_display < 99 || percent_display > 101) */
		{
			/* space for 5 digits - up to 99999% Atari speed */
			UBYTE *screen = (UBYTE *) Screen_atari + Screen_visible_x1 + 5 * SMALLFONT_WIDTH
			          	+ (Screen_visible_y2 - SMALLFONT_HEIGHT) * Screen_WIDTH;
			SmallFont_DrawChar(screen, SMALLFONT_PERCENT, 0x0c, 0x00);
			SmallFont_DrawInt(screen - SMALLFONT_WIDTH, percent_display, 0x0c, 0x00);
		}
	}
}