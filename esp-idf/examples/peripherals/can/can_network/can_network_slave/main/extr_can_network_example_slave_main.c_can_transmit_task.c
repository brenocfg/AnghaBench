#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ tx_task_action_t ;
struct TYPE_5__ {int* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_PERIOD_MS ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  EXAMPLE_TAG ; 
 scalar_t__ TX_SEND_DATA ; 
 scalar_t__ TX_SEND_PING_RESP ; 
 scalar_t__ TX_SEND_STOP_RESP ; 
 scalar_t__ TX_TASK_EXIT ; 
 int /*<<< orphan*/  can_transmit (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctrl_task_sem ; 
 TYPE_1__ data_message ; 
 int /*<<< orphan*/  pdMS_TO_TICKS (int /*<<< orphan*/ ) ; 
 scalar_t__ pdTRUE ; 
 TYPE_1__ ping_resp ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  stop_data_sem ; 
 TYPE_1__ stop_resp ; 
 int /*<<< orphan*/  tx_task_queue ; 
 int /*<<< orphan*/  vTaskDelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xQueueReceive (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 
 scalar_t__ xSemaphoreTake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xTaskGetTickCount () ; 

__attribute__((used)) static void can_transmit_task(void *arg)
{
    while (1) {
        tx_task_action_t action;
        xQueueReceive(tx_task_queue, &action, portMAX_DELAY);

        if (action == TX_SEND_PING_RESP) {
            //Transmit ping response to master
            can_transmit(&ping_resp, portMAX_DELAY);
            ESP_LOGI(EXAMPLE_TAG, "Transmitted ping response");
            xSemaphoreGive(ctrl_task_sem);
        } else if (action == TX_SEND_DATA) {
            //Transmit data messages until stop command is received
            ESP_LOGI(EXAMPLE_TAG, "Start transmitting data");
            while (1) {
                //FreeRTOS tick count used to simulate sensor data
                uint32_t sensor_data = xTaskGetTickCount();
                for (int i = 0; i < 4; i++) {
                    data_message.data[i] = (sensor_data >> (i * 8)) & 0xFF;
                }
                can_transmit(&data_message, portMAX_DELAY);
                ESP_LOGI(EXAMPLE_TAG, "Transmitted data value %d", sensor_data);
                vTaskDelay(pdMS_TO_TICKS(DATA_PERIOD_MS));
                if (xSemaphoreTake(stop_data_sem, 0) == pdTRUE) {
                    break;
                }
            }
        } else if (action == TX_SEND_STOP_RESP) {
            //Transmit stop response to master
            can_transmit(&stop_resp, portMAX_DELAY);
            ESP_LOGI(EXAMPLE_TAG, "Transmitted stop response");
            xSemaphoreGive(ctrl_task_sem);
        } else if (action == TX_TASK_EXIT) {
            break;
        }
    }
    vTaskDelete(NULL);
}