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
typedef  int /*<<< orphan*/  wifi_prov_ctx_t ;
typedef  int /*<<< orphan*/  wifi_config_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  free_config (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * get_config (int /*<<< orphan*/ **) ; 
 scalar_t__ wifi_prov_mgr_configure_sta (int /*<<< orphan*/ *) ; 

__attribute__((used)) static esp_err_t apply_config_handler(wifi_prov_ctx_t **ctx)
{
    wifi_config_t *wifi_cfg = get_config(ctx);
    if (!wifi_cfg) {
        ESP_LOGE(TAG, "Wi-Fi config not set");
        return ESP_ERR_INVALID_STATE;
    }

    esp_err_t ret = wifi_prov_mgr_configure_sta(wifi_cfg);
    if (ret == ESP_OK) {
        ESP_LOGD(TAG, "Wi-Fi Credentials Applied");
    } else {
        ESP_LOGE(TAG, "Failed to apply Wi-Fi Credentials");
    }

    free_config(ctx);
    return ret;
}