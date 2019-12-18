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
typedef  int /*<<< orphan*/  esp_slave_context_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  ESP_ERROR_CHECK (scalar_t__) ; 
 scalar_t__ ESP_ERR_NOT_FINISHED ; 
 scalar_t__ ESP_ERR_NOT_FOUND ; 
 scalar_t__ ESP_ERR_TIMEOUT ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  ESP_LOG_BUFFER_HEXDUMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOG_INFO ; 
 scalar_t__ ESP_OK ; 
 int HOST_SLC0_RX_NEW_PACKET_INT_ST ; 
 size_t READ_BUFFER_LEN ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ esp_slave_clear_intr (int /*<<< orphan*/ *,int) ; 
 scalar_t__ esp_slave_get_intr (int /*<<< orphan*/ *,int*,int*) ; 
 scalar_t__ esp_slave_get_packet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,size_t*,int const) ; 
 scalar_t__ esp_slave_wait_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcv_buffer ; 

esp_err_t process_event(esp_slave_context_t *context)
{
    esp_err_t ret = esp_slave_wait_int(context, 0);
    if (ret == ESP_ERR_TIMEOUT) {
        return ret;
    }
    ESP_ERROR_CHECK(ret);

    uint32_t intr_raw, intr_st;
    ret = esp_slave_get_intr(context, &intr_raw, &intr_st);
    ESP_ERROR_CHECK(ret);
    ret = esp_slave_clear_intr(context, intr_raw);
    ESP_ERROR_CHECK(ret);
    ESP_LOGD(TAG, "intr: %08X", intr_raw);

    for (int i = 0; i < 8; i++) {
        if (intr_raw & BIT(i)) {
            ESP_LOGI(TAG, "host int: %d", i);
        }
    }

    const int wait_ms = 50;
    if (intr_raw & HOST_SLC0_RX_NEW_PACKET_INT_ST) {
        ESP_LOGD(TAG, "new packet coming");
        while (1) {
            size_t size_read = READ_BUFFER_LEN;
            ret = esp_slave_get_packet(context, rcv_buffer, READ_BUFFER_LEN, &size_read, wait_ms);
            if (ret == ESP_ERR_NOT_FOUND) {
                ESP_LOGE(TAG, "interrupt but no data can be read");
                break;
            } else if (ret != ESP_OK && ret != ESP_ERR_NOT_FINISHED) {
                ESP_LOGE(TAG, "rx packet error: %08X", ret);
                return ret;
            }

            ESP_LOGI(TAG, "receive data, size: %d", size_read);
            ESP_LOG_BUFFER_HEXDUMP(TAG, rcv_buffer, size_read, ESP_LOG_INFO);
            if (ret == ESP_OK) {
                break;
            }
        }
    }
    return ESP_OK;
}