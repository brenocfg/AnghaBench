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
typedef  int /*<<< orphan*/  esp_ota_img_states_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OTA_IMG_NEW ; 
 int /*<<< orphan*/  ESP_OTA_IMG_UNDEFINED ; 
 int /*<<< orphan*/  TAG ; 

__attribute__((used)) static esp_ota_img_states_t set_new_state_otadata(void)
{
#ifdef CONFIG_BOOTLOADER_APP_ROLLBACK_ENABLE
    ESP_LOGD(TAG, "Monitoring the first boot of the app is enabled.");
    return ESP_OTA_IMG_NEW;
#else
    return ESP_OTA_IMG_UNDEFINED;
#endif
}