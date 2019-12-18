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
 int /*<<< orphan*/  ESP_OK ; 
 int TASK_RESET_PERIOD_S ; 
 int /*<<< orphan*/  esp_task_wdt_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_task_wdt_reset () ; 
 int /*<<< orphan*/  esp_task_wdt_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdMS_TO_TICKS (int) ; 
 int /*<<< orphan*/  vTaskDelay (int /*<<< orphan*/ ) ; 

void reset_task(void *arg)
{
    //Subscribe this task to TWDT, then check if it is subscribed
    CHECK_ERROR_CODE(esp_task_wdt_add(NULL), ESP_OK);
    CHECK_ERROR_CODE(esp_task_wdt_status(NULL), ESP_OK);

    while(1){
        //reset the watchdog every 2 seconds
        CHECK_ERROR_CODE(esp_task_wdt_reset(), ESP_OK);  //Comment this line to trigger a TWDT timeout
        vTaskDelay(pdMS_TO_TICKS(TASK_RESET_PERIOD_S * 1000));
    }
}