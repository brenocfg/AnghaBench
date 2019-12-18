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
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ esp_bluedroid_deinit () ; 
 scalar_t__ esp_bluedroid_disable () ; 
 scalar_t__ esp_bt_controller_deinit () ; 
 scalar_t__ esp_bt_controller_disable () ; 
 int /*<<< orphan*/  esp_get_free_heap_size () ; 

esp_err_t simple_ble_stop(void)
{
    esp_err_t err;
    ESP_LOGD(TAG, "Free mem at start of simple_ble_stop %d", esp_get_free_heap_size());
    err = esp_bluedroid_disable();
    if (err != ESP_OK) {
        return ESP_FAIL;
    }
    ESP_LOGD(TAG, "esp_bluedroid_disable called successfully");
    err = esp_bluedroid_deinit();
    if (err != ESP_OK) {
        return err;
    }
    ESP_LOGD(TAG, "esp_bluedroid_deinit called successfully");
    err = esp_bt_controller_disable();
    if (err != ESP_OK) {
        return ESP_FAIL;
    }

    /* The API `esp_bt_controller_deinit` will have to be removed when we add support for
     * `reset to provisioning`
     */
    ESP_LOGD(TAG, "esp_bt_controller_disable called successfully");
    err = esp_bt_controller_deinit();
    if (err != ESP_OK) {
        return ESP_FAIL;
    }
    ESP_LOGD(TAG, "esp_bt_controller_deinit called successfully");

    ESP_LOGD(TAG, "Free mem at end of simple_ble_stop %d", esp_get_free_heap_size());
    return ESP_OK;
}