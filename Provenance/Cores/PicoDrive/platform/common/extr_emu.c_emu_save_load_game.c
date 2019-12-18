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
struct TYPE_4__ {unsigned char* bram; } ;
struct TYPE_3__ {unsigned char* data; int size; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int PAHW_MCD ; 
 int POPT_EN_MCD_RAMCART ; 
 int PicoAHW ; 
 int PicoOpt ; 
 int PicoState (char*,int) ; 
 TYPE_2__* Pico_mcd ; 
 TYPE_1__ SRam ; 
 char* emu_get_save_fname (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emu_status_msg (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fread (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 int fwrite (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lprintf (char*,int,int,char*) ; 
 int /*<<< orphan*/  memcpy32 (int*,int*,int) ; 
 int /*<<< orphan*/  state_slot ; 
 int /*<<< orphan*/  sync () ; 

int emu_save_load_game(int load, int sram)
{
	int ret = 0;
	char *saveFname;

	// make save filename
	saveFname = emu_get_save_fname(load, sram, state_slot, NULL);
	if (saveFname == NULL) {
		if (!sram)
			emu_status_msg(load ? "LOAD FAILED (missing file)" : "SAVE FAILED");
		return -1;
	}

	lprintf("saveLoad (%i, %i): %s\n", load, sram, saveFname);

	if (sram)
	{
		FILE *sramFile;
		int sram_size;
		unsigned char *sram_data;
		int truncate = 1;
		if (PicoAHW & PAHW_MCD)
		{
			if (PicoOpt & POPT_EN_MCD_RAMCART) {
				sram_size = 0x12000;
				sram_data = SRam.data;
				if (sram_data)
					memcpy32((int *)sram_data, (int *)Pico_mcd->bram, 0x2000/4);
			} else {
				sram_size = 0x2000;
				sram_data = Pico_mcd->bram;
				truncate  = 0; // the .brm may contain RAM cart data after normal brm
			}
		} else {
			sram_size = SRam.size;
			sram_data = SRam.data;
		}
		if (sram_data == NULL)
			return 0; // SRam forcefully disabled for this game

		if (load)
		{
			sramFile = fopen(saveFname, "rb");
			if (!sramFile)
				return -1;
			ret = fread(sram_data, 1, sram_size, sramFile);
			ret = ret > 0 ? 0 : -1;
			fclose(sramFile);
			if ((PicoAHW & PAHW_MCD) && (PicoOpt&POPT_EN_MCD_RAMCART))
				memcpy32((int *)Pico_mcd->bram, (int *)sram_data, 0x2000/4);
		} else {
			// sram save needs some special processing
			// see if we have anything to save
			for (; sram_size > 0; sram_size--)
				if (sram_data[sram_size-1]) break;

			if (sram_size) {
				sramFile = fopen(saveFname, truncate ? "wb" : "r+b");
				if (!sramFile) sramFile = fopen(saveFname, "wb"); // retry
				if (!sramFile) return -1;
				ret = fwrite(sram_data, 1, sram_size, sramFile);
				ret = (ret != sram_size) ? -1 : 0;
				fclose(sramFile);
#ifdef __GP2X__
				sync();
#endif
			}
		}
		return ret;
	}
	else
	{
		ret = PicoState(saveFname, !load);
		if (!ret) {
#ifdef __GP2X__
			if (!load) sync();
#endif
			emu_status_msg(load ? "STATE LOADED" : "STATE SAVED");
		} else {
			emu_status_msg(load ? "LOAD FAILED" : "SAVE FAILED");
			ret = -1;
		}

		return ret;
	}
}