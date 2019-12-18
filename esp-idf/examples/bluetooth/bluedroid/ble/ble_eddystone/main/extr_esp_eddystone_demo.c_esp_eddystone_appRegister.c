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

/* Variables and functions */
 int /*<<< orphan*/  DEMO_TAG ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  esp_ble_gap_register_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_err_to_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_gap_cb ; 

void esp_eddystone_appRegister(void)
{
    esp_err_t status;
    
    ESP_LOGI(DEMO_TAG,"Register callback");

    /*<! register the scan callback function to the gap module */
    if((status = esp_ble_gap_register_callback(esp_gap_cb)) != ESP_OK) {
        ESP_LOGE(DEMO_TAG,"gap register error: %s", esp_err_to_name(status));
        return;
    }
}