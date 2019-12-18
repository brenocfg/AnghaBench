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
 int /*<<< orphan*/  PM_POST_SUSPEND ; 
 int /*<<< orphan*/  pm_notifier_call_chain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_restore_console () ; 
 int /*<<< orphan*/  suspend_thaw_processes () ; 
 int /*<<< orphan*/  usermodehelper_enable () ; 

__attribute__((used)) static void suspend_finish(void)
{
	suspend_thaw_processes();
	usermodehelper_enable();
	pm_notifier_call_chain(PM_POST_SUSPEND);
	pm_restore_console();
}