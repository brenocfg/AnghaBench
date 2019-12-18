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
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 TYPE_1__* protoble_internal ; 
 int /*<<< orphan*/  protocomm_ble_cleanup () ; 
 int /*<<< orphan*/  simple_ble_deinit () ; 
 scalar_t__ simple_ble_stop () ; 

esp_err_t protocomm_ble_stop(protocomm_t *pc)
{
    if ((pc != NULL) &&
        (protoble_internal != NULL ) &&
        (pc == protoble_internal->pc_ble)) {
        esp_err_t ret = ESP_OK;
        ret = simple_ble_stop();
        if (ret) {
            ESP_LOGE(TAG, "BLE stop failed");
        }
        simple_ble_deinit();
        protocomm_ble_cleanup();
        return ret;
    }
    return ESP_ERR_INVALID_ARG;
}