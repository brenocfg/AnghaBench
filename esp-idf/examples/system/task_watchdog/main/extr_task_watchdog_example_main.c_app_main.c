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
 int /*<<< orphan*/  CHECK_ERROR_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_ERR_NOT_FOUND ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TWDT_TIMEOUT_S ; 
 int /*<<< orphan*/  esp_task_wdt_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_task_wdt_deinit () ; 
 int /*<<< orphan*/  esp_task_wdt_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_task_wdt_init (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  esp_task_wdt_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdMS_TO_TICKS (int) ; 
 int portNUM_PROCESSORS ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  reset_task ; 
 int /*<<< orphan*/ ** task_handles ; 
 int /*<<< orphan*/  vTaskDelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xTaskCreatePinnedToCore (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/ * xTaskGetIdleTaskHandleForCPU (int) ; 

void app_main(void)
{
    printf("Initialize TWDT\n");
    //Initialize or reinitialize TWDT
    CHECK_ERROR_CODE(esp_task_wdt_init(TWDT_TIMEOUT_S, false), ESP_OK);

    //Subscribe Idle Tasks to TWDT if they were not subscribed at startup
#ifndef CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU0
    esp_task_wdt_add(xTaskGetIdleTaskHandleForCPU(0));
#endif
#ifndef CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU1
    esp_task_wdt_add(xTaskGetIdleTaskHandleForCPU(1));
#endif

    //Create user tasks and add them to watchdog
    for(int i = 0; i < portNUM_PROCESSORS; i++){
        xTaskCreatePinnedToCore(reset_task, "reset task", 1024, NULL, 10, &task_handles[i], i);
    }

    printf("Delay for 10 seconds\n");
    vTaskDelay(pdMS_TO_TICKS(10000));   //Delay for 10 seconds

    printf("Unsubscribing and deleting tasks\n");
    //Delete and unsubscribe Users Tasks from Task Watchdog, then unsubscribe idle task
    for(int i = 0; i < portNUM_PROCESSORS; i++){
        vTaskDelete(task_handles[i]);   //Delete user task first (prevents the resetting of an unsubscribed task)
        CHECK_ERROR_CODE(esp_task_wdt_delete(task_handles[i]), ESP_OK);     //Unsubscribe task from TWDT
        CHECK_ERROR_CODE(esp_task_wdt_status(task_handles[i]), ESP_ERR_NOT_FOUND);  //Confirm task is unsubscribed

        //unsubscribe idle task
        CHECK_ERROR_CODE(esp_task_wdt_delete(xTaskGetIdleTaskHandleForCPU(i)), ESP_OK);     //Unsubscribe Idle Task from TWDT
        CHECK_ERROR_CODE(esp_task_wdt_status(xTaskGetIdleTaskHandleForCPU(i)), ESP_ERR_NOT_FOUND);      //Confirm Idle task has unsubscribed
    }


    //Deinit TWDT after all tasks have unsubscribed
    CHECK_ERROR_CODE(esp_task_wdt_deinit(), ESP_OK);
    CHECK_ERROR_CODE(esp_task_wdt_status(NULL), ESP_ERR_INVALID_STATE);     //Confirm TWDT has been deinitialized

    printf("Complete\n");
}