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
typedef  scalar_t__ QueueHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  alloc_task ; 
 int /*<<< orphan*/  esp_log_set_vprintf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_sysview_vprintf ; 
 scalar_t__ heap_trace_init_tohost () ; 
 scalar_t__ xQueueCreate (int,int) ; 
 int /*<<< orphan*/  xTaskCreatePinnedToCore (int /*<<< orphan*/ ,char*,int,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void app_main(void)
{
    // redirect log messages to the host using SystemView tracing module
    esp_log_set_vprintf(&esp_sysview_vprintf);
    QueueHandle_t queue = xQueueCreate(10, sizeof(void *));
    if(queue == 0) {
        ESP_LOGE(TAG, "Failed to create queue!");
        return;
    }
    // init host-based heap tracing
    if(heap_trace_init_tohost() != ESP_OK) {
        ESP_LOGE(TAG, "Failed to init heap trace!");
        return;
    }
    xTaskCreatePinnedToCore(alloc_task, "alloc", 2048, queue, 5, NULL, 0);
}