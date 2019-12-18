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
 int /*<<< orphan*/  ia64_cpu_local_tick_fn ; 
 int /*<<< orphan*/  smp_call_function (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void
xen_timer_resume_on_aps(void)
{
	smp_call_function(&ia64_cpu_local_tick_fn, NULL, 1);
}