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
typedef  int /*<<< orphan*/  QueueHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ pdPASS ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 scalar_t__ xQueueReceive (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xTaskGetCurrentTaskHandle () ; 

__attribute__((used)) static void free_task(void *p)
{
    QueueHandle_t queue = (QueueHandle_t)p;
    while (1) {
        void *p = NULL;
        if (xQueueReceive(queue, ( void * )&p, portMAX_DELAY) != pdPASS) {
            ESP_LOGE(TAG, "Failed to send to queue!");
        } else {
            ESP_LOGI(TAG, "Task[%p]: free memory @ %p", xTaskGetCurrentTaskHandle(), p);
            free(p);
        }
    }
}