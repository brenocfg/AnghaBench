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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int cpu_number () ; 
 int /*<<< orphan*/  timer_queue_migrate_cpu (int) ; 

uint32_t
pmTimerQueueMigrate(int target_cpu)
{
    /* Call the etimer code to do this. */
    return (target_cpu != cpu_number())
		? timer_queue_migrate_cpu(target_cpu)
		: 0;
}