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
 int MESSAGE ; 
 int /*<<< orphan*/  TIMER_GROUP_0 ; 
 int /*<<< orphan*/  eSetValueWithOverwrite ; 
 int isr_give ; 
 int /*<<< orphan*/  notifs_sent ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  rec_task_handle ; 
 int /*<<< orphan*/  task_delete_semphr ; 
 int /*<<< orphan*/  timer_start (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trigger_send_semphr ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int xPortGetCoreID () ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xSemaphoreTake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xTaskNotify (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xTaskNotifyGive (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sender_task (void* arg){
    int curcore = xPortGetCoreID();

    //Test xTaskNotify
    xSemaphoreTake(trigger_send_semphr, portMAX_DELAY);
    notifs_sent++;
    xTaskNotify(rec_task_handle, (MESSAGE << curcore), eSetValueWithOverwrite);

    //Test xTaskNotifyGive
    xSemaphoreTake(trigger_send_semphr, portMAX_DELAY);
    notifs_sent++;
    xTaskNotifyGive(rec_task_handle);

    //Test xTaskNotifyFromISR
    xSemaphoreTake(trigger_send_semphr, portMAX_DELAY);
    isr_give = false;
    timer_start(TIMER_GROUP_0, curcore);

    //Test vTaskNotifyGiveFromISR
    xSemaphoreTake(trigger_send_semphr, portMAX_DELAY);
    isr_give = true;
    timer_start(TIMER_GROUP_0, curcore);

    //Delete Task and Semaphores
    xSemaphoreGive(task_delete_semphr);
    vTaskDelete(NULL);
}