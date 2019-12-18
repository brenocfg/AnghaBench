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
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  xen_init_missing_ticks_accounting (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_local_tick_resume () ; 

__attribute__((used)) static void ia64_cpu_local_tick_fn(void *unused)
{
	xen_local_tick_resume();
	xen_init_missing_ticks_accounting(smp_processor_id());
}