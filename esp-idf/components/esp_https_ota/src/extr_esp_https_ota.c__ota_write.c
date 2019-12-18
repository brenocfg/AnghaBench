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
struct TYPE_3__ {size_t binary_file_len; int /*<<< orphan*/  update_handle; } ;
typedef  TYPE_1__ esp_https_ota_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_ERR_HTTPS_OTA_IN_PROGRESS ; 
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ esp_ota_write (int /*<<< orphan*/ ,void const*,size_t) ; 

__attribute__((used)) static esp_err_t _ota_write(esp_https_ota_t *https_ota_handle, const void *buffer, size_t buf_len)
{
    if (buffer == NULL || https_ota_handle == NULL) {
        return ESP_FAIL;
    }
    esp_err_t err = esp_ota_write(https_ota_handle->update_handle, buffer, buf_len);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error: esp_ota_write failed! err=0x%d", err);
    } else {
        https_ota_handle->binary_file_len += buf_len;
        ESP_LOGD(TAG, "Written image length %d", https_ota_handle->binary_file_len);
        err = ESP_ERR_HTTPS_OTA_IN_PROGRESS;
    }
    return err;
}