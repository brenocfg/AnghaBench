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
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  blocked_task_handle ; 
 int /*<<< orphan*/  done_sem ; 
 scalar_t__ eBlocked ; 
 scalar_t__ eReady ; 
 scalar_t__ eRunning ; 
 scalar_t__ eSuspended ; 
 scalar_t__ eTaskGetState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  suspended_task_handle ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xTaskGetCurrentTaskHandle () ; 
 int /*<<< orphan*/  xTaskGetIdleTaskHandle () ; 

void test_task_get_state(void* arg)
{
    //Current task should return eRunning
    TEST_ASSERT(eTaskGetState(xTaskGetCurrentTaskHandle()) == eRunning);
    //Idle task of current core should return eReady
    TEST_ASSERT(eTaskGetState(xTaskGetIdleTaskHandle()) == eReady);
    //Blocked Task should return eBlocked
    TEST_ASSERT(eTaskGetState(blocked_task_handle) == eBlocked);
    //Suspended Task should return eSuspended
    TEST_ASSERT(eTaskGetState(suspended_task_handle) == eSuspended);

    xSemaphoreGive(done_sem);
    vTaskDelete(NULL);
}