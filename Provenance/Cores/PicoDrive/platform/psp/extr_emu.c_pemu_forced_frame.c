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
 int /*<<< orphan*/  EmuScanPrepare () ; 
 int /*<<< orphan*/  EmuScanSlowBegin ; 
 int /*<<< orphan*/  EmuScanSlowEnd ; 
 int /*<<< orphan*/  PDF_NONE ; 
 int POPT_ACC_SPRITES ; 
 int POPT_ALT_RENDERER ; 
 int POPT_EN_SOFTSCALE ; 
 int /*<<< orphan*/  PicoDrawSetCallbacks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PicoDrawSetOutFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PicoFrameDrawOnly () ; 
 int PicoOpt ; 
 int* VRAM_CACHED_STUFF ; 
 int /*<<< orphan*/  blit1 () ; 
 TYPE_1__ currentConfig ; 
 int /*<<< orphan*/  memset32 (int*,int,int) ; 
 int /*<<< orphan*/  memset32_uncached (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ psp_screen ; 
 int /*<<< orphan*/  sceGuSync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vidResetMode () ; 

void pemu_forced_frame(int no_scale, int do_emu)
{
	int po_old = PicoOpt;
	int eo_old = currentConfig.EmuOpt;

	PicoOpt &= ~POPT_ALT_RENDERER;
	PicoOpt |= POPT_ACC_SPRITES;
	if (!no_scale)
		PicoOpt |= POPT_EN_SOFTSCALE;
	currentConfig.EmuOpt |= 0x80;

	vidResetMode();
	memset32(VRAM_CACHED_STUFF, 0xe0e0e0e0, 512*8/4); // borders
	memset32((int *)VRAM_CACHED_STUFF + 512*232/4, 0xe0e0e0e0, 512*8/4);
	memset32_uncached((int *)psp_screen + 512*264*2/4, 0, 512*8*2/4);

	PicoDrawSetOutFormat(PDF_NONE, 0);
	PicoDrawSetCallbacks(EmuScanSlowBegin, EmuScanSlowEnd);
	EmuScanPrepare();
	PicoFrameDrawOnly();
	blit1();
	sceGuSync(0,0);

	PicoOpt = po_old;
	currentConfig.EmuOpt = eo_old;
}