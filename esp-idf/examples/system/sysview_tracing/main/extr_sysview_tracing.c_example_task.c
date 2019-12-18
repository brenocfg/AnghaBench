#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  timer_isr_handle_t ;
struct TYPE_3__ {int /*<<< orphan*/  timer; int /*<<< orphan*/  group; } ;
typedef  TYPE_1__ example_event_data_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  SYSVIEW_EXAMPLE_WAIT_EVENT_END (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSVIEW_EXAMPLE_WAIT_EVENT_START () ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  example_timer_isr ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 scalar_t__ timer_isr_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ timer_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xTaskGetCurrentTaskHandle () ; 
 int /*<<< orphan*/  xTaskNotifyWait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void example_task(void *p)
{
    example_event_data_t *arg = (example_event_data_t *) p;
    timer_isr_handle_t inth;

    ESP_LOGI(TAG, "%p: run task", xTaskGetCurrentTaskHandle());

    esp_err_t res = timer_isr_register(arg->group, arg->timer, example_timer_isr, arg, 0, &inth);
    if (res != ESP_OK) {
        ESP_LOGE(TAG, "%p: failed to register timer ISR", xTaskGetCurrentTaskHandle());
    } else {
        res = timer_start(arg->group, arg->timer);
        if (res != ESP_OK) {
            ESP_LOGE(TAG, "%p: failed to start timer", xTaskGetCurrentTaskHandle());
        }
    }

    while (1) {
        uint32_t event_val;
        SYSVIEW_EXAMPLE_WAIT_EVENT_START();
        xTaskNotifyWait(0, 0, &event_val, portMAX_DELAY);
        SYSVIEW_EXAMPLE_WAIT_EVENT_END(event_val);
        ESP_LOGI(TAG, "Task[%p]: received event %d", xTaskGetCurrentTaskHandle(), event_val);
    }
}