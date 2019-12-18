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
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  app_prov_configure_sta (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_config (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * get_config (int /*<<< orphan*/ **) ; 

__attribute__((used)) static esp_err_t apply_config_handler(wifi_prov_ctx_t **ctx)
{
    wifi_config_t *wifi_cfg = get_config(ctx);
    if (!wifi_cfg) {
        ESP_LOGE(TAG, "WiFi config not set");
        return ESP_FAIL;
    }

    app_prov_configure_sta(wifi_cfg);
    ESP_LOGI(TAG, "WiFi Credentials Applied");

    free_config(ctx);
    return ESP_OK;
}