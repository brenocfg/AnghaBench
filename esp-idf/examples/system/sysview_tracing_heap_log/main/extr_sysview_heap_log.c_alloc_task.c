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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  QueueHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/  HEAP_TRACE_ALL ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  free_task ; 
 int /*<<< orphan*/  heap_trace_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_trace_stop () ; 
 void* malloc (int) ; 
 scalar_t__ pdPASS ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 scalar_t__ portNUM_PROCESSORS ; 
 int portTICK_PERIOD_MS ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 
 scalar_t__ xQueueSend (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xTaskCreatePinnedToCore (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  xTaskGetCurrentTaskHandle () ; 

__attribute__((used)) static void alloc_task(void *p)
{
    QueueHandle_t queue = (QueueHandle_t)p;

    xTaskCreatePinnedToCore(free_task, "free", 2048, queue, 5, NULL, portNUM_PROCESSORS-1);

    // here GDB will stop at brekpoint and execute OpenOCD command to start tracing
    heap_trace_start(HEAP_TRACE_ALL);
    for(int i = 1; i < 5; i++) {
        uint32_t sz = 2*i;
        void *p = malloc(sz/2);
        // WARNING: the previous allocated memory is intentionally not deallocated in order to cause memory leak!
        p = malloc(sz);
        ESP_LOGI(TAG, "Task[%p]: allocated %d bytes @ %p", xTaskGetCurrentTaskHandle(), sz, p);
        if (xQueueSend(queue, ( void * )&p, portMAX_DELAY) != pdPASS) {
            ESP_LOGE(TAG, "Failed to send to queue!");
        }
        vTaskDelay(100/portTICK_PERIOD_MS);
    }
    // here GDB will stop at brekpoint and execute OpenOCD command to stop tracing
    heap_trace_stop();
    while(1);
}