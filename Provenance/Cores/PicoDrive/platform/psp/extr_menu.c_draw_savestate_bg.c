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
struct TYPE_2__ {int /*<<< orphan*/  video; int /*<<< orphan*/ * vsram; int /*<<< orphan*/ * cram; int /*<<< orphan*/ * vram; } ;

/* Variables and functions */
 int PAHW_MCD ; 
 TYPE_1__ Pico ; 
 int PicoAHW ; 
 int /*<<< orphan*/  PicoCdLoadStateGfx (void*) ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  areaClose (void*) ; 
 int /*<<< orphan*/  areaRead (int /*<<< orphan*/ *,int,int,void*) ; 
 int /*<<< orphan*/  areaSeek (void*,int,int /*<<< orphan*/ ) ; 
 char* emu_GetSaveFName (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emu_forcedFrame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emu_setSaveStateCbs (int) ; 
 void* fopen (char*,char*) ; 
 void* get_oldstate_for_preview () ; 
 void* gzopen (char*,char*) ; 
 int /*<<< orphan*/  menu_prepare_bg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restore_oldstate (void*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void draw_savestate_bg(int slot)
{
	void *file, *oldstate;
	char *fname;

	fname = emu_GetSaveFName(1, 0, slot);
	if (!fname) return;

	oldstate = get_oldstate_for_preview();
	if (oldstate == NULL) return;

	if (strcmp(fname + strlen(fname) - 3, ".gz") == 0) {
		file = gzopen(fname, "rb");
		emu_setSaveStateCbs(1);
	} else {
		file = fopen(fname, "rb");
		emu_setSaveStateCbs(0);
	}

	if (file) {
		if (PicoAHW & PAHW_MCD) {
			PicoCdLoadStateGfx(file);
		} else {
			areaSeek(file, 0x10020, SEEK_SET);  // skip header and RAM in state file
			areaRead(Pico.vram, 1, sizeof(Pico.vram), file);
			areaSeek(file, 0x2000, SEEK_CUR);
			areaRead(Pico.cram, 1, sizeof(Pico.cram), file);
			areaRead(Pico.vsram, 1, sizeof(Pico.vsram), file);
			areaSeek(file, 0x221a0, SEEK_SET);
			areaRead(&Pico.video, 1, sizeof(Pico.video), file);
		}
		areaClose(file);
	}

	emu_forcedFrame(0);
	menu_prepare_bg(1, 0);

	restore_oldstate(oldstate);
}