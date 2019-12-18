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
typedef  int /*<<< orphan*/  wifi_mode_t ;

/* Variables and functions */
 int ESP_ERR_WIFI_MODE ; 
 int ESP_FAIL ; 
 int ESP_OK ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  WIFI_MODE_AP ; 
 int /*<<< orphan*/  WIFI_MODE_NULL ; 
 int esp_wifi_get_mode (int /*<<< orphan*/ *) ; 
 int esp_wifi_get_promiscuous (int*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,...) ; 

int wps_check_wifi_mode(void)
{
    bool sniffer = false;
    wifi_mode_t mode;
    int ret;

    ret = esp_wifi_get_mode(&mode);
    if (ESP_OK != ret) {
        wpa_printf(MSG_ERROR, "wps check wifi mode: failed to get wifi mode ret=%d", ret);
        return ESP_FAIL;
    }

    ret = esp_wifi_get_promiscuous(&sniffer);
    if (ESP_OK != ret) {
        wpa_printf(MSG_ERROR, "wps check wifi mode: failed to get sniffer mode ret=%d", ret);
        return ESP_FAIL;
    }

    if (mode == WIFI_MODE_AP || mode == WIFI_MODE_NULL || sniffer == true) {
        wpa_printf(MSG_ERROR, "wps check wifi mode: wrong wifi mode=%d sniffer=%d", mode, sniffer);
        return ESP_ERR_WIFI_MODE;
    }

    return ESP_OK;
}