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
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  RB_DEBUGGER ; 
 int /*<<< orphan*/  __STDERR_FILENO ; 
 int _mach_snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  host_reboot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  master_host_port ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,int) ; 

void
panic(const char *s, ...)
{
	char buffer[1024];
	int len = _mach_snprintf(buffer, sizeof(buffer), "panic: %s\n", s);
	write(__STDERR_FILENO, buffer, len);
	
#define RB_DEBUGGER	0x1000	/* enter debugger NOW */
	(void) host_reboot(master_host_port, RB_DEBUGGER);

	/* 4279008 - don't return */
	abort();
}