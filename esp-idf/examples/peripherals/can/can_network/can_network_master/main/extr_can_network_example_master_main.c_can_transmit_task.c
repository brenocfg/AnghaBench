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
typedef  scalar_t__ tx_task_action_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  EXAMPLE_TAG ; 
 int /*<<< orphan*/  PING_PERIOD_MS ; 
 scalar_t__ TX_SEND_PINGS ; 
 scalar_t__ TX_SEND_START_CMD ; 
 scalar_t__ TX_SEND_STOP_CMD ; 
 scalar_t__ TX_TASK_EXIT ; 
 int /*<<< orphan*/  can_transmit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdMS_TO_TICKS (int /*<<< orphan*/ ) ; 
 scalar_t__ pdTRUE ; 
 int /*<<< orphan*/  ping_message ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  start_message ; 
 int /*<<< orphan*/  stop_message ; 
 int /*<<< orphan*/  stop_ping_sem ; 
 int /*<<< orphan*/  tx_task_queue ; 
 int /*<<< orphan*/  vTaskDelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xQueueReceive (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ xSemaphoreTake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void can_transmit_task(void *arg)
{
    while (1) {
        tx_task_action_t action;
        xQueueReceive(tx_task_queue, &action, portMAX_DELAY);

        if (action == TX_SEND_PINGS) {
            //Repeatedly transmit pings
            ESP_LOGI(EXAMPLE_TAG, "Transmitting ping");
            while (xSemaphoreTake(stop_ping_sem, 0) != pdTRUE) {
                can_transmit(&ping_message, portMAX_DELAY);
                vTaskDelay(pdMS_TO_TICKS(PING_PERIOD_MS));
            }
        } else if (action == TX_SEND_START_CMD) {
            //Transmit start command to slave
            can_transmit(&start_message, portMAX_DELAY);
            ESP_LOGI(EXAMPLE_TAG, "Transmitted start command");
        } else if (action == TX_SEND_STOP_CMD) {
            //Transmit stop command to slave
            can_transmit(&stop_message, portMAX_DELAY);
            ESP_LOGI(EXAMPLE_TAG, "Transmitted stop command");
        } else if (action == TX_TASK_EXIT) {
            break;
        }
    }
    vTaskDelete(NULL);
}