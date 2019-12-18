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
 int /*<<< orphan*/  TEST_ASSERT_INT_WITHIN (int,int,scalar_t__) ; 
 int /*<<< orphan*/  control_task ; 
 int delta_ms ; 
 scalar_t__ duration_ctrl_task_ms ; 
 scalar_t__ duration_wait_task_ms ; 
 int portTICK_PERIOD_MS ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int suspend_both_cpus ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 
 int waiting_ms ; 
 int /*<<< orphan*/  waiting_task ; 
 int /*<<< orphan*/  xTaskCreatePinnedToCore (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void test_scheduler_suspend1(int cpu)
{
    /* This test tests a case then both CPUs were in suspend state and then resume CPUs back.
     * A task for which a wait time has been set and this time has elapsed in the suspended state should in any case be ready to start.
     * (In an old implementation of xTaskIncrementTick function the counting for waiting_task() will be continued
     * (excluding time in suspended) after control_task() is finished.)
     */
    duration_wait_task_ms = 0;
    duration_ctrl_task_ms = 0;

    printf("Test for CPU%d\n", cpu);
    int other_cpu = (cpu == 0) ? 1 : 0;
    xTaskCreatePinnedToCore(&waiting_task, "waiting_task", 8192, NULL, 5, NULL, other_cpu);
    xTaskCreatePinnedToCore(&control_task, "control_task", 8192, NULL, 5, NULL, cpu);

    vTaskDelay(waiting_ms * 2 / portTICK_PERIOD_MS);
    TEST_ASSERT_INT_WITHIN(4, waiting_ms + delta_ms + 4, duration_ctrl_task_ms);
    if (suspend_both_cpus == false && cpu == 1) {
        // CPU0 continues to increase the TickCount and the wait_task does not depend on Suspended Scheduler on CPU1
        TEST_ASSERT_INT_WITHIN(2, waiting_ms, duration_wait_task_ms);
    } else {
        TEST_ASSERT_INT_WITHIN(4, waiting_ms + delta_ms + 4, duration_wait_task_ms);
    }

    printf("\n");
}