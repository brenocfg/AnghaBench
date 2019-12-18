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
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 unsigned long get_lockd_grace_period () ; 
 int /*<<< orphan*/  grace_period_end ; 
 int /*<<< orphan*/  lockd_manager ; 
 int /*<<< orphan*/  locks_start_grace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void set_grace_period(void)
{
	unsigned long grace_period = get_lockd_grace_period();

	locks_start_grace(&lockd_manager);
	cancel_delayed_work_sync(&grace_period_end);
	schedule_delayed_work(&grace_period_end, grace_period);
}