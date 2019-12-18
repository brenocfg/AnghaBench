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
typedef  int /*<<< orphan*/  esp_slave_context_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  JOB_RESET ; 
 int /*<<< orphan*/  SLAVE_INTR_NOTIFY ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ esp_slave_send_slave_intr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ esp_slave_wait_for_ioready (int /*<<< orphan*/ *) ; 
 scalar_t__ esp_slave_write_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int portTICK_RATE_MS ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

esp_err_t slave_reset(esp_slave_context_t *context)
{
    esp_err_t ret;
    ESP_LOGI(TAG, "send reset to slave...");
    ret = esp_slave_write_reg(context, 0, JOB_RESET, NULL);
    if (ret != ESP_OK) {
        return ret;
    }
    ret = esp_slave_send_slave_intr(context, BIT(SLAVE_INTR_NOTIFY));
    if (ret != ESP_OK) {
        return ret;
    }

    vTaskDelay(500 / portTICK_RATE_MS);
    ret = esp_slave_wait_for_ioready(context);
    ESP_LOGI(TAG, "slave io ready");
    return ret;
}