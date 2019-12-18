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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int NOTIFY_OK ; 
 int /*<<< orphan*/  SCLP_PM_EVENT_THAW ; 
 scalar_t__ sclp_suspend_state ; 
 scalar_t__ sclp_suspend_state_suspended ; 
 int /*<<< orphan*/  sclp_undo_suspend (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sclp_panic_notify(struct notifier_block *self,
			     unsigned long event, void *data)
{
	if (sclp_suspend_state == sclp_suspend_state_suspended)
		sclp_undo_suspend(SCLP_PM_EVENT_THAW);
	return NOTIFY_OK;
}