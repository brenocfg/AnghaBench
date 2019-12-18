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
typedef  int /*<<< orphan*/  exe ;
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;

/* Variables and functions */
 int /*<<< orphan*/  AbortExit () ; 
 int /*<<< orphan*/  GetExeName (char*,int) ; 
 scalar_t__ LocalTime64 () ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  Print (char*,...) ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  SleepThread (int) ; 
 scalar_t__ SystemToLocal64 (int /*<<< orphan*/ ) ; 
 scalar_t__ Tick64 () ; 
 int /*<<< orphan*/  TickToTime (scalar_t__) ; 
 char* UNIX_ARG_EXIT ; 
 int /*<<< orphan*/  UnixCloseIO () ; 
 scalar_t__ WIFEXITED (int) ; 
 char** ZeroMalloc (int) ; 
 int /*<<< orphan*/  execvp (char*,char**) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  setsid () ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

bool CheckKernel()
{
	UINT num = 10, i;
	UINT64 s = Tick64();
	UINT64 t = Tick64();

	for (i = 0;i < num;i++)
	{
		UINT64 q = Tick64();
		if (t > q)
		{
			Print("Tick64 #1 Failed.\n");
			return false;
		}

		t = q;

		SleepThread(100);
	}

	t = (Tick64() - s);
	if (t <= 500 || t >= 2000)
	{
		Print("Tick64 #2 Failed.\n");
		return false;
	}
	else if (false)
	{
		UINT64 tick1 = Tick64();
		UINT64 time1;
		UINT64 time2;

		SleepThread(1000);

		time2 = LocalTime64();
		time1 = SystemToLocal64(TickToTime(tick1));

		if (time2 > time1)
		{
			s = time2 - time1;
		}
		else
		{
			s = time1 - time2;
		}

		if (s <= 500 || s >= 2000)
		{
			Print("TickToTime Failed.\n");
			return false;
		}
	}

#ifdef	OS_UNIX
	{
		// Test of child process
		UINT pid;
		char exe[MAX_SIZE];

		GetExeName(exe, sizeof(exe));

		pid = fork();

		if (pid == -1)
		{
			Print("fork Failed.\n");
			return false;
		}

		if (pid == 0)
		{
			char *param = UNIX_ARG_EXIT;
			char **args;

			args = ZeroMalloc(sizeof(char *) * 3);
			args[0] = exe;
			args[1] = param;
			args[2] = NULL;

			setsid();

			// Close the standard I/O
			UnixCloseIO();

			// Stop unwanted signals
			signal(SIGHUP, SIG_IGN);

			execvp(exe, args);
			AbortExit();
		}
		else
		{
			int status = 0, ret;

			// Wait for the termination of the child process
			ret = waitpid(pid, &status, 0);

			if (WIFEXITED(status) == 0)
			{
				// Aborted
				Print("waitpid Failed: 0x%x\n", ret);
				return false;
			}
		}
	}
#endif	// OS_UNIX

	return true;
}