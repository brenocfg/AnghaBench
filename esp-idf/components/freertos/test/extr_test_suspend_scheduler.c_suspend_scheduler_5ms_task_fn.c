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
 int /*<<< orphan*/  ets_delay_us (int) ; 
 int sched_suspended ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vTaskSuspendAll () ; 
 int /*<<< orphan*/  xTaskResumeAll () ; 

__attribute__((used)) static void suspend_scheduler_5ms_task_fn(void *ignore)
{
    vTaskSuspendAll();
    sched_suspended = true;
    for (int i = 0; i <5; i++) {
        ets_delay_us(1000);
    }
    xTaskResumeAll();
    sched_suspended = false;
    vTaskDelete(NULL);
}