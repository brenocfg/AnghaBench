#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int key_t ;

/* Variables and functions */
 int IPC_CREAT ; 
 int IPC_EXCL ; 
 int ftok (char*,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 void* pp_counters ; 
 unsigned int pprof_get_one () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 void* shmat (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int shmemid ; 
 int shmget (int,int,int) ; 

void pprof_init(void)
{
	int this_is_new_shmem = 1;
	key_t shmemkey;
	void *shmem;

#ifndef PPROF_TOOL
	unsigned int tmp = pprof_get_one();
	printf("pprof: measured diff is %u\n", pprof_get_one() - tmp);
#endif

	shmemkey = ftok(".", 0x02ABC32E);
	if (shmemkey == -1)
	{
		perror("pprof: ftok failed");
		return;
	}

#ifndef PPROF_TOOL
	shmemid = shmget(shmemkey, sizeof(*pp_counters),
		IPC_CREAT | IPC_EXCL | 0644);
	if (shmemid == -1)
#endif
	{
		shmemid = shmget(shmemkey, sizeof(*pp_counters),
				0644);
		if (shmemid == -1)
		{
			perror("pprof: shmget failed");
			return;
		}
		this_is_new_shmem = 0;
	}

	shmem = shmat(shmemid, NULL, 0);
	if (shmem == (void *)-1)
	{
		perror("pprof: shmat failed");
		return;
	}

	pp_counters = shmem;
	if (this_is_new_shmem) {
		memset(pp_counters, 0, sizeof(*pp_counters));
		printf("pprof: pp_counters cleared.\n");
	}
}