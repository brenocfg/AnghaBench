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
 unsigned int NO_CMDLINE_MAP ; 
 int PID_MAX_DEFAULT ; 
 int /*<<< orphan*/  __raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __raw_spin_unlock (int /*<<< orphan*/ *) ; 
 unsigned int* map_pid_to_cmdline ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 char** saved_cmdlines ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  trace_cmdline_lock ; 

void trace_find_cmdline(int pid, char comm[])
{
	unsigned map;

	if (!pid) {
		strcpy(comm, "<idle>");
		return;
	}

	if (pid > PID_MAX_DEFAULT) {
		strcpy(comm, "<...>");
		return;
	}

	preempt_disable();
	__raw_spin_lock(&trace_cmdline_lock);
	map = map_pid_to_cmdline[pid];
	if (map != NO_CMDLINE_MAP)
		strcpy(comm, saved_cmdlines[map]);
	else
		strcpy(comm, "<...>");

	__raw_spin_unlock(&trace_cmdline_lock);
	preempt_enable();
}