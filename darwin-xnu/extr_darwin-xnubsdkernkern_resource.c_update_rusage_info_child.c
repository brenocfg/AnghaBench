#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rusage_info_child {int /*<<< orphan*/  ri_child_elapsed_abstime; int /*<<< orphan*/  ri_child_pageins; int /*<<< orphan*/  ri_child_interrupt_wkups; int /*<<< orphan*/  ri_child_pkg_idle_wkups; int /*<<< orphan*/  ri_child_system_time; int /*<<< orphan*/  ri_child_user_time; } ;
struct TYPE_3__ {scalar_t__ ri_child_elapsed_abstime; scalar_t__ ri_proc_start_abstime; scalar_t__ ri_proc_exit_abstime; scalar_t__ ri_child_pageins; scalar_t__ ri_pageins; scalar_t__ ri_child_interrupt_wkups; scalar_t__ ri_interrupt_wkups; scalar_t__ ri_child_pkg_idle_wkups; scalar_t__ ri_pkg_idle_wkups; scalar_t__ ri_child_system_time; scalar_t__ ri_system_time; scalar_t__ ri_child_user_time; scalar_t__ ri_user_time; } ;
typedef  TYPE_1__ rusage_info_current ;

/* Variables and functions */

void
update_rusage_info_child(struct rusage_info_child *ri, rusage_info_current *ri_current)
{
	ri->ri_child_user_time += (ri_current->ri_user_time +
					ri_current->ri_child_user_time);
	ri->ri_child_system_time += (ri_current->ri_system_time +
					ri_current->ri_child_system_time);
	ri->ri_child_pkg_idle_wkups += (ri_current->ri_pkg_idle_wkups +
					ri_current->ri_child_pkg_idle_wkups);
	ri->ri_child_interrupt_wkups += (ri_current->ri_interrupt_wkups +
					ri_current->ri_child_interrupt_wkups);
	ri->ri_child_pageins += (ri_current->ri_pageins +
					ri_current->ri_child_pageins);
	ri->ri_child_elapsed_abstime += ((ri_current->ri_proc_exit_abstime -
		ri_current->ri_proc_start_abstime) + ri_current->ri_child_elapsed_abstime);
}