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
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  esp_event_loop_run (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  loop_without_task ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

__attribute__((used)) static void application_task(void* args)
{
    while(1) {
        ESP_LOGI(TAG, "application_task: running application task");
        esp_event_loop_run(loop_without_task, 100);
        vTaskDelay(10);
    }
}