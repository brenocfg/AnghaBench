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
typedef  int /*<<< orphan*/  TimerHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT_INT_WITHIN (int,int,int) ; 
 int /*<<< orphan*/  control_task ; 
 int delta_ms ; 
 int duration_ctrl_task_ms ; 
 int duration_timer_ms ; 
 int /*<<< orphan*/  pdTRUE ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int portTICK_PERIOD_MS ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  timer_callback ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 
 int waiting_ms ; 
 int /*<<< orphan*/  xTaskCreatePinnedToCore (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xTimerCreate (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xTimerDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xTimerStart (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_scheduler_suspend3(int cpu)
{
    duration_timer_ms = 0;
    duration_ctrl_task_ms = 0;

    printf("Test for CPU%d\n", cpu);
    TimerHandle_t count_time = xTimerCreate("count_time", 1, pdTRUE, NULL, timer_callback);
    xTimerStart( count_time, portMAX_DELAY);
    xTaskCreatePinnedToCore(&control_task, "control_task", 8192, NULL, 5, NULL, cpu);

    vTaskDelay(waiting_ms * 2 / portTICK_PERIOD_MS);
    xTimerDelete(count_time, portMAX_DELAY);
    printf("Finish duration_timer_ms=%d ms\n", duration_timer_ms);

    TEST_ASSERT_INT_WITHIN(2, waiting_ms * 2, duration_timer_ms);
    TEST_ASSERT_INT_WITHIN(5, waiting_ms + delta_ms, duration_ctrl_task_ms);

    printf("\n");
}