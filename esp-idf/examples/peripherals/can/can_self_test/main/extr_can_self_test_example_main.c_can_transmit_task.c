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
struct TYPE_3__ {int data_length_code; int* data; int /*<<< orphan*/  flags; int /*<<< orphan*/  identifier; } ;
typedef  TYPE_1__ can_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_MSG_FLAG_SELF ; 
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_ID ; 
 int NO_OF_ITERS ; 
 int NO_OF_MSGS ; 
 int /*<<< orphan*/  can_transmit (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdMS_TO_TICKS (int) ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  tx_sem ; 
 int /*<<< orphan*/  vTaskDelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xSemaphoreTake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void can_transmit_task(void *arg)
{
    can_message_t tx_msg = {.data_length_code = 1, .identifier = MSG_ID, .flags = CAN_MSG_FLAG_SELF};
    for (int iter = 0; iter < NO_OF_ITERS; iter++) {
        xSemaphoreTake(tx_sem, portMAX_DELAY);
        for (int i = 0; i < NO_OF_MSGS; i++) {
            //Transmit messages using self reception request
            tx_msg.data[0] = i;
            ESP_ERROR_CHECK(can_transmit(&tx_msg, portMAX_DELAY));
            vTaskDelay(pdMS_TO_TICKS(10));
        }
    }
    vTaskDelete(NULL);
}