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
 int PBTN_DOWN ; 
 int PBTN_L ; 
 int PBTN_LEFT ; 
 int PBTN_MA2 ; 
 int PBTN_MA3 ; 
 int PBTN_MBACK ; 
 int PBTN_MOK ; 
 int PBTN_R ; 
 int PBTN_RIGHT ; 
 int PBTN_UP ; 
 int /*<<< orphan*/  PDRAW_32X_ON ; 
 int /*<<< orphan*/  PDRAW_LAYERA_ON ; 
 int /*<<< orphan*/  PDRAW_LAYERB_ON ; 
 int /*<<< orphan*/  PDRAW_SPRITES_HI_ON ; 
 int /*<<< orphan*/  PDRAW_SPRITES_LOW_ON ; 
 char* PDebug32x () ; 
 int /*<<< orphan*/  PDebugCPUStep () ; 
 int /*<<< orphan*/  PDebugDumpMem () ; 
 char* PDebugMain () ; 
 int /*<<< orphan*/  PDebugShowPalette (scalar_t__,int) ; 
 int /*<<< orphan*/  PDebugShowSprite (unsigned short*,int,int) ; 
 int /*<<< orphan*/  PDebugShowSpriteStats (unsigned short*,int) ; 
 char* PDebugSpriteList () ; 
 int /*<<< orphan*/  PicoDrawMask ; 
 int /*<<< orphan*/  PicoFrame () ; 
 int PicoSkipFrame ; 
 int /*<<< orphan*/ * PsndOut ; 
 int /*<<< orphan*/  draw_frame_debug () ; 
 int /*<<< orphan*/  draw_text_debug (char*,int,int) ; 
 int g_menuscreen_h ; 
 scalar_t__ g_menuscreen_ptr ; 
 int g_menuscreen_w ; 
 int in_menu_wait (int,int /*<<< orphan*/ *,int) ; 
 int in_menu_wait_any (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  make_bg (int) ; 
 int me_mfont_h ; 
 int me_sfont_h ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  menu_draw_begin (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_draw_end () ; 
 int /*<<< orphan*/  mkdir (char*,int) ; 
 int /*<<< orphan*/  mplayer_loop () ; 
 int /*<<< orphan*/  pemu_forced_frame (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plat_debug_cat (char*) ; 
 int /*<<< orphan*/  smalltext_out16 (int /*<<< orphan*/ ,int,char*,int) ; 

__attribute__((used)) static void debug_menu_loop(void)
{
	int inp, mode = 0;
	int spr_offs = 0, dumped = 0;
	char *tmp;

	while (1)
	{
		menu_draw_begin(1, 0);
		switch (mode)
		{
			case 0: tmp = PDebugMain();
				plat_debug_cat(tmp);
				draw_text_debug(tmp, 0, 0);
				if (dumped) {
					smalltext_out16(g_menuscreen_w - 6 * me_sfont_h,
						g_menuscreen_h - me_mfont_h, "dumped", 0xffff);
					dumped = 0;
				}
				break;
			case 1: draw_frame_debug();
				break;
			case 2: pemu_forced_frame(1, 0);
				make_bg(1);
				PDebugShowSpriteStats((unsigned short *)g_menuscreen_ptr + (g_menuscreen_h/2 - 240/2)*g_menuscreen_w +
					g_menuscreen_w/2 - 320/2, g_menuscreen_w);
				break;
			case 3: memset(g_menuscreen_ptr, 0, g_menuscreen_w * g_menuscreen_h * 2);
				PDebugShowPalette(g_menuscreen_ptr, g_menuscreen_w);
				PDebugShowSprite((unsigned short *)g_menuscreen_ptr + g_menuscreen_w*120 + g_menuscreen_w/2 + 16,
					g_menuscreen_w, spr_offs);
				draw_text_debug(PDebugSpriteList(), spr_offs, 6);
				break;
			case 4: tmp = PDebug32x();
				draw_text_debug(tmp, 0, 0);
				break;
		}
		menu_draw_end();

		inp = in_menu_wait(PBTN_MOK|PBTN_MBACK|PBTN_MA2|PBTN_MA3|PBTN_L|PBTN_R |
					PBTN_UP|PBTN_DOWN|PBTN_LEFT|PBTN_RIGHT, NULL, 70);
		if (inp & PBTN_MBACK) return;
		if (inp & PBTN_L) { mode--; if (mode < 0) mode = 4; }
		if (inp & PBTN_R) { mode++; if (mode > 4) mode = 0; }
		switch (mode)
		{
			case 0:
				if (inp & PBTN_MOK)
					PDebugCPUStep();
				if (inp & PBTN_MA3) {
					while (inp & PBTN_MA3)
						inp = in_menu_wait_any(NULL, -1);
					mplayer_loop();
				}
				if ((inp & (PBTN_MA2|PBTN_LEFT)) == (PBTN_MA2|PBTN_LEFT)) {
					mkdir("dumps", 0777);
					PDebugDumpMem();
					while (inp & PBTN_MA2) inp = in_menu_wait_any(NULL, -1);
					dumped = 1;
				}
				break;
			case 1:
				if (inp & PBTN_LEFT)  PicoDrawMask ^= PDRAW_LAYERB_ON;
				if (inp & PBTN_RIGHT) PicoDrawMask ^= PDRAW_LAYERA_ON;
				if (inp & PBTN_DOWN)  PicoDrawMask ^= PDRAW_SPRITES_LOW_ON;
				if (inp & PBTN_UP)    PicoDrawMask ^= PDRAW_SPRITES_HI_ON;
				if (inp & PBTN_MA2)   PicoDrawMask ^= PDRAW_32X_ON;
				if (inp & PBTN_MOK) {
					PsndOut = NULL; // just in case
					PicoSkipFrame = 1;
					PicoFrame();
					PicoSkipFrame = 0;
					while (inp & PBTN_MOK) inp = in_menu_wait_any(NULL, -1);
				}
				break;
			case 3:
				if (inp & PBTN_DOWN)  spr_offs++;
				if (inp & PBTN_UP)    spr_offs--;
				if (spr_offs < 0) spr_offs = 0;
				break;
		}
	}
}