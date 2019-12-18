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
 int /*<<< orphan*/  CASSETTE_GetPosition () ; 
 int /*<<< orphan*/  CASSETTE_GetSize () ; 
 scalar_t__ CASSETTE_STATUS_NONE ; 
 scalar_t__ CASSETTE_record ; 
 scalar_t__ CASSETTE_status ; 
 scalar_t__ SIO_LAST_READ ; 
 int SIO_last_drive ; 
 scalar_t__ SIO_last_op ; 
 scalar_t__ SIO_last_op_time ; 
 int /*<<< orphan*/  SIO_last_sector ; 
 int SMALLFONT_C ; 
 int SMALLFONT_D ; 
 int SMALLFONT_HEIGHT ; 
 int SMALLFONT_SLASH ; 
 int* SMALLFONT_WIDTH ; 
 int Screen_WIDTH ; 
 scalar_t__ Screen_atari ; 
 scalar_t__ Screen_show_disk_led ; 
 scalar_t__ Screen_show_sector_counter ; 
 int Screen_visible_x2 ; 
 int Screen_visible_y2 ; 
 int /*<<< orphan*/  SmallFont_DrawChar (int*,int,int,int) ; 
 int* SmallFont_DrawInt (int,int /*<<< orphan*/ ,int,int) ; 

void Screen_DrawDiskLED(void)
{
	if (SIO_last_op_time > 0) {
		UBYTE *screen;
		if (SIO_last_drive != 0x60)
			SIO_last_op_time--;
		screen = (UBYTE *) Screen_atari + Screen_visible_x2 - SMALLFONT_WIDTH
			+ (Screen_visible_y2 - SMALLFONT_HEIGHT) * Screen_WIDTH;
		if (SIO_last_drive == 0x60 || SIO_last_drive == 0x61) {
			if (CASSETTE_status != CASSETTE_STATUS_NONE) {
				if (Screen_show_disk_led)
					SmallFont_DrawChar(screen, SMALLFONT_C, 0x00, (UBYTE) (CASSETTE_record ? 0x2b : 0xac));

				if (Screen_show_sector_counter) {
					/* Displaying tape length during saving is pointless since it would equal the number
					of the currently-written block, which is already displayed. */
					if (!CASSETTE_record) {
						screen = SmallFont_DrawInt(screen - SMALLFONT_WIDTH, CASSETTE_GetSize(), 0x00, 0x88);
						SmallFont_DrawChar(screen, SMALLFONT_SLASH, 0x00, 0x88);
					}
					SmallFont_DrawInt(screen - SMALLFONT_WIDTH, CASSETTE_GetPosition(), 0x00, 0x88);
				}
			}
		}
		else {
			if (Screen_show_disk_led) {
				SmallFont_DrawChar(screen, SIO_last_drive, 0x00, (UBYTE) (SIO_last_op == SIO_LAST_READ ? 0xac : 0x2b));
				SmallFont_DrawChar(screen -= SMALLFONT_WIDTH, SMALLFONT_D, 0x00, (UBYTE) (SIO_last_op == SIO_LAST_READ ? 0xac : 0x2b));
			}

			if (Screen_show_sector_counter)
				SmallFont_DrawInt(screen - SMALLFONT_WIDTH, SIO_last_sector, 0x00, 0x88);
		}
	}
}