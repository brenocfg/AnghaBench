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
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  esp_supplicant_deinit () ; 
 scalar_t__ esp_wifi_deinit_internal () ; 
 int /*<<< orphan*/  tcpip_adapter_clear_default_wifi_handlers () ; 

esp_err_t esp_wifi_deinit(void)
{
    esp_err_t err = ESP_OK;

    esp_supplicant_deinit();
    err = esp_wifi_deinit_internal();
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to deinit Wi-Fi driver (0x%x)", err);
    }

#if CONFIG_ESP_NETIF_TCPIP_ADAPTER_COMPATIBLE_LAYER
    tcpip_adapter_clear_default_wifi_handlers();
#endif

    return err;
}