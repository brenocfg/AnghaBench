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
 int /*<<< orphan*/  eNoAction ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  xTaskGetCurrentTaskHandle () ; 
 int /*<<< orphan*/  xTaskNotify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xTaskNotifyWait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *waiting_thread(void *arg)
{
    TaskHandle_t *task_handle = (TaskHandle_t *)arg;
    TaskHandle_t parent_task  = *task_handle;

    *task_handle = xTaskGetCurrentTaskHandle();

    xTaskNotify(parent_task, 0, eNoAction);
    xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);
    return NULL;
}