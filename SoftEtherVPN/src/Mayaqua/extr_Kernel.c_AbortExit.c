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

/* Variables and functions */
 int /*<<< orphan*/  RLIMIT_CORE ; 
 int /*<<< orphan*/  UnixSetResourceLimit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  abort () ; 

void AbortExit()
{
#ifdef	OS_WIN32
	_exit(1);
#else	// OS_WIN32

#ifdef	RLIMIT_CORE
	UnixSetResourceLimit(RLIMIT_CORE, 0);
#endif	// RLIMIT_CORE

	abort();
#endif	// OS_WIN32
}