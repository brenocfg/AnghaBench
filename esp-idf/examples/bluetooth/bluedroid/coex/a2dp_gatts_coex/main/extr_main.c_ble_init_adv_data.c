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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  raw_adv_data ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  BT_BLE_COEX_TAG ; 
 int ESP_BLE_ADV_FLAG_BREDR_NOT_SPT ; 
 int ESP_BLE_ADV_FLAG_GEN_DISC ; 
 int ESP_BLE_AD_TYPE_NAME_CMPL ; 
 int ESP_BT_EIR_TYPE_FLAGS ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ esp_ble_gap_config_adv_data_raw (int*,int) ; 
 scalar_t__ esp_ble_gap_config_scan_rsp_data_raw (int*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void ble_init_adv_data(const char *name)
{
    int len = strlen(name);
    uint8_t raw_adv_data[len+5];
    //flag
    raw_adv_data[0] = 2;
    raw_adv_data[1] = ESP_BT_EIR_TYPE_FLAGS;
    raw_adv_data[2] = (ESP_BLE_ADV_FLAG_GEN_DISC | ESP_BLE_ADV_FLAG_BREDR_NOT_SPT);
    //adv name
    raw_adv_data[3] = len + 1;
    raw_adv_data[4] = ESP_BLE_AD_TYPE_NAME_CMPL;
    for (int i = 0;i < len;i++)
    {
        raw_adv_data[i+5] = *(name++);
    }
    //The length of adv data must be less than 31 bytes
    esp_err_t raw_adv_ret = esp_ble_gap_config_adv_data_raw(raw_adv_data, sizeof(raw_adv_data));
    if (raw_adv_ret){
        ESP_LOGE(BT_BLE_COEX_TAG, "config raw adv data failed, error code = 0x%x ", raw_adv_ret);
    }
    esp_err_t raw_scan_ret = esp_ble_gap_config_scan_rsp_data_raw(raw_adv_data, sizeof(raw_adv_data));
    if (raw_scan_ret){
        ESP_LOGE(BT_BLE_COEX_TAG, "config raw scan rsp data failed, error code = 0x%x", raw_scan_ret);
    }
}