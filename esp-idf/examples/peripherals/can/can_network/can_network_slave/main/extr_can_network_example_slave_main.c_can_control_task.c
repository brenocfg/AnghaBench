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
typedef  int /*<<< orphan*/  tx_task_action_t ;
typedef  int /*<<< orphan*/  rx_task_action_t ;
struct TYPE_3__ {scalar_t__ msgs_to_tx; } ;
typedef  TYPE_1__ can_status_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  EXAMPLE_TAG ; 
 int ITER_DELAY_MS ; 
 int NO_OF_ITERS ; 
 int /*<<< orphan*/  RX_RECEIVE_PING ; 
 int /*<<< orphan*/  RX_RECEIVE_START_CMD ; 
 int /*<<< orphan*/  RX_RECEIVE_STOP_CMD ; 
 int /*<<< orphan*/  RX_TASK_EXIT ; 
 int /*<<< orphan*/  TX_SEND_DATA ; 
 int /*<<< orphan*/  TX_SEND_PING_RESP ; 
 int /*<<< orphan*/  TX_SEND_STOP_RESP ; 
 int /*<<< orphan*/  TX_TASK_EXIT ; 
 int /*<<< orphan*/  can_get_status_info (TYPE_1__*) ; 
 int /*<<< orphan*/  can_start () ; 
 int /*<<< orphan*/  can_stop () ; 
 int /*<<< orphan*/  ctrl_task_sem ; 
 int /*<<< orphan*/  done_sem ; 
 int /*<<< orphan*/  pdMS_TO_TICKS (int) ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  rx_task_queue ; 
 int /*<<< orphan*/  tx_task_queue ; 
 int /*<<< orphan*/  vTaskDelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xQueueSend (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xSemaphoreTake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void can_control_task(void *arg)
{
    xSemaphoreTake(ctrl_task_sem, portMAX_DELAY);
    tx_task_action_t tx_action;
    rx_task_action_t rx_action;

    for (int iter = 0; iter < NO_OF_ITERS; iter++) {
        ESP_ERROR_CHECK(can_start());
        ESP_LOGI(EXAMPLE_TAG, "Driver started");

        //Listen of pings from master
        rx_action = RX_RECEIVE_PING;
        xQueueSend(rx_task_queue, &rx_action, portMAX_DELAY);
        xSemaphoreTake(ctrl_task_sem, portMAX_DELAY);

        //Send ping response
        tx_action = TX_SEND_PING_RESP;
        xQueueSend(tx_task_queue, &tx_action, portMAX_DELAY);
        xSemaphoreTake(ctrl_task_sem, portMAX_DELAY);

        //Listen for start command
        rx_action = RX_RECEIVE_START_CMD;
        xQueueSend(rx_task_queue, &rx_action, portMAX_DELAY);
        xSemaphoreTake(ctrl_task_sem, portMAX_DELAY);

        //Start sending data messages and listen for stop command
        tx_action = TX_SEND_DATA;
        rx_action = RX_RECEIVE_STOP_CMD;
        xQueueSend(tx_task_queue, &tx_action, portMAX_DELAY);
        xQueueSend(rx_task_queue, &rx_action, portMAX_DELAY);
        xSemaphoreTake(ctrl_task_sem, portMAX_DELAY);

        //Send stop response
        tx_action = TX_SEND_STOP_RESP;
        xQueueSend(tx_task_queue, &tx_action, portMAX_DELAY);
        xSemaphoreTake(ctrl_task_sem, portMAX_DELAY);

        //Wait for bus to become free
        can_status_info_t status_info;
        can_get_status_info(&status_info);
        while (status_info.msgs_to_tx > 0) {
            vTaskDelay(pdMS_TO_TICKS(100));
            can_get_status_info(&status_info);
        }

        ESP_ERROR_CHECK(can_stop());
        ESP_LOGI(EXAMPLE_TAG, "Driver stopped");
        vTaskDelay(pdMS_TO_TICKS(ITER_DELAY_MS));
    }

    //Stop TX and RX tasks
    tx_action = TX_TASK_EXIT;
    rx_action = RX_TASK_EXIT;
    xQueueSend(tx_task_queue, &tx_action, portMAX_DELAY);
    xQueueSend(rx_task_queue, &rx_action, portMAX_DELAY);

    //Delete Control task
    xSemaphoreGive(done_sem);
    vTaskDelete(NULL);
}