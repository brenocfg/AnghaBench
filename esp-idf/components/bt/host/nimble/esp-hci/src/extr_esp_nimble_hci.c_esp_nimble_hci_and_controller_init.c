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
typedef  int /*<<< orphan*/  esp_bt_controller_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  BT_CONTROLLER_INIT_CONFIG_DEFAULT () ; 
 int /*<<< orphan*/  ESP_BT_MODE_BLE ; 
 int /*<<< orphan*/  ESP_BT_MODE_CLASSIC_BT ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  esp_bt_controller_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_bt_controller_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_bt_controller_mem_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_nimble_hci_init () ; 

esp_err_t esp_nimble_hci_and_controller_init(void)
{
    esp_err_t ret;

    esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT);

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();

    if ((ret = esp_bt_controller_init(&bt_cfg)) != ESP_OK) {
        return ret;
    }

    if ((ret = esp_bt_controller_enable(ESP_BT_MODE_BLE)) != ESP_OK) {
        return ret;
    }
    return esp_nimble_hci_init();
}