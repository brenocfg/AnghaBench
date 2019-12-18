#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int dirtyPal; int frame_count; scalar_t__ pal; } ;
struct TYPE_6__ {int* reg; } ;
struct TYPE_10__ {TYPE_2__ m; TYPE_1__ video; } ;
struct TYPE_9__ {scalar_t__ changed; } ;
struct TYPE_8__ {scalar_t__ CPUclock; int EmuOpt; int Frameskip; } ;

/* Variables and functions */
 int EOPT_EN_SOUND ; 
 int /*<<< orphan*/  EmuScanPrepare () ; 
 int PAHW_MCD ; 
 scalar_t__ PGS_Menu ; 
 scalar_t__ PGS_Running ; 
 TYPE_5__ Pico ; 
 int PicoAHW ; 
 int /*<<< orphan*/  PicoCDBufferFree () ; 
 int /*<<< orphan*/  PicoCDBufferInit () ; 
 int /*<<< orphan*/  PicoFrame () ; 
 int PicoOpt ; 
 int /*<<< orphan*/ * PsndOut ; 
 TYPE_4__ SRam ; 
 int /*<<< orphan*/  SkipFrame () ; 
 int /*<<< orphan*/  blit2 (char*,char*,int) ; 
 int /*<<< orphan*/  clearArea (int) ; 
 TYPE_3__ currentConfig ; 
 int /*<<< orphan*/  emu_msg_cb (char*) ; 
 int /*<<< orphan*/  emu_save_load_game (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emu_set_fastforward (int /*<<< orphan*/ ) ; 
 scalar_t__ engineState ; 
 int /*<<< orphan*/  lprintf (char*,...) ; 
 int /*<<< orphan*/  memset32_uncached (int*,int /*<<< orphan*/ ,int) ; 
 int mp3_init () ; 
 int* noticeMsg ; 
 int noticeMsgTime ; 
 int /*<<< orphan*/  pemu_sound_start () ; 
 int /*<<< orphan*/  pemu_sound_stop () ; 
 scalar_t__ psp_get_cpu_clock () ; 
 int psp_set_cpu_clock (scalar_t__) ; 
 scalar_t__ psp_video_get_active_fb () ; 
 int reset_timing ; 
 int /*<<< orphan*/  sceDisplayWaitVblankStart () ; 
 int /*<<< orphan*/  sceGuSync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* sceKernelGetSystemTimeLow () ; 
 int /*<<< orphan*/  set_scaling_params () ; 
 int /*<<< orphan*/  simpleWait (unsigned int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 
 int /*<<< orphan*/  updateKeys () ; 
 int /*<<< orphan*/  vidResetMode () ; 

void pemu_loop(void)
{
	static int mp3_init_done = 0;
	char fpsbuff[24]; // fps count c string
	unsigned int tval, tval_thissec = 0; // timing
	int target_fps, target_frametime, lim_time, tval_diff, i, oldmodes = 0;
	int pframes_done, pframes_shown; // "period" frames, used for sync
	int  frames_done,  frames_shown, tval_fpsc = 0; // actual frames
	char *notice = NULL;

	lprintf("entered emu_Loop()\n");

	fpsbuff[0] = 0;

	if (currentConfig.CPUclock != psp_get_cpu_clock()) {
		lprintf("setting cpu clock to %iMHz... ", currentConfig.CPUclock);
		i = psp_set_cpu_clock(currentConfig.CPUclock);
		lprintf(i ? "failed\n" : "done\n");
		currentConfig.CPUclock = psp_get_cpu_clock();
	}

	// make sure we are in correct mode
	vidResetMode();
	clearArea(1);
	Pico.m.dirtyPal = 1;
	oldmodes = ((Pico.video.reg[12]&1)<<2) ^ 0xc;

	// pal/ntsc might have changed, reset related stuff
	target_fps = Pico.m.pal ? 50 : 60;
	target_frametime = Pico.m.pal ? (1000000<<8)/50 : (1000000<<8)/60+1;
	reset_timing = 1;

	if (PicoAHW & PAHW_MCD) {
		// prepare CD buffer
		PicoCDBufferInit();
		// mp3...
		if (!mp3_init_done) {
			i = mp3_init();
			mp3_init_done = 1;
			if (i) { engineState = PGS_Menu; return; }
		}
	}

	// prepare sound stuff
	PsndOut = NULL;
	if (currentConfig.EmuOpt & EOPT_EN_SOUND)
	{
		pemu_sound_start();
	}

	sceDisplayWaitVblankStart();
	pframes_shown = pframes_done =
	 frames_shown =  frames_done = 0;

	tval_fpsc = sceKernelGetSystemTimeLow();

	// loop?
	while (engineState == PGS_Running)
	{
		int modes;

		tval = sceKernelGetSystemTimeLow();
		if (reset_timing || tval < tval_fpsc) {
			//stdbg("timing reset");
			reset_timing = 0;
			tval_thissec = tval;
			pframes_shown = pframes_done = 0;
		}

		// show notice message?
		if (noticeMsgTime) {
			static int noticeMsgSum;
			if (tval - noticeMsgTime > 2000000) { // > 2.0 sec
				noticeMsgTime = 0;
				clearArea(0);
				notice = 0;
			} else {
				int sum = noticeMsg[0]+noticeMsg[1]+noticeMsg[2];
				if (sum != noticeMsgSum) { clearArea(0); noticeMsgSum = sum; }
				notice = noticeMsg;
			}
		}

		// check for mode changes
		modes = ((Pico.video.reg[12]&1)<<2)|(Pico.video.reg[1]&8);
		if (modes != oldmodes) {
			oldmodes = modes;
			clearArea(1);
			set_scaling_params();
		}

		// second passed?
		if (tval - tval_fpsc >= 1000000)
		{
			if (currentConfig.EmuOpt & 2)
				sprintf(fpsbuff, "%02i/%02i  ", frames_shown, frames_done);
			frames_done = frames_shown = 0;
			tval_fpsc += 1000000;
		}

		if (tval - tval_thissec >= 1000000)
		{
			// missing 1 frame?
			if (currentConfig.Frameskip < 0 && pframes_done < target_fps) {
				SkipFrame(); pframes_done++; frames_done++;
			}

			tval_thissec += 1000000;

			if (currentConfig.Frameskip < 0) {
				pframes_done  -= target_fps; if (pframes_done  < 0) pframes_done  = 0;
				pframes_shown -= target_fps; if (pframes_shown < 0) pframes_shown = 0;
				if (pframes_shown > pframes_done) pframes_shown = pframes_done;
			} else {
				pframes_done = pframes_shown = 0;
			}
		}
#ifdef PFRAMES
		sprintf(fpsbuff, "%i", Pico.m.frame_count);
#endif

		lim_time = (pframes_done+1) * target_frametime;
		if (currentConfig.Frameskip >= 0) // frameskip enabled
		{
			for (i = 0; i < currentConfig.Frameskip; i++) {
				updateKeys();
				SkipFrame(); pframes_done++; frames_done++;
				if (!(currentConfig.EmuOpt&0x40000)) { // do framelimitting if needed
					int tval_diff;
					tval = sceKernelGetSystemTimeLow();
					tval_diff = (int)(tval - tval_thissec) << 8;
					if (tval_diff < lim_time) // we are too fast
						simpleWait(tval + ((lim_time - tval_diff)>>8));
				}
				lim_time += target_frametime;
			}
		}
		else // auto frameskip
		{
			int tval_diff;
			tval = sceKernelGetSystemTimeLow();
			tval_diff = (int)(tval - tval_thissec) << 8;
			if (tval_diff > lim_time && (pframes_done/16 < pframes_shown))
			{
				// no time left for this frame - skip
				if (tval_diff - lim_time >= (300000<<8)) {
					reset_timing = 1;
					continue;
				}
				updateKeys();
				SkipFrame(); pframes_done++; frames_done++;
				continue;
			}
		}

		updateKeys();

		if (!(PicoOpt&0x10))
			EmuScanPrepare();

		PicoFrame();

		sceGuSync(0,0);

		// check time
		tval = sceKernelGetSystemTimeLow();
		tval_diff = (int)(tval - tval_thissec) << 8;

		blit2(fpsbuff, notice, tval_diff > lim_time);

		if (currentConfig.Frameskip < 0 && tval_diff - lim_time >= (300000<<8)) { // slowdown detection
			reset_timing = 1;
		}
		else if (!(currentConfig.EmuOpt&0x40000) || currentConfig.Frameskip < 0)
		{
			// sleep if we are still too fast
			if (tval_diff < lim_time)
			{
				// we are too fast
				simpleWait(tval + ((lim_time - tval_diff) >> 8));
			}
		}

		pframes_done++; pframes_shown++;
		 frames_done++;  frames_shown++;
	}


	emu_set_fastforward(0);

	if (PicoAHW & PAHW_MCD) PicoCDBufferFree();

	if (PsndOut != NULL) {
		pemu_sound_stop();
		PsndOut = NULL;
	}

	// save SRAM
	if ((currentConfig.EmuOpt & 1) && SRam.changed) {
		emu_msg_cb("Writing SRAM/BRAM..");
		emu_save_load_game(0, 1);
		SRam.changed = 0;
	}

	// clear fps counters and stuff
	memset32_uncached((int *)psp_video_get_active_fb() + 512*264*2/4, 0, 512*8*2/4);
}