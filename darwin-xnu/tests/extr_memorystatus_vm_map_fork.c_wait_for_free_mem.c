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
typedef  int /*<<< orphan*/  memsize ;
typedef  int /*<<< orphan*/  memorystatus_level ;
typedef  int int64_t ;

/* Variables and functions */
 int MAX (int /*<<< orphan*/ ,int) ; 
 int MEGABYTE ; 
 int /*<<< orphan*/  T_ASSERT_GT (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  T_ASSERT_LE (int,int,char*) ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (int,char*) ; 
 int /*<<< orphan*/  T_LOG (char*,int,int,int) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  T_SKIP (char*,int,int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int sysctlbyname (char*,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
wait_for_free_mem(int need_mb)
{
	int64_t		memsize;
	int		memorystatus_level;
	size_t		size;
	int64_t		avail;
	int		err;
	int		try;

	/*
	 * get amount of memory in the machine
	 */
	size = sizeof(memsize);
	err = sysctlbyname("hw.memsize", &memsize, &size, NULL, 0);
	T_QUIET; T_ASSERT_POSIX_SUCCESS(err, "sysctlbyname(hw.memsize...) failed");

	/*
	 * Use a loop to briefly sleep and recheck if short on memory.
	 */
	try = 1;
	for (;;) {

		/*
		 * memorystatus_level is a percentage of memory available. For example 20 means 1/5 of memory.
		 * It currently doesn't exist on macOS but neither does jetsam, so pass the test there.
		 */
		size = sizeof(memorystatus_level);
		if (sysctlbyname("kern.memorystatus_level", &memorystatus_level, &size, NULL, 0) != 0)
			return;
		T_QUIET; T_ASSERT_LE(memorystatus_level, 100, "memorystatus_level too high");
		T_QUIET; T_ASSERT_GT(memorystatus_level, 0, "memorystatus_level negative");

		/*
		 * jetsam kicks in at memory status level of 15%, so subtract that much out of what's available.
		 */
		avail = MAX(0, (memsize * (memorystatus_level - 15)) / 100);

		/*
		 * We're good to go if there's more than enough available.
		 */
		if ((int64_t)need_mb * MEGABYTE < avail)
			return;

		/*
		 * issue a message to log and sleep briefly to see if we can get more memory
		 */
		if (try-- == 0)
			break;
		T_LOG("Need %d MB, only %d MB available. sleeping 5 seconds for more to free. memorystatus_level %d",
		    need_mb, (int)(avail / MEGABYTE), memorystatus_level);
		sleep(5);
	}
	T_SKIP("Needed %d MB, but only %d MB available. Skipping test to avoid jetsam issues.",
	    need_mb, (int)(avail / MEGABYTE));
}