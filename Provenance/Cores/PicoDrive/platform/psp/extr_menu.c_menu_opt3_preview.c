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
struct TYPE_3__ {int* reg; } ;
struct TYPE_4__ {TYPE_1__ video; TYPE_1__* vsram; TYPE_1__* cram; TYPE_1__* vram; } ;
typedef  int /*<<< orphan*/  Bytef ;

/* Variables and functions */
 TYPE_2__ Pico ; 
 char* bg_buffer ; 
 int /*<<< orphan*/  emu_forcedFrame (int /*<<< orphan*/ ) ; 
 void* get_oldstate_for_preview () ; 
 int /*<<< orphan*/  lprintf (char*,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  memset32_uncached (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  menu_prepare_bg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psp_screen ; 
 int /*<<< orphan*/  restore_oldstate (void*) ; 
 scalar_t__ rom_loaded ; 
 int uncompress (int /*<<< orphan*/ *,unsigned long*,void*,unsigned long) ; 

__attribute__((used)) static void menu_opt3_preview(int is_32col)
{
	void *oldstate = NULL;

	if (!rom_loaded || ((Pico.video.reg[12]&1)^1) != is_32col)
	{
		extern char bgdatac32_start[], bgdatac40_start[];
		extern int bgdatac32_size, bgdatac40_size;
		void *bgdata = is_32col ? bgdatac32_start : bgdatac40_start;
		unsigned long insize = is_32col ? bgdatac32_size : bgdatac40_size, outsize = 65856;
		int ret;
		ret = uncompress((Bytef *)bg_buffer, &outsize, bgdata, insize);
		if (ret == 0)
		{
			if (rom_loaded) oldstate = get_oldstate_for_preview();
			memcpy(Pico.vram,  bg_buffer, sizeof(Pico.vram));
			memcpy(Pico.cram,  (char *)bg_buffer + 0x10000, 0x40*2);
			memcpy(Pico.vsram, (char *)bg_buffer + 0x10080, 0x40*2);
			memcpy(&Pico.video,(char *)bg_buffer + 0x10100, 0x40);
		}
		else
			lprintf("uncompress returned %i\n", ret);
	}

	memset32_uncached(psp_screen, 0, 512*272*2/4);
	emu_forcedFrame(0);
	menu_prepare_bg(1, 0);

	if (oldstate) restore_oldstate(oldstate);
}