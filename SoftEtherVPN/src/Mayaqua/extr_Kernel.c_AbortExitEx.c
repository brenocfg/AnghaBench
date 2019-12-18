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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  RLIMIT_CORE ; 
 int /*<<< orphan*/  UnixSetResourceLimit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strlen (char*) ; 

void AbortExitEx(char *msg)
{
	FILE *f;
	// Validate arguments
	if (msg == NULL)
	{
		msg = "Unknown Error";
	}

	f = fopen("abort_error_log.txt", "w");
	if (f != NULL)
	{
		fwrite(msg, 1, strlen(msg), f);
		fclose(f);
	}

	fputs("Fatal Error: ", stdout);
	fputs(msg, stdout);
	fputs("\r\n", stdout);

#ifdef	OS_WIN32
	_exit(1);
#else	// OS_WIN32

#ifdef	RLIMIT_CORE
	UnixSetResourceLimit(RLIMIT_CORE, 0);
#endif	// RLIMIT_CORE

	abort();
#endif	// OS_WIN32
}