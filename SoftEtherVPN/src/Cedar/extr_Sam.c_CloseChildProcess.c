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
typedef  scalar_t__ PID ;

/* Variables and functions */
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  kill (scalar_t__,int /*<<< orphan*/ ) ; 

void CloseChildProcess(PID pid, int* fd )
{
#ifdef OS_WIN32
	// not implemented
#else // OS_WIN32
	if( fd != 0 )
	{
			close(fd[0]);
			close(fd[1]);
	}

	if( pid > 0 )
	{
		kill(pid, SIGTERM);
	}
#endif // OS_WIN32
}