#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ucData ;
struct TYPE_6__ {int baseclock; int rate; int busy; scalar_t__* jobs; } ;
typedef  TYPE_1__ _940_data_t ;
typedef  TYPE_1__ _940_ctl_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ JOB940_INITALL ; 
 unsigned char* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int MP3_SIZE_MAX ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  Pause940 (int) ; 
 int /*<<< orphan*/  Reset940 (int,int) ; 
 int crashed_940 ; 
 int errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/ * g_argv ; 
 int* gp2x_memregl ; 
 int* gp2x_memregs ; 
 int /*<<< orphan*/  memdev ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mmap (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned char* mp3_mem ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  read_to_upper (unsigned char*,unsigned char*,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* shared_ctl ; 
 TYPE_1__* shared_data ; 
 unsigned char* shared_mem ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

void YM2612Init_940(int baseclock, int rate)
{
	printf("YM2612Init_940()\n");
	printf("Mem usage: shared_data: %i, shared_ctl: %i\n", sizeof(*shared_data), sizeof(*shared_ctl));

	Reset940(1, 2);
	Pause940(1);

	gp2x_memregs[0x3B46>>1] = 0xffff; // clear pending DUALCPU interrupts for 940
	gp2x_memregs[0x3B42>>1] = 0xffff; // enable DUALCPU interrupts for 940

	gp2x_memregl[0x4508>>2] = ~(1<<26); // unmask DUALCPU ints in the undocumented 940's interrupt controller

	if (shared_mem == NULL)
	{
		shared_mem = (unsigned char *) mmap(0, 0x210000, PROT_READ|PROT_WRITE, MAP_SHARED, memdev, 0x2000000);
		if(shared_mem == MAP_FAILED)
		{
			printf("mmap(shared_data) failed with %i\n", errno);
			exit(1);
		}
		shared_data = (_940_data_t *) (shared_mem+0x100000);
		/* this area must not get buffered on either side */
		shared_ctl =  (_940_ctl_t *)  (shared_mem+0x200000);
		mp3_mem = (unsigned char *) mmap(0, MP3_SIZE_MAX, PROT_READ|PROT_WRITE, MAP_SHARED, memdev, 0x3000000);
		if (mp3_mem == MAP_FAILED)
		{
			printf("mmap(mp3_mem) failed with %i\n", errno);
			exit(1);
		}
		crashed_940 = 1;
	}

	if (crashed_940)
	{
		unsigned char ucData[1024];
		int i;
		char binpath[1024];
		FILE *fp;

		strncpy(binpath, g_argv[0], 1023);
		binpath[1023] = 0;
		for (i = strlen(binpath); i > 0; i--)
			if (binpath[i] == '/') { binpath[i] = 0; break; }
		strcat(binpath, "/code940.bin");

		fp = fopen(binpath, "rb");
		if(!fp)
		{
			printf("failed to open %s\n", binpath);
			exit(1);
		}

		read_to_upper(shared_mem, ucData, sizeof(ucData), fp);
		fclose(fp);
		crashed_940 = 0;
	}

	memset(shared_data, 0, sizeof(*shared_data));
	memset(shared_ctl,  0, sizeof(*shared_ctl));

	/* now cause 940 to init it's ym2612 stuff */
	shared_ctl->baseclock = baseclock;
	shared_ctl->rate = rate;
	shared_ctl->jobs[0] = JOB940_INITALL;
	shared_ctl->jobs[1] = 0;
	shared_ctl->busy = 1;

	/* start the 940 */
	Reset940(0, 2);
	Pause940(0);
}