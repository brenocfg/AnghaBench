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
 int /*<<< orphan*/  __cpuc_flush_kern_all () ; 
 int /*<<< orphan*/  __cpuc_flush_user_all () ; 
 int /*<<< orphan*/  arch_reset (char,char const*) ; 
 int /*<<< orphan*/  arm_machine_restart (char,char const*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static void s3c24xx_pm_restart(char mode, const char *cmd)
{
	if (mode != 's') {
		unsigned long flags;

		local_irq_save(flags);
		__cpuc_flush_kern_all();
		__cpuc_flush_user_all();

		arch_reset(mode, cmd);
		local_irq_restore(flags);
	}

	/* fallback, or unhandled */
	arm_machine_restart(mode, cmd);
}