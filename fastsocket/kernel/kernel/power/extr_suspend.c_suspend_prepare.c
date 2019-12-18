#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  enter; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  PM_POST_SUSPEND ; 
 int /*<<< orphan*/  PM_SUSPEND_PREPARE ; 
 int pm_notifier_call_chain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_prepare_console () ; 
 int /*<<< orphan*/  pm_restore_console () ; 
 int suspend_freeze_processes () ; 
 TYPE_1__* suspend_ops ; 
 int /*<<< orphan*/  suspend_thaw_processes () ; 
 int usermodehelper_disable () ; 
 int /*<<< orphan*/  usermodehelper_enable () ; 

__attribute__((used)) static int suspend_prepare(void)
{
	int error;

	if (!suspend_ops || !suspend_ops->enter)
		return -EPERM;

	pm_prepare_console();

	error = pm_notifier_call_chain(PM_SUSPEND_PREPARE);
	if (error)
		goto Finish;

	error = usermodehelper_disable();
	if (error)
		goto Finish;

	error = suspend_freeze_processes();
	if (!error)
		return 0;

	suspend_thaw_processes();
	usermodehelper_enable();
 Finish:
	pm_notifier_call_chain(PM_POST_SUSPEND);
	pm_restore_console();
	return error;
}