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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ rx_task_action_t ;
struct TYPE_3__ {scalar_t__ identifier; int data_length_code; int* data; } ;
typedef  TYPE_1__ can_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  EXAMPLE_TAG ; 
 scalar_t__ ID_SLAVE_DATA ; 
 scalar_t__ ID_SLAVE_PING_RESP ; 
 scalar_t__ ID_SLAVE_STOP_RESP ; 
 scalar_t__ NO_OF_DATA_MSGS ; 
 scalar_t__ RX_RECEIVE_DATA ; 
 scalar_t__ RX_RECEIVE_PING_RESP ; 
 scalar_t__ RX_RECEIVE_STOP_RESP ; 
 scalar_t__ RX_TASK_EXIT ; 
 int /*<<< orphan*/  can_receive (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctrl_task_sem ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  rx_task_queue ; 
 int /*<<< orphan*/  stop_ping_sem ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xQueueReceive (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void can_receive_task(void *arg)
{
    while (1) {
        rx_task_action_t action;
        xQueueReceive(rx_task_queue, &action, portMAX_DELAY);

        if (action == RX_RECEIVE_PING_RESP) {
            //Listen for ping response from slave
            while (1) {
                can_message_t rx_msg;
                can_receive(&rx_msg, portMAX_DELAY);
                if (rx_msg.identifier == ID_SLAVE_PING_RESP) {
                    xSemaphoreGive(stop_ping_sem);
                    xSemaphoreGive(ctrl_task_sem);
                    break;
                }
            }
        } else if (action == RX_RECEIVE_DATA) {
            //Receive data messages from slave
            uint32_t data_msgs_rec = 0;
            while (data_msgs_rec < NO_OF_DATA_MSGS) {
                can_message_t rx_msg;
                can_receive(&rx_msg, portMAX_DELAY);
                if (rx_msg.identifier == ID_SLAVE_DATA) {
                    uint32_t data = 0;
                    for (int i = 0; i < rx_msg.data_length_code; i++) {
                        data |= (rx_msg.data[i] << (i * 8));
                    }
                    ESP_LOGI(EXAMPLE_TAG, "Received data value %d", data);
                    data_msgs_rec ++;
                }
            }
            xSemaphoreGive(ctrl_task_sem);
        } else if (action == RX_RECEIVE_STOP_RESP) {
            //Listen for stop response from slave
            while (1) {
                can_message_t rx_msg;
                can_receive(&rx_msg, portMAX_DELAY);
                if (rx_msg.identifier == ID_SLAVE_STOP_RESP) {
                    xSemaphoreGive(ctrl_task_sem);
                    break;
                }
            }
        } else if (action == RX_TASK_EXIT) {
            break;
        }
    }
    vTaskDelete(NULL);
}