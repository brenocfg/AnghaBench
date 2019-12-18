#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  binpath ;
struct TYPE_7__ {scalar_t__ frame_count; } ;
struct TYPE_9__ {TYPE_1__ m; } ;
struct TYPE_8__ {int baseclock; int rate; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* CODE940_FILE ; 
 int /*<<< orphan*/  JOB940_INITALL ; 
 int PBTN_MBACK ; 
 int PBTN_MOK ; 
 TYPE_6__ Pico ; 
 int /*<<< orphan*/  YM2612Init_ (int,int) ; 
 int /*<<< orphan*/  add_job_940 (int /*<<< orphan*/ ) ; 
 scalar_t__ crashed_940 ; 
 int /*<<< orphan*/  emu_make_path (char*,char*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fread (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 TYPE_2__* g_screen_ptr ; 
 int /*<<< orphan*/  gp2x_video_flip2 () ; 
 int /*<<< orphan*/  in_menu_wait (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  internal_reset () ; 
 int /*<<< orphan*/ * loaded_mp3 ; 
 int /*<<< orphan*/  memcpy (scalar_t__,unsigned char*,int) ; 
 int* memregl ; 
 int* memregs ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pause940 (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  reset940 (int,int) ; 
 TYPE_2__* shared_ctl ; 
 TYPE_2__* shared_data ; 
 scalar_t__ shared_mem ; 
 int /*<<< orphan*/  text_out16 (int,int,char*) ; 

void YM2612Init_940(int baseclock, int rate)
{
	static int oldrate;

	// HACK
	if (Pico.m.frame_count > 0 && !crashed_940 && rate == oldrate)
		return;

	printf("YM2612Init_940()\n");
	printf("Mem usage: shared_data: %i, shared_ctl: %i\n", sizeof(*shared_data), sizeof(*shared_ctl));

	reset940(1, 2);
	pause940(1);

	memregs[0x3B40>>1] = 0;      // disable DUALCPU interrupts for 920
	memregs[0x3B42>>1] = 1;      // enable  DUALCPU interrupts for 940

	memregl[0x4504>>2] = 0;        // make sure no FIQs will be generated
	memregl[0x4508>>2] = ~(1<<26); // unmask DUALCPU ints in the undocumented 940's interrupt controller


	if (crashed_940)
	{
		unsigned char ucData[1024];
		int nRead, nLen = 0;
		char binpath[512];
		FILE *fp;

		emu_make_path(binpath, CODE940_FILE, sizeof(binpath));
		fp = fopen(binpath, "rb");
		if(!fp)
		{
			memset(g_screen_ptr, 0, 320*240*2);
			text_out16(10, 100, "failed to open required file:");
			text_out16(10, 110, CODE940_FILE);
			gp2x_video_flip2();
			in_menu_wait(PBTN_MOK|PBTN_MBACK, NULL, 100);
			printf("failed to open %s\n", binpath);
			exit(1);
		}

		while(1)
		{
			nRead = fread(ucData, 1, 1024, fp);
			if(nRead <= 0)
				break;
			memcpy(shared_mem + nLen, ucData, nRead);
			nLen += nRead;
		}
		fclose(fp);
		crashed_940 = 0;
	}

	memset(shared_data, 0, sizeof(*shared_data));
	memset(shared_ctl,  0, sizeof(*shared_ctl));

	/* cause local ym2612 to init REGS */
	YM2612Init_(baseclock, rate);

	internal_reset();

	loaded_mp3 = NULL;

	memregs[0x3B46>>1] = 0xffff; // clear pending DUALCPU interrupts for 940
	memregl[0x4500>>2] = 0xffffffff; // clear pending IRQs in SRCPND
	memregl[0x4510>>2] = 0xffffffff; // clear pending IRQs in INTPND

	/* start the 940 */
	reset940(0, 2);
	pause940(0);

	// YM2612ResetChip_940(); // will be done on JOB940_YM2612INIT

	/* now cause 940 to init it's ym2612 stuff */
	shared_ctl->baseclock = baseclock;
	shared_ctl->rate = rate;
	add_job_940(JOB940_INITALL);

	oldrate = rate;
}