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
typedef  int /*<<< orphan*/  __get_cpu_var ;

/* Variables and functions */
 int /*<<< orphan*/  get_timestamp (int) ; 
 int smp_processor_id () ; 

__attribute__((used)) static void __touch_watchdog(void)
{
	int this_cpu = smp_processor_id();

	__get_cpu_var(watchdog_touch_ts) = get_timestamp(this_cpu);
}