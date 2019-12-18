#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ ssid; } ;
struct TYPE_4__ {TYPE_3__ sta; } ;
typedef  TYPE_1__ wifi_config_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_ERR_INVALID_ARG ; 
 scalar_t__ ESP_ERR_INVALID_STATE ; 
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_IF_WIFI_STA ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  debug_print_wifi_credentials (TYPE_3__,char*) ; 
 scalar_t__ esp_wifi_get_config (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  prov_ctx_lock ; 
 scalar_t__ strlen (char const*) ; 

esp_err_t wifi_prov_mgr_is_provisioned(bool *provisioned)
{
    if (!provisioned) {
        return ESP_ERR_INVALID_ARG;
    }

    *provisioned = false;

    if (!prov_ctx_lock) {
        ESP_LOGE(TAG, "Provisioning manager not initialized");
        return ESP_ERR_INVALID_STATE;
    }

    /* Get Wi-Fi Station configuration */
    wifi_config_t wifi_cfg;
    if (esp_wifi_get_config(ESP_IF_WIFI_STA, &wifi_cfg) != ESP_OK) {
        return ESP_FAIL;
    }

    if (strlen((const char *) wifi_cfg.sta.ssid)) {
        *provisioned = true;
        debug_print_wifi_credentials(wifi_cfg.sta, "Found");
    }
    return ESP_OK;
}