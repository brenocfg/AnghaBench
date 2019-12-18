#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  protocomm_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_2__ {int /*<<< orphan*/ * pc_ble; } ;

/* Variables and functions */
 scalar_t__ ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  ble_cfg_p ; 
 scalar_t__ ble_gap_adv_stop () ; 
 scalar_t__ esp_nimble_hci_and_controller_deinit () ; 
 int /*<<< orphan*/  free_gatt_ble_misc_memory (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nimble_port_deinit () ; 
 scalar_t__ nimble_port_stop () ; 
 TYPE_1__* protoble_internal ; 
 int /*<<< orphan*/  protocomm_ble_cleanup () ; 

esp_err_t protocomm_ble_stop(protocomm_t *pc)
{
    ESP_LOGD(TAG, "protocomm_ble_stop called here...");
    if ((pc != NULL) &&
            (protoble_internal != NULL ) &&
            (pc == protoble_internal->pc_ble)) {
        esp_err_t ret = ESP_OK;

        esp_err_t rc = ble_gap_adv_stop();
        if (rc) {
            ESP_LOGD(TAG, "Error in stopping advertisement with err code = %d",
                     rc);
        }

        ret = nimble_port_stop();
        if (ret == 0) {
            nimble_port_deinit();
            ret = esp_nimble_hci_and_controller_deinit();
            if (ret != ESP_OK) {
                ESP_LOGE(TAG, "esp_nimble_hci_and_controller_deinit() failed with error: %d", ret);
            }
        }

        free_gatt_ble_misc_memory(ble_cfg_p);
        protocomm_ble_cleanup();
        return ret;
    }
    return ESP_ERR_INVALID_ARG;
}