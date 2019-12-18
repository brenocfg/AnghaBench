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
 int /*<<< orphan*/  gdbstub_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mn10300_proc_hard_reset () ; 
 int /*<<< orphan*/  mn10300_unit_hard_reset () ; 

void machine_restart(char *cmd)
{
#ifdef CONFIG_GDBSTUB
	gdbstub_exit(0);
#endif

#ifdef mn10300_unit_hard_reset
	mn10300_unit_hard_reset();
#else
	mn10300_proc_hard_reset();
#endif
}