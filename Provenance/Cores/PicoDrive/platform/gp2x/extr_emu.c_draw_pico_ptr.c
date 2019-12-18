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
struct TYPE_4__ {int* reg; } ;
struct TYPE_6__ {TYPE_1__ video; } ;
struct TYPE_5__ {int EmuOpt; } ;

/* Variables and functions */
 int EOPT_WIZ_TEAR_FIX ; 
 int PICO_PEN_ADJUST_X ; 
 int PICO_PEN_ADJUST_Y ; 
 int POPT_DIS_32C_BORDER ; 
 TYPE_3__ Pico ; 
 int PicoOpt ; 
 int RT_16BIT ; 
 TYPE_2__ currentConfig ; 
 scalar_t__ g_screen_ptr ; 
 scalar_t__ pico_inp_mode ; 
 int pico_pen_x ; 
 int pico_pen_y ; 

__attribute__((used)) static void draw_pico_ptr(void)
{
	unsigned short *p = (unsigned short *)g_screen_ptr;
	int x, y, pitch = 320;

	// only if pen enabled and for 16bit modes
	if (pico_inp_mode == 0 || currentConfig.EmuOpt != RT_16BIT)
		return;

	x = pico_pen_x + PICO_PEN_ADJUST_X;
	y = pico_pen_y + PICO_PEN_ADJUST_Y;
	if (!(Pico.video.reg[12]&1) && !(PicoOpt & POPT_DIS_32C_BORDER))
		x += 32;

	if (currentConfig.EmuOpt & EOPT_WIZ_TEAR_FIX) {
		pitch = 240;
		p += (319 - x) * pitch + y;
	} else
		p += x + y * pitch;

	p[0]       ^= 0xffff;
	p[pitch-1] ^= 0xffff;
	p[pitch]   ^= 0xffff;
	p[pitch+1] ^= 0xffff;
	p[pitch*2] ^= 0xffff;
}