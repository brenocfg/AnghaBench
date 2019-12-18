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
typedef  int esp_err_t ;

/* Variables and functions */
 int ESP_OK ; 
 int esp_bt_controller_deinit () ; 
 int esp_bt_controller_disable () ; 
 int esp_nimble_hci_deinit () ; 

esp_err_t esp_nimble_hci_and_controller_deinit(void)
{
    int ret;
    ret = esp_nimble_hci_deinit();
    if (ret != ESP_OK) {
        return ret;
    }

    ret = esp_bt_controller_disable();
    if (ret != ESP_OK) {
        return ret;
    }

    ret = esp_bt_controller_deinit();
    if (ret != ESP_OK) {
        return ret;
    }

    return ESP_OK;
}