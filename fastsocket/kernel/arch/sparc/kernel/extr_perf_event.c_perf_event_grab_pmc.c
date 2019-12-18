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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  active_events ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nmi_active ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  perf_stop_nmi_watchdog ; 
 int /*<<< orphan*/  pmc_grab_mutex ; 

void perf_event_grab_pmc(void)
{
	if (atomic_inc_not_zero(&active_events))
		return;

	mutex_lock(&pmc_grab_mutex);
	if (atomic_read(&active_events) == 0) {
		if (atomic_read(&nmi_active) > 0) {
			on_each_cpu(perf_stop_nmi_watchdog, NULL, 1);
			BUG_ON(atomic_read(&nmi_active) != 0);
		}
		atomic_inc(&active_events);
	}
	mutex_unlock(&pmc_grab_mutex);
}