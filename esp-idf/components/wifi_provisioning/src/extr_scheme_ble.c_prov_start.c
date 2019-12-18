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
typedef  int /*<<< orphan*/  protocomm_t ;
typedef  int /*<<< orphan*/  protocomm_ble_config_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_ERR_INVALID_ARG ; 
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ protocomm_ble_start (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static esp_err_t prov_start(protocomm_t *pc, void *config)
{
    if (!pc) {
        ESP_LOGE(TAG, "Protocomm handle cannot be null");
        return ESP_ERR_INVALID_ARG;
    }

    if (!config) {
        ESP_LOGE(TAG, "Cannot start with null configuration");
        return ESP_ERR_INVALID_ARG;
    }

    protocomm_ble_config_t *ble_config = (protocomm_ble_config_t *) config;

    /* Start protocomm as BLE service */
    if (protocomm_ble_start(pc, ble_config) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to start protocomm BLE service");
        return ESP_FAIL;
    }
    return ESP_OK;
}