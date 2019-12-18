#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int EmuOpt; } ;

/* Variables and functions */
 int EOPT_EN_CD_LEDS ; 
 int EOPT_SHOW_FPS ; 
 int PAHW_MCD ; 
 int PicoAHW ; 
 TYPE_1__ currentConfig ; 
 int /*<<< orphan*/  draw_cd_leds () ; 
 int /*<<< orphan*/  emu_osd_text16 (int,int /*<<< orphan*/ ,char const*) ; 
 int g_osd_fps_x ; 
 int /*<<< orphan*/  g_osd_y ; 

void pemu_finalize_frame(const char *fps, const char *notice)
{
	if (notice && notice[0])
		emu_osd_text16(2, g_osd_y, notice);
	if (fps && fps[0] && (currentConfig.EmuOpt & EOPT_SHOW_FPS))
		emu_osd_text16(g_osd_fps_x, g_osd_y, fps);
	if ((PicoAHW & PAHW_MCD) && (currentConfig.EmuOpt & EOPT_EN_CD_LEDS))
		draw_cd_leds();
}