#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ dirtyPal; } ;
struct TYPE_6__ {TYPE_1__ m; } ;
struct TYPE_5__ {scalar_t__ renderer; int EmuOpt; } ;

/* Variables and functions */
 int EOPT_EN_CD_LEDS ; 
 int EOPT_SHOW_FPS ; 
 unsigned short* HighPal ; 
 int PAHW_32X ; 
 int PAHW_MCD ; 
 TYPE_3__ Pico ; 
 int PicoAHW ; 
 unsigned char* PicoDraw2FB ; 
 int /*<<< orphan*/  PicoDrawUpdateHighPal () ; 
 scalar_t__ RT_16BIT ; 
 TYPE_2__ currentConfig ; 
 int /*<<< orphan*/  draw_cd_leds () ; 
 int /*<<< orphan*/  emu_osd_text16 (int,scalar_t__,char const*) ; 
 scalar_t__ g_screen_height ; 
 scalar_t__ g_screen_ptr ; 
 int g_screen_width ; 

void pemu_finalize_frame(const char *fps, const char *notice)
{
	if (currentConfig.renderer != RT_16BIT && !(PicoAHW & PAHW_32X)) {
		unsigned short *pd = (unsigned short *)g_screen_ptr + 8 * g_screen_width;
		unsigned char *ps = PicoDraw2FB + 328*8 + 8;
		unsigned short *pal = HighPal;
		int i, x;
		if (Pico.m.dirtyPal)
			PicoDrawUpdateHighPal();
		for (i = 0; i < 224; i++, ps += 8)
			for (x = 0; x < 320; x++)
				*pd++ = pal[*ps++];
	}

	if (notice || (currentConfig.EmuOpt & EOPT_SHOW_FPS)) {
		if (notice)
			emu_osd_text16(4, g_screen_height - 8, notice);
		if (currentConfig.EmuOpt & EOPT_SHOW_FPS)
			emu_osd_text16(g_screen_width - 60, g_screen_height - 8, fps);
	}
	if ((PicoAHW & PAHW_MCD) && (currentConfig.EmuOpt & EOPT_EN_CD_LEDS))
		draw_cd_leds();
}