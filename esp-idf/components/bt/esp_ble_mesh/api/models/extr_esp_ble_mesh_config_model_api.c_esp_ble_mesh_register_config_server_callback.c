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
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  esp_ble_mesh_cfg_server_cb_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_PID_CONFIG_SERVER ; 
 int /*<<< orphan*/  ESP_BLE_HOST_STATUS_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_BLE_HOST_STATUS_ENABLED ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 scalar_t__ btc_profile_cb_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

esp_err_t esp_ble_mesh_register_config_server_callback(esp_ble_mesh_cfg_server_cb_t callback)
{
    ESP_BLE_HOST_STATUS_CHECK(ESP_BLE_HOST_STATUS_ENABLED);

    return (btc_profile_cb_set(BTC_PID_CONFIG_SERVER, callback) == 0 ? ESP_OK : ESP_FAIL);
}