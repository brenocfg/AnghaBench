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
typedef  int /*<<< orphan*/  TaskHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (unsigned int,unsigned int volatile) ; 
 int /*<<< orphan*/  TEST_ASSERT_NOT_EQUAL (unsigned int,unsigned int volatile) ; 
 scalar_t__ UNITY_FREERTOS_PRIORITY ; 
 int /*<<< orphan*/  printf (char*,unsigned int volatile) ; 
 int /*<<< orphan*/  task_count ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskResume (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskSuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xTaskCreatePinnedToCore (int /*<<< orphan*/ ,char*,int,void*,scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void test_suspend_resume(int target_core)
{
    volatile unsigned counter = 0;
    TaskHandle_t counter_task;

    xTaskCreatePinnedToCore(task_count, "Count", 2048,
                            (void *)&counter, UNITY_FREERTOS_PRIORITY + 1,
                            &counter_task, target_core);

    vTaskDelay(10);
    /* check some counting has happened */
    TEST_ASSERT_NOT_EQUAL(0, counter);

    // Do the next part a few times, just to be sure multiple suspends & resumes
    // work as expected...
    const int TEST_ITERATIONS = 5;
    for (int i = 0; i < TEST_ITERATIONS; i++) {
        vTaskSuspend(counter_task);
        unsigned suspend_count = counter;
        printf("Suspending @ %d\n", suspend_count);

        vTaskDelay(2);

        printf("Still suspended @ %d\n", counter);

        /* check the counter hasn't gone up while the task is suspended */
        TEST_ASSERT_EQUAL(suspend_count, counter);
        vTaskResume(counter_task);
        vTaskDelay(2);

        printf("Resumed @ %d\n", counter);
        /* check the counter is going up again now the task is resumed */
        TEST_ASSERT_NOT_EQUAL(suspend_count, counter);
    }

    vTaskDelete(counter_task);
}