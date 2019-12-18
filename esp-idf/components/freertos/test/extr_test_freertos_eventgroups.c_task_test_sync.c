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
 int /*<<< orphan*/  ALL_RESPONSE_BITS ; 
 int /*<<< orphan*/  BIT_DONE (int) ; 
 int /*<<< orphan*/  BIT_RESPONSE (int) ; 
 int COUNT ; 
 int /*<<< orphan*/  done_sem ; 
 int /*<<< orphan*/  eg ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xEventGroupClearBits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xEventGroupSetBits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xEventGroupSync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void task_test_sync(void *param)
{
    int task_num = (int)param;

    printf("Started %d\n", task_num);

    for (int i = 0; i < COUNT; i++) {
        /* set our bit, and wait on all tasks to set their bits */
        xEventGroupSync(eg, BIT_RESPONSE(task_num), ALL_RESPONSE_BITS, portMAX_DELAY);
        /* clear our bit */
        xEventGroupClearBits(eg, BIT_RESPONSE(task_num));
    }
    int after_done = xEventGroupSetBits(eg, BIT_DONE(task_num));

    printf("Done %d = 0x%08x\n", task_num, after_done);

    xSemaphoreGive(done_sem);
    vTaskDelete(NULL);
}