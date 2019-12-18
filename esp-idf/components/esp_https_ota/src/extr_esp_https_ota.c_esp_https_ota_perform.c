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
struct TYPE_3__ {int state; int binary_file_len; scalar_t__ ota_upgrade_buf; int /*<<< orphan*/  ota_upgrade_buf_size; int /*<<< orphan*/  http_client; int /*<<< orphan*/  update_handle; int /*<<< orphan*/  update_partition; } ;
typedef  TYPE_1__ esp_https_ota_t ;
typedef  scalar_t__ esp_https_ota_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_FAIL ; 
#define  ESP_HTTPS_OTA_BEGIN 129 
#define  ESP_HTTPS_OTA_IN_PROGRESS 128 
 int ESP_HTTPS_OTA_SUCCESS ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  OTA_SIZE_UNKNOWN ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  _ota_write (TYPE_1__*,void const*,int) ; 
 int /*<<< orphan*/  esp_err_to_name (int /*<<< orphan*/ ) ; 
 int esp_http_client_read (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_ota_begin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

esp_err_t esp_https_ota_perform(esp_https_ota_handle_t https_ota_handle)
{
    esp_https_ota_t *handle = (esp_https_ota_t *)https_ota_handle;
    if (handle == NULL) {
        ESP_LOGE(TAG, "esp_https_ota_perform: Invalid argument");
        return ESP_ERR_INVALID_ARG;
    }
    if (handle->state < ESP_HTTPS_OTA_BEGIN) {
        ESP_LOGE(TAG, "esp_https_ota_perform: Invalid state");
        return ESP_FAIL;
    }

    esp_err_t err;
    int data_read;
    switch (handle->state) {
        case ESP_HTTPS_OTA_BEGIN:
            err = esp_ota_begin(handle->update_partition, OTA_SIZE_UNKNOWN, &handle->update_handle);
            if (err != ESP_OK) {
                ESP_LOGE(TAG, "esp_ota_begin failed (%s)", esp_err_to_name(err));
                return err;
            }
            handle->state = ESP_HTTPS_OTA_IN_PROGRESS;
            /* In case `esp_https_ota_read_img_desc` was invoked first,
               then the image data read there should be written to OTA partition
               */
            if (handle->binary_file_len) {
                return _ota_write(handle, (const void *)handle->ota_upgrade_buf, handle->binary_file_len);
            }
            /* falls through */
        case ESP_HTTPS_OTA_IN_PROGRESS:
            data_read = esp_http_client_read(handle->http_client,
                                             handle->ota_upgrade_buf,
                                             handle->ota_upgrade_buf_size);
            if (data_read == 0) {
                ESP_LOGI(TAG, "Connection closed");
            } else if (data_read < 0) {
                ESP_LOGE(TAG, "Error: SSL data read error");
                return ESP_FAIL;
            } else if (data_read > 0) {
                return _ota_write(handle, (const void *)handle->ota_upgrade_buf, data_read);
            }
            handle->state = ESP_HTTPS_OTA_SUCCESS;
            break;
         default:
            ESP_LOGE(TAG, "Invalid ESP HTTPS OTA State");
            return ESP_FAIL;
            break;
    }
    return ESP_OK;
}