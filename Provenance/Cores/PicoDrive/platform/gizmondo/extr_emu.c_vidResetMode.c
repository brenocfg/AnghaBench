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
struct TYPE_4__ {int dirtyPal; } ;
struct TYPE_6__ {TYPE_1__ m; } ;
struct TYPE_5__ {int EmuOpt; } ;

/* Variables and functions */
 int /*<<< orphan*/  EmuScanBegin16 ; 
 int /*<<< orphan*/  EmuScanBegin8 ; 
 int /*<<< orphan*/  PDF_NONE ; 
 int /*<<< orphan*/  PDF_RGB555 ; 
 TYPE_3__ Pico ; 
 int /*<<< orphan*/  PicoDrawSetCallbacks (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PicoDrawSetOutFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PicoOpt ; 
 TYPE_2__ currentConfig ; 
 int /*<<< orphan*/ * fb_lock (int) ; 
 int /*<<< orphan*/  fb_unlock () ; 
 int /*<<< orphan*/ * giz_screen ; 
 int* localPal ; 
 int /*<<< orphan*/  memset32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vidResetMode(void)
{
	giz_screen = fb_lock(1);

	if (PicoOpt&0x10) {
	} else if (currentConfig.EmuOpt&0x80) {
		PicoDrawSetOutFormat(PDF_RGB555, 0);
		PicoDrawSetCallbacks(EmuScanBegin16, NULL);
	} else {
		PicoDrawSetOutFormat(PDF_NONE, 0);
		PicoDrawSetCallbacks(EmuScanBegin8, NULL);
	}
	if ((PicoOpt&0x10) || !(currentConfig.EmuOpt&0x80)) {
		// setup pal for 8-bit modes
		localPal[0xc0] = 0x0600;
		localPal[0xd0] = 0xc000;
		localPal[0xe0] = 0x0000; // reserved pixels for OSD
		localPal[0xf0] = 0xffff;
	}
	Pico.m.dirtyPal = 1;

	memset32(giz_screen, 0, 321*240*2/4);
	if (currentConfig.EmuOpt&0x8000) {
		fb_unlock();
		giz_screen = fb_lock(0);
		memset32(giz_screen, 0, 321*240*2/4);
	}
	fb_unlock();
	giz_screen = NULL;
}