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
typedef  int uint8_t ;
struct TYPE_3__ {int intr_mask; scalar_t__ pad_num; int /*<<< orphan*/  pad_val; int /*<<< orphan*/  pad_status; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ touch_event_t ;
typedef  int /*<<< orphan*/  portTickType ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  TAG ; 
 int TOUCH_PAD_INTR_MASK_ACTIVE ; 
 int TOUCH_PAD_INTR_MASK_DONE ; 
 int TOUCH_PAD_INTR_MASK_INACTIVE ; 
 scalar_t__* button ; 
 int pdTRUE ; 
 scalar_t__ portMAX_DELAY ; 
 int portTICK_RATE_MS ; 
 int /*<<< orphan*/  que_touch ; 
 int /*<<< orphan*/  tp_example_set_thresholds () ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 
 int xQueueReceive (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tp_example_read_task(void *pvParameter)
{
    touch_event_t evt = {0};
    static uint8_t guard_mode_flag = 0;
    /* Wait touch sensor init done */
    vTaskDelay(100 / portTICK_RATE_MS);
    tp_example_set_thresholds();

    while (1) {
        int ret = xQueueReceive(que_touch, &evt, (portTickType)portMAX_DELAY);
        if (ret != pdTRUE) {
            continue;
        }
        if (evt.intr_mask & TOUCH_PAD_INTR_MASK_ACTIVE) {
            /* if guard pad be touched, other pads no response. */
            if (evt.pad_num == button[3]) {
                guard_mode_flag = 1;
                ESP_LOGW(TAG, "TouchSensor [%d] be actived, enter guard mode", evt.pad_num);
            } else {
                if (guard_mode_flag == 0) {
                    ESP_LOGI(TAG, "TouchSensor [%d] be actived, status mask 0x%x", evt.pad_num, evt.pad_status);
                } else {
                    ESP_LOGW(TAG, "In guard mode. No response");
                }
            }
        }
        if (evt.intr_mask & TOUCH_PAD_INTR_MASK_INACTIVE) {
            /* if guard pad be touched, other pads no response. */
            if (evt.pad_num == button[3]) {
                guard_mode_flag = 0;
                ESP_LOGW(TAG, "TouchSensor [%d] be actived, exit guard mode", evt.pad_num);
            } else {
                if (guard_mode_flag == 0) {
                    ESP_LOGI(TAG, "TouchSensor [%d] be inactived, status mask 0x%x", evt.pad_num, evt.pad_status);
                }
            }
        }
        if (evt.intr_mask & TOUCH_PAD_INTR_MASK_DONE) {
            ESP_LOGI(TAG, "TouchSensor [%d] measure done, raw data %d", evt.pad_num, evt.pad_val);
        }
    }
}