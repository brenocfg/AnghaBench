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
 int /*<<< orphan*/  TIF_POLLING_NRFLAG ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  need_resched () ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_thread_flag (int /*<<< orphan*/ ) ; 

void
cpu_idle(void)
{
	set_thread_flag(TIF_POLLING_NRFLAG);

	while (1) {
		/* FIXME -- EV6 and LCA45 know how to power down
		   the CPU.  */

		while (!need_resched())
			cpu_relax();
		schedule();
	}
}