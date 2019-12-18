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
 int FALSE ; 
 int /*<<< orphan*/  Log_flushlog () ; 
 scalar_t__ MONITOR_Run () ; 
 int TRUE ; 
 int /*<<< orphan*/  curs_set (int) ; 
 int /*<<< orphan*/  endwin () ; 

int PLATFORM_Exit(int run_monitor)
{
	curs_set(1);
	endwin();
	Log_flushlog();

	if (run_monitor && MONITOR_Run()) {
		curs_set(0);
		return TRUE;
	}
	return FALSE;
}