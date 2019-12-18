#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ dirtyPal; } ;
struct TYPE_5__ {int* reg; } ;
struct TYPE_8__ {TYPE_2__ m; TYPE_1__ video; } ;
struct TYPE_7__ {int EmuOpt; } ;

/* Variables and functions */
 int EOPT_EN_CD_LEDS ; 
 int EOPT_SHOW_FPS ; 
 int PAHW_32X ; 
 int PAHW_MCD ; 
 int PAHW_PICO ; 
 int PAHW_SVP ; 
 int POPT_DIS_32C_BORDER ; 
 TYPE_4__ Pico ; 
 int PicoAHW ; 
 scalar_t__ PicoDraw2FB ; 
 int PicoOpt ; 
 scalar_t__ RT_8BIT_ACC ; 
 scalar_t__ RT_8BIT_FAST ; 
 TYPE_3__ currentConfig ; 
 int /*<<< orphan*/  draw_cd_leds () ; 
 int /*<<< orphan*/  draw_pico_ptr () ; 
 int /*<<< orphan*/  g_screen_ptr ; 
 scalar_t__ get_renderer () ; 
 int /*<<< orphan*/  gp2x_video_setpalette (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  localPal ; 
 int make_local_pal (int) ; 
 int /*<<< orphan*/  memset32 (int*,int,int) ; 
 int osd_fps_x ; 
 int /*<<< orphan*/  osd_text (int,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  osd_y ; 
 int /*<<< orphan*/  vidcpyM2 (int /*<<< orphan*/ ,scalar_t__,int,int) ; 

void pemu_finalize_frame(const char *fps, const char *notice)
{
	int emu_opt = currentConfig.EmuOpt;
	int ret;

	if (PicoAHW & PAHW_32X)
		; // nothing to do
	else if (get_renderer() == RT_8BIT_FAST)
	{
		// 8bit fast renderer
		if (Pico.m.dirtyPal) {
			Pico.m.dirtyPal = 0;
			ret = make_local_pal(1);
			// feed new palette to our device
			gp2x_video_setpalette(localPal, ret);
		}
		// a hack for VR
		if (PicoAHW & PAHW_SVP)
			memset32((int *)(PicoDraw2FB+328*8+328*223), 0xe0e0e0e0, 328);
		// do actual copy
		vidcpyM2(g_screen_ptr, PicoDraw2FB+328*8,
			!(Pico.video.reg[12] & 1), !(PicoOpt & POPT_DIS_32C_BORDER));
	}
	else if (get_renderer() == RT_8BIT_ACC)
	{
		// 8bit accurate renderer
		if (Pico.m.dirtyPal)
		{
			Pico.m.dirtyPal = 0;
			ret = make_local_pal(0);
			gp2x_video_setpalette(localPal, ret);
		}
	}

	if (notice)
		osd_text(4, osd_y, notice);
	if (emu_opt & EOPT_SHOW_FPS)
		osd_text(osd_fps_x, osd_y, fps);
	if ((PicoAHW & PAHW_MCD) && (emu_opt & EOPT_EN_CD_LEDS))
		draw_cd_leds();
	if (PicoAHW & PAHW_PICO)
		draw_pico_ptr();
}