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
 int /*<<< orphan*/  BIT_CALL ; 
 int /*<<< orphan*/  BIT_RESPONSE (int) ; 
 int COUNT ; 
 int /*<<< orphan*/  TEST_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  done_sem ; 
 int /*<<< orphan*/  eg ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xEventGroupSetBits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xEventGroupWaitBits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void task_event_group_call_response(void *param)
{
    int task_num = (int)param;

    printf("Started %d\n", task_num);

    for (int i = 0; i < COUNT; i++) {
        /* Wait until the common "call" bit is set, starts off all tasks
           (clear on return) */
        TEST_ASSERT( xEventGroupWaitBits(eg, BIT_CALL, true, false, portMAX_DELAY) );

        /* Set our individual "response" bit */
        xEventGroupSetBits(eg, BIT_RESPONSE(task_num));
    }

    printf("Task %d done\n", task_num);
    xSemaphoreGive(done_sem);
    vTaskDelete(NULL);
}