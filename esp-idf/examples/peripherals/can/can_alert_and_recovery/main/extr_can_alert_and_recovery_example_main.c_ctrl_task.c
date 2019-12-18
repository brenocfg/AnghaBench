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

/* Variables and functions */
 int CAN_ALERT_ABOVE_ERR_WARN ; 
 int CAN_ALERT_BUS_OFF ; 
 int CAN_ALERT_BUS_RECOVERED ; 
 int CAN_ALERT_ERR_PASS ; 
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  EXAMPLE_TAG ; 
 int /*<<< orphan*/  can_initiate_recovery () ; 
 int /*<<< orphan*/  can_read_alerts (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_reconfigure_alerts (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  can_start () ; 
 int /*<<< orphan*/  ctrl_task_sem ; 
 int /*<<< orphan*/  pdMS_TO_TICKS (int) ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int trigger_tx_error ; 
 int /*<<< orphan*/  tx_task_sem ; 
 int /*<<< orphan*/  vTaskDelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xSemaphoreTake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ctrl_task(void *arg)
{
    xSemaphoreTake(ctrl_task_sem, portMAX_DELAY);
    ESP_ERROR_CHECK(can_start());
    ESP_LOGI(EXAMPLE_TAG, "Driver started");
    ESP_LOGI(EXAMPLE_TAG, "Starting transmissions");
    xSemaphoreGive(tx_task_sem);    //Start transmit task

    //Prepare to trigger errors, reconfigure alerts to detect change in error state
    can_reconfigure_alerts(CAN_ALERT_ABOVE_ERR_WARN | CAN_ALERT_ERR_PASS | CAN_ALERT_BUS_OFF, NULL);
    for (int i = 3; i > 0; i--) {
        ESP_LOGW(EXAMPLE_TAG, "Trigger TX errors in %d", i);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    ESP_LOGI(EXAMPLE_TAG, "Trigger errors");
    trigger_tx_error = true;

    while (1) {
        uint32_t alerts;
        can_read_alerts(&alerts, portMAX_DELAY);
        if (alerts & CAN_ALERT_ABOVE_ERR_WARN) {
            ESP_LOGI(EXAMPLE_TAG, "Surpassed Error Warning Limit");
        }
        if (alerts & CAN_ALERT_ERR_PASS) {
            ESP_LOGI(EXAMPLE_TAG, "Entered Error Passive state");
        }
        if (alerts & CAN_ALERT_BUS_OFF) {
            ESP_LOGI(EXAMPLE_TAG, "Bus Off state");
            //Prepare to initiate bus recovery, reconfigure alerts to detect bus recovery completion
            can_reconfigure_alerts(CAN_ALERT_BUS_RECOVERED, NULL);
            for (int i = 3; i > 0; i--) {
                ESP_LOGW(EXAMPLE_TAG, "Initiate bus recovery in %d", i);
                vTaskDelay(pdMS_TO_TICKS(1000));
            }
            can_initiate_recovery();    //Needs 128 occurrences of bus free signal
            ESP_LOGI(EXAMPLE_TAG, "Initiate bus recovery");
        }
        if (alerts & CAN_ALERT_BUS_RECOVERED) {
            //Bus recovery was successful, exit control task to uninstall driver
            ESP_LOGI(EXAMPLE_TAG, "Bus Recovered");
            break;
        }
    }
    //No need call can_stop(), bus recovery will return to stopped state
    xSemaphoreGive(ctrl_task_sem);
    vTaskDelete(NULL);
}