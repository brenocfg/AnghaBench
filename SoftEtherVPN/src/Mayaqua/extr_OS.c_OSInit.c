#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* Init ) () ;} ;

/* Variables and functions */
 TYPE_1__* UnixGetDispatchTable () ; 
 TYPE_1__* Win32GetDispatchTable () ; 
 TYPE_1__* os ; 
 int /*<<< orphan*/  stub1 () ; 

void OSInit()
{
	// Get the dispatch table
#ifdef	OS_WIN32
	os = Win32GetDispatchTable();
#else	// OS_WIN32
	os = UnixGetDispatchTable();
#endif	// OS_WIN32

	// Calling the OS-specific initialization function
	os->Init();
}