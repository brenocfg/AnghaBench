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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ esp_err_t ;
typedef  int /*<<< orphan*/  err_msg ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  GATTC_TAG ; 
 int /*<<< orphan*/  PROFILE_APP_ID ; 
 void* cmd_heartbeat_queue ; 
 void* cmd_reg_queue ; 
 scalar_t__ esp_ble_gap_register_callback (int /*<<< orphan*/ ) ; 
 scalar_t__ esp_ble_gatt_set_local_mtu (int) ; 
 int /*<<< orphan*/  esp_ble_gattc_app_register (int /*<<< orphan*/ ) ; 
 scalar_t__ esp_ble_gattc_register_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_err_to_name_r (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  esp_gap_cb ; 
 int /*<<< orphan*/  esp_gattc_cb ; 
 int /*<<< orphan*/  spp_client_reg_task ; 
 int /*<<< orphan*/  spp_heart_beat_task ; 
 void* xQueueCreate (int,int) ; 
 int /*<<< orphan*/  xTaskCreate (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

void ble_client_appRegister(void)
{
    esp_err_t status;
    char err_msg[20];

    ESP_LOGI(GATTC_TAG, "register callback");

    //register the scan callback function to the gap module
    if ((status = esp_ble_gap_register_callback(esp_gap_cb)) != ESP_OK) {
        ESP_LOGE(GATTC_TAG, "gap register error: %s", esp_err_to_name_r(status, err_msg, sizeof(err_msg)));
        return;
    }
    //register the callback function to the gattc module
    if ((status = esp_ble_gattc_register_callback(esp_gattc_cb)) != ESP_OK) {
        ESP_LOGE(GATTC_TAG, "gattc register error: %s", esp_err_to_name_r(status, err_msg, sizeof(err_msg)));
        return;
    }
    esp_ble_gattc_app_register(PROFILE_APP_ID);

    esp_err_t local_mtu_ret = esp_ble_gatt_set_local_mtu(200);
    if (local_mtu_ret){
        ESP_LOGE(GATTC_TAG, "set local  MTU failed: %s", esp_err_to_name_r(local_mtu_ret, err_msg, sizeof(err_msg)));
    }

    cmd_reg_queue = xQueueCreate(10, sizeof(uint32_t));
    xTaskCreate(spp_client_reg_task, "spp_client_reg_task", 2048, NULL, 10, NULL);

#ifdef SUPPORT_HEARTBEAT
    cmd_heartbeat_queue = xQueueCreate(10, sizeof(uint32_t));
    xTaskCreate(spp_heart_beat_task, "spp_heart_beat_task", 2048, NULL, 10, NULL);
#endif
}