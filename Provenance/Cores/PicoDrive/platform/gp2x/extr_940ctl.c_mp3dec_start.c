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
struct TYPE_2__ {int mp3_len; int mp3_offs; scalar_t__ mp3_buffsel; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ CHECK_BUSY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JOB940_INVALIDATE_DCACHE ; 
 int /*<<< orphan*/  JOB940_MP3DECODE ; 
 int /*<<< orphan*/  JOB940_MP3RESET ; 
 int /*<<< orphan*/  MP3_SIZE_MAX ; 
 int POPT_EXT_FM ; 
 int /*<<< orphan*/  PicoMessage (char*) ; 
 int PicoOpt ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  add_job_940 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fread (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * loaded_mp3 ; 
 int /*<<< orphan*/  mp3_mem ; 
 int /*<<< orphan*/  printf (char*) ; 
 int reset_timing ; 
 TYPE_1__* shared_ctl ; 
 int /*<<< orphan*/  wait_busy_940 (int /*<<< orphan*/ ) ; 

int mp3dec_start(FILE *f, int fpos_start)
{
	if (!(PicoOpt & POPT_EXT_FM)) {
		//mp3_start_play_local(f, pos);
		return -1;
	}

	if (loaded_mp3 != f)
	{
		if (PicoMessage != NULL)
		{
			fseek(f, 0, SEEK_END);
			if (ftell(f) > 2*1024*1024)
				PicoMessage("Loading MP3...");
		}
		fseek(f, 0, SEEK_SET);
		fread(mp3_mem, 1, MP3_SIZE_MAX, f);
		if (!feof(f))
			printf("Warning: mp3 was too large, not all data loaded.\n");
		shared_ctl->mp3_len = ftell(f);
		loaded_mp3 = f;

		// as we are going to change 940's cacheable area,
		// we must invalidate it's cache..
		if (CHECK_BUSY(JOB940_MP3DECODE))
			wait_busy_940(JOB940_MP3DECODE);
		add_job_940(JOB940_INVALIDATE_DCACHE);
		reset_timing = 1;
	}

	shared_ctl->mp3_offs = fpos_start;
	shared_ctl->mp3_buffsel = 0;

	add_job_940(JOB940_MP3RESET);
	if (CHECK_BUSY(JOB940_MP3RESET))
		wait_busy_940(JOB940_MP3RESET);

	// because we decode ahea, need to start now
	if (shared_ctl->mp3_offs < shared_ctl->mp3_len) {
		add_job_940(JOB940_MP3DECODE);
	}

	return 0;
}