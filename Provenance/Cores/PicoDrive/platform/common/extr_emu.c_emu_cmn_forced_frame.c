#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int dirtyPal; } ;
struct TYPE_4__ {TYPE_1__ m; } ;

/* Variables and functions */
 int /*<<< orphan*/  PDF_RGB555 ; 
 int POPT_ACC_SPRITES ; 
 int POPT_ALT_RENDERER ; 
 int POPT_EN_SOFTSCALE ; 
 TYPE_2__ Pico ; 
 int /*<<< orphan*/  PicoDrawSetOutFormat (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PicoFrame () ; 
 int /*<<< orphan*/  PicoFrameDrawOnly () ; 
 int PicoOpt ; 
 int g_screen_height ; 
 int /*<<< orphan*/  g_screen_ptr ; 
 int g_screen_width ; 
 int /*<<< orphan*/  memset32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void emu_cmn_forced_frame(int no_scale, int do_emu)
{
	int po_old = PicoOpt;

	memset32(g_screen_ptr, 0, g_screen_width * g_screen_height * 2 / 4);

	PicoOpt &= ~POPT_ALT_RENDERER;
	PicoOpt |= POPT_ACC_SPRITES;
	if (!no_scale)
		PicoOpt |= POPT_EN_SOFTSCALE;

	PicoDrawSetOutFormat(PDF_RGB555, 1);
	Pico.m.dirtyPal = 1;
	if (do_emu)
		PicoFrame();
	else
		PicoFrameDrawOnly();

	PicoOpt = po_old;
}