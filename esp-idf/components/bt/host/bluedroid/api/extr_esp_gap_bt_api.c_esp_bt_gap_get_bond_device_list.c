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
typedef  int /*<<< orphan*/  esp_bd_addr_t ;
typedef  int /*<<< orphan*/  bt_bdaddr_t ;

/* Variables and functions */
 int BT_STATUS_SUCCESS ; 
 scalar_t__ ESP_BLUEDROID_STATUS_ENABLED ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 int btc_storage_get_bonded_bt_devices_list (int /*<<< orphan*/ *,int) ; 
 int btc_storage_get_num_bt_bond_devices () ; 
 scalar_t__ esp_bluedroid_get_status () ; 

esp_err_t esp_bt_gap_get_bond_device_list(int *dev_num, esp_bd_addr_t *dev_list)
{
    int ret;
    int dev_num_total;

    if (dev_num == NULL || dev_list == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    if (esp_bluedroid_get_status() != ESP_BLUEDROID_STATUS_ENABLED) {
        return ESP_ERR_INVALID_STATE;
    }

    dev_num_total = btc_storage_get_num_bt_bond_devices();
    if (*dev_num > dev_num_total) {
        *dev_num = dev_num_total;
    }

    ret = btc_storage_get_bonded_bt_devices_list((bt_bdaddr_t *)dev_list, *dev_num);

    return (ret == BT_STATUS_SUCCESS ? ESP_OK : ESP_FAIL);
}