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
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 int /*<<< orphan*/  Print (char*) ; 
 int /*<<< orphan*/  SMExec () ; 

void server_manager_test(UINT num, char **arg)
{
#ifdef	OS_WIN32
	SMExec();
#else	// OS_WIN32
	Print("This command is supported only on Win32.");
#endif	// OS_WIN32
}