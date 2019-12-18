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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ TickType_t ;

/* Variables and functions */
 int /*<<< orphan*/  IDEAL_DELAY_PERIOD_MS ; 
 int /*<<< orphan*/  IDEAL_DELAY_PERIOD_US ; 
 int NO_OF_CYCLES ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_UINT32_WITHIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TICKS_TO_DELAY ; 
 int /*<<< orphan*/  TICKS_TO_MS (scalar_t__) ; 
 int /*<<< orphan*/  TICK_PERIOD_US ; 
 scalar_t__ ref_clock_get () ; 
 int /*<<< orphan*/  task_delete_semphr ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 
 int /*<<< orphan*/  vTaskDelayUntil (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 
 scalar_t__ xTaskGetTickCount () ; 

__attribute__((used)) static void delaying_task(void* arg)
{
    uint64_t ref_prev, ref_current;
    TickType_t last_wake_time;
    TickType_t ticks_before_delay;

    vTaskDelay(1);  //Delay until next tick to synchronize operations to tick boundaries

    last_wake_time = xTaskGetTickCount();
    ticks_before_delay = last_wake_time;
    ref_prev = ref_clock_get();

    for(int i = 0; i < NO_OF_CYCLES; i++){
        //Delay of TICKS_TO_DELAY
        vTaskDelayUntil(&last_wake_time, TICKS_TO_DELAY);
        //Get current ref clock
        TEST_ASSERT_EQUAL(IDEAL_DELAY_PERIOD_MS, TICKS_TO_MS(xTaskGetTickCount() - ticks_before_delay));
        ref_current = ref_clock_get();
        TEST_ASSERT_UINT32_WITHIN(TICK_PERIOD_US, IDEAL_DELAY_PERIOD_US, (uint32_t)(ref_current - ref_prev));
        ref_prev = ref_current;
        ticks_before_delay = last_wake_time;
    }

    //Delete Task after prescribed number of cycles
    xSemaphoreGive(task_delete_semphr);
    vTaskDelete(NULL);
}