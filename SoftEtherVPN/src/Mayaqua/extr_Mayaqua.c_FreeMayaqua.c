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
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeCommandLineStr () ; 
 int /*<<< orphan*/  FreeCommandLineTokens () ; 
 int /*<<< orphan*/  FreeCryptLibrary () ; 
 int /*<<< orphan*/  FreeHamcore () ; 
 int /*<<< orphan*/  FreeKernelStatus () ; 
 int /*<<< orphan*/  FreeNetwork () ; 
 int /*<<< orphan*/  FreeOsInfo () ; 
 int /*<<< orphan*/  FreePrivateIPFile () ; 
 int /*<<< orphan*/  FreeProbe () ; 
 int /*<<< orphan*/  FreeSecure () ; 
 int /*<<< orphan*/  FreeStringLibrary () ; 
 int /*<<< orphan*/  FreeTable () ; 
 int /*<<< orphan*/  FreeThreading () ; 
 int /*<<< orphan*/  FreeTick64 () ; 
 int /*<<< orphan*/  FreeTracking () ; 
 scalar_t__ IsTrackingEnabled () ; 
 int /*<<< orphan*/  MsFree () ; 
 int /*<<< orphan*/  OSFree () ; 
 int /*<<< orphan*/  PrintDebugInformation () ; 
 int /*<<< orphan*/  PrintKernelStatus () ; 
 scalar_t__ g_debug ; 
 scalar_t__ g_memcheck ; 
 scalar_t__ init_mayaqua_counter ; 
 int /*<<< orphan*/ * tick_manual_lock ; 

void FreeMayaqua()
{
	if ((--init_mayaqua_counter) > 0)
	{
		return;
	}

	// Release of Private IP File
	FreePrivateIPFile();

	// Release of Probe
	FreeProbe();

	// Delete the table
	FreeTable();

	// Release of security token module
	FreeSecure();

	// Release of the operating system specific module
#ifdef	OS_WIN32
	MsFree();
#endif	// OS_WIN32

	// Release of OS information
	FreeOsInfo();

	// Release of HamCore file system
	FreeHamcore();

	// Release of the command line string
	FreeCommandLineStr();

	// Release of the command line token
	FreeCommandLineTokens();

	// Release of network communication module
	FreeNetwork();

	// Release of real-time clock
	FreeTick64();

	// Release of the string library
	FreeStringLibrary();

	// Release of thread pool
	FreeThreading();

	// Release of crypt library
	FreeCryptLibrary();

	if (IsTrackingEnabled())
	{
		// Show the kernel status
		if (g_debug)
		{
			PrintKernelStatus();
		}

		// Display the debug information
		if (g_memcheck)
		{
			PrintDebugInformation();
		}

		// Release the tracking
		FreeTracking();
	}

	// Release of the kernel status
	FreeKernelStatus();

	DeleteLock(tick_manual_lock);
	tick_manual_lock = NULL;

	// Release of OS
	OSFree();
}