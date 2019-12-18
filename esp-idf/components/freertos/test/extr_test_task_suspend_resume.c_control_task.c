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
typedef  int int64_t ;

/* Variables and functions */
 int delta_ms ; 
 int duration_ctrl_task_ms ; 
 int esp_timer_get_time () ; 
 int /*<<< orphan*/  ets_delay_us (int) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int /*<<< orphan*/  resume_scheduler_on_both_cpus () ; 
 int /*<<< orphan*/  suspend_scheduler_on_both_cpus () ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int waiting_ms ; 
 int xPortGetCoreID () ; 

__attribute__((used)) static void control_task(void *pvParameters)
{
    int cpu_id = xPortGetCoreID();
    ets_delay_us(2000); // let to start the waiting_task first
    printf("Start control_task cpu=%d\n", cpu_id);
    int64_t start_time = esp_timer_get_time();

    suspend_scheduler_on_both_cpus();
    ets_delay_us(waiting_ms * 1000 + delta_ms * 1000);
    resume_scheduler_on_both_cpus();

    duration_ctrl_task_ms = (esp_timer_get_time() - start_time) / 1000;
    printf("Finish control_task cpu=%d, time=%d ms\n", cpu_id, duration_ctrl_task_ms);
    vTaskDelete(NULL);
}