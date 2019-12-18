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
typedef  int /*<<< orphan*/ * esp_https_ota_handle_t ;
struct TYPE_3__ {int /*<<< orphan*/  const* http_config; } ;
typedef  TYPE_1__ esp_https_ota_config_t ;
typedef  int /*<<< orphan*/  esp_http_client_config_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_ERR_HTTPS_OTA_IN_PROGRESS ; 
 scalar_t__ ESP_ERR_INVALID_ARG ; 
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ esp_https_ota_begin (TYPE_1__*,int /*<<< orphan*/ **) ; 
 scalar_t__ esp_https_ota_finish (int /*<<< orphan*/ *) ; 
 scalar_t__ esp_https_ota_perform (int /*<<< orphan*/ *) ; 

esp_err_t esp_https_ota(const esp_http_client_config_t *config)
{
    if (!config) {
        ESP_LOGE(TAG, "esp_http_client config not found");
        return ESP_ERR_INVALID_ARG;
    }    

    esp_https_ota_config_t ota_config = {
        .http_config = config,
    };

    esp_https_ota_handle_t https_ota_handle = NULL;
    esp_err_t err = esp_https_ota_begin(&ota_config, &https_ota_handle);
    if (https_ota_handle == NULL) {
        return ESP_FAIL;
    }

    while (1) {
        err = esp_https_ota_perform(https_ota_handle);
        if (err != ESP_ERR_HTTPS_OTA_IN_PROGRESS) {
            break;
        }
    }

    esp_err_t ota_finish_err = esp_https_ota_finish(https_ota_handle);
    if (err != ESP_OK) {
        /* If there was an error in esp_https_ota_perform(),
           then it is given more precedence than error in esp_https_ota_finish()
         */
        return err;
    } else if (ota_finish_err != ESP_OK) {
        return ota_finish_err;
    }
    return ESP_OK;
}