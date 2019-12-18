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
struct TYPE_5__ {int frame_count; scalar_t__ pal; } ;
struct TYPE_8__ {TYPE_1__ m; } ;
struct TYPE_7__ {scalar_t__ changed; } ;
struct TYPE_6__ {int EmuOpt; int Frameskip; } ;

/* Variables and functions */
 int EOPT_EN_SRAM ; 
 int EOPT_EXT_FRMLIMIT ; 
 int EOPT_NO_FRMLIMIT ; 
 int EOPT_SHOW_FPS ; 
 int EOPT_VSYNC ; 
 scalar_t__ PGS_Running ; 
 TYPE_4__ Pico ; 
 int /*<<< orphan*/  PicoFrame () ; 
 int /*<<< orphan*/  PicoLoopPrepare () ; 
 int PicoSkipFrame ; 
 TYPE_3__ SRam ; 
 int STATUS_MSG_TIMEOUT ; 
 TYPE_2__ currentConfig ; 
 int /*<<< orphan*/  emu_loop_prep () ; 
 int /*<<< orphan*/  emu_save_load_game (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emu_set_fastforward (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emu_sound_stop () ; 
 int /*<<< orphan*/  emu_update_input () ; 
 scalar_t__ engineState ; 
 scalar_t__ flip_after_sync ; 
 int get_ticks () ; 
 int /*<<< orphan*/  main ; 
 int ms_to_ticks (int) ; 
 int* noticeMsg ; 
 int notice_msg_time ; 
 int /*<<< orphan*/  pemu_finalize_frame (char*,char*) ; 
 int /*<<< orphan*/  pemu_loop_end () ; 
 int /*<<< orphan*/  pemu_sound_start () ; 
 int /*<<< orphan*/  plat_status_msg_busy_first (char*) ; 
 int /*<<< orphan*/  plat_status_msg_clear () ; 
 int /*<<< orphan*/  plat_video_flip () ; 
 int /*<<< orphan*/  plat_video_loop_prepare () ; 
 int /*<<< orphan*/  plat_video_wait_vsync () ; 
 int /*<<< orphan*/  plat_wait_till_us (unsigned int) ; 
 int /*<<< orphan*/  pprof_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pprof_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int reset_timing ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 

void emu_loop(void)
{
	int frames_done, frames_shown;	/* actual frames for fps counter */
	int target_frametime_x3;
	unsigned int timestamp_x3 = 0;
	unsigned int timestamp_aim_x3 = 0;
	unsigned int timestamp_fps_x3 = 0;
	char *notice_msg = NULL;
	char fpsbuff[24];
	int fskip_cnt = 0;

	fpsbuff[0] = 0;

	PicoLoopPrepare();

	plat_video_loop_prepare();
	emu_loop_prep();
	pemu_sound_start();

	/* number of ticks per frame */
	if (Pico.m.pal)
		target_frametime_x3 = 3 * ms_to_ticks(1000) / 50;
	else
		target_frametime_x3 = 3 * ms_to_ticks(1000) / 60;

	reset_timing = 1;
	frames_done = frames_shown = 0;

	/* loop with resync every 1 sec. */
	while (engineState == PGS_Running)
	{
		int skip = 0;
		int diff;

		pprof_start(main);

		if (reset_timing) {
			reset_timing = 0;
			plat_video_wait_vsync();
			timestamp_aim_x3 = get_ticks() * 3;
			timestamp_fps_x3 = timestamp_aim_x3;
			fskip_cnt = 0;
		}
		else if (currentConfig.EmuOpt & EOPT_NO_FRMLIMIT) {
			timestamp_aim_x3 = get_ticks() * 3;
		}

		timestamp_x3 = get_ticks() * 3;

		// show notice_msg message?
		if (notice_msg_time != 0)
		{
			static int noticeMsgSum;
			if (timestamp_x3 - ms_to_ticks(notice_msg_time) * 3
			     > ms_to_ticks(STATUS_MSG_TIMEOUT) * 3)
			{
				notice_msg_time = 0;
				plat_status_msg_clear();
				plat_video_flip();
				plat_status_msg_clear(); /* Do it again in case of double buffering */
				notice_msg = NULL;
			}
			else {
				int sum = noticeMsg[0] + noticeMsg[1] + noticeMsg[2];
				if (sum != noticeMsgSum) {
					plat_status_msg_clear();
					noticeMsgSum = sum;
				}
				notice_msg = noticeMsg;
			}
		}

		// second changed?
		if (timestamp_x3 - timestamp_fps_x3 >= ms_to_ticks(1000) * 3)
		{
#ifdef BENCHMARK
			static int bench = 0, bench_fps = 0, bench_fps_s = 0, bfp = 0, bf[4];
			if (++bench == 10) {
				bench = 0;
				bench_fps_s = bench_fps;
				bf[bfp++ & 3] = bench_fps;
				bench_fps = 0;
			}
			bench_fps += frames_shown;
			sprintf(fpsbuff, "%02i/%02i/%02i", frames_shown, bench_fps_s, (bf[0]+bf[1]+bf[2]+bf[3])>>2);
			printf("%s\n", fpsbuff);
#else
			if (currentConfig.EmuOpt & EOPT_SHOW_FPS)
				sprintf(fpsbuff, "%02i/%02i  ", frames_shown, frames_done);
#endif
			frames_shown = frames_done = 0;
			timestamp_fps_x3 += ms_to_ticks(1000) * 3;
		}
#ifdef PFRAMES
		sprintf(fpsbuff, "%i", Pico.m.frame_count);
#endif

		diff = timestamp_aim_x3 - timestamp_x3;

		if (currentConfig.Frameskip >= 0) // frameskip enabled (or 0)
		{
			if (fskip_cnt < currentConfig.Frameskip) {
				fskip_cnt++;
				skip = 1;
			}
			else {
				fskip_cnt = 0;
			}
		}
		else if (diff < -target_frametime_x3)
		{
			/* no time left for this frame - skip */
			/* limit auto frameskip to 8 */
			if (frames_done / 8 <= frames_shown)
				skip = 1;
		}

		// don't go in debt too much
		while (diff < -target_frametime_x3 * 3) {
			timestamp_aim_x3 += target_frametime_x3;
			diff = timestamp_aim_x3 - timestamp_x3;
		}

		emu_update_input();
		if (skip) {
			int do_audio = diff > -target_frametime_x3 * 2;
			PicoSkipFrame = do_audio ? 1 : 2;
			PicoFrame();
			PicoSkipFrame = 0;
		}
		else {
			PicoFrame();
			pemu_finalize_frame(fpsbuff, notice_msg);
			frames_shown++;
		}
		frames_done++;
		timestamp_aim_x3 += target_frametime_x3;

		if (!skip && !flip_after_sync)
			plat_video_flip();

		/* frame limiter */
		if (!skip && !reset_timing
		    && !(currentConfig.EmuOpt & (EOPT_NO_FRMLIMIT|EOPT_EXT_FRMLIMIT)))
		{
			unsigned int timestamp = get_ticks();
			diff = timestamp_aim_x3 - timestamp * 3;

			// sleep or vsync if we are still too fast
			if (diff > target_frametime_x3 && (currentConfig.EmuOpt & EOPT_VSYNC)) {
				// we are too fast
				plat_video_wait_vsync();
				timestamp = get_ticks();
				diff = timestamp * 3 - timestamp_aim_x3;
			}
			if (diff > target_frametime_x3) {
				// still too fast
				plat_wait_till_us(timestamp + (diff - target_frametime_x3) / 3);
			}
		}

		if (!skip && flip_after_sync)
			plat_video_flip();

		pprof_end(main);
	}

	emu_set_fastforward(0);

	// save SRAM
	if ((currentConfig.EmuOpt & EOPT_EN_SRAM) && SRam.changed) {
		plat_status_msg_busy_first("Writing SRAM/BRAM...");
		emu_save_load_game(0, 1);
		SRam.changed = 0;
	}

	pemu_loop_end();
	emu_sound_stop();
}