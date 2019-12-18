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
 scalar_t__ boot_trace ; 
 scalar_t__ pre_initcalls_finished ; 
 int /*<<< orphan*/  tracing_stop_sched_switch_record () ; 

void disable_boot_trace(void)
{
	if (boot_trace && pre_initcalls_finished)
		tracing_stop_sched_switch_record();
}