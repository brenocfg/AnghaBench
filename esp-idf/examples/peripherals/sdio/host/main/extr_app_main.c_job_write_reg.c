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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  esp_slave_context_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOG_BUFFER_HEXDUMP (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOG_INFO ; 
 int /*<<< orphan*/  JOB_WRITE_REG ; 
 int /*<<< orphan*/  SLAVE_REG_VALUE ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  esp_slave_read_reg (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_slave_write_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slave_inform_job (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

void job_write_reg(esp_slave_context_t *context, int value)
{
    esp_err_t ret;
    uint8_t reg_read[64];
    ESP_LOGI(TAG, "========JOB: write slave reg========");
    ret = esp_slave_write_reg(context, SLAVE_REG_VALUE, value, NULL);
    ESP_ERROR_CHECK(ret);

    ret = slave_inform_job(context, JOB_WRITE_REG);
    ESP_ERROR_CHECK(ret);

    vTaskDelay(10);
    for (int i = 0; i < 64; i++) {
        ESP_LOGD(TAG, "reading register %d", i);
        ret = esp_slave_read_reg(context, i, &reg_read[i]);
        ESP_ERROR_CHECK(ret);
    }

    ESP_LOGI(TAG, "read registers:");
    ESP_LOG_BUFFER_HEXDUMP(TAG, reg_read, 64, ESP_LOG_INFO);
}