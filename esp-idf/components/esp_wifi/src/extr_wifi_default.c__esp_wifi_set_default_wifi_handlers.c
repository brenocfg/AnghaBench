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
typedef  int /*<<< orphan*/  shutdown_handler_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_ERR_INVALID_STATE ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  IP_EVENT ; 
 int /*<<< orphan*/  IP_EVENT_STA_GOT_IP ; 
 int /*<<< orphan*/  WIFI_EVENT ; 
 int /*<<< orphan*/  WIFI_EVENT_AP_START ; 
 int /*<<< orphan*/  WIFI_EVENT_AP_STOP ; 
 int /*<<< orphan*/  WIFI_EVENT_STA_CONNECTED ; 
 int /*<<< orphan*/  WIFI_EVENT_STA_DISCONNECTED ; 
 int /*<<< orphan*/  WIFI_EVENT_STA_START ; 
 int /*<<< orphan*/  WIFI_EVENT_STA_STOP ; 
 int /*<<< orphan*/  _esp_wifi_clear_default_wifi_handlers () ; 
 scalar_t__ esp_event_handler_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ esp_register_shutdown_handler (int /*<<< orphan*/ ) ; 
 scalar_t__ esp_wifi_stop ; 
 int /*<<< orphan*/  wifi_default_action_ap_start ; 
 int /*<<< orphan*/  wifi_default_action_ap_stop ; 
 int /*<<< orphan*/  wifi_default_action_sta_connected ; 
 int /*<<< orphan*/  wifi_default_action_sta_disconnected ; 
 int /*<<< orphan*/  wifi_default_action_sta_got_ip ; 
 int /*<<< orphan*/  wifi_default_action_sta_start ; 
 int /*<<< orphan*/  wifi_default_action_sta_stop ; 
 int wifi_default_handlers_set ; 

esp_err_t _esp_wifi_set_default_wifi_handlers(void)
{
    if (wifi_default_handlers_set) {
        return ESP_OK;
    }
    esp_err_t err;
    err = esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_START, wifi_default_action_sta_start, NULL);
    if (err != ESP_OK) {
        goto fail;
    }

    err = esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_STOP, wifi_default_action_sta_stop, NULL);
    if (err != ESP_OK) {
        goto fail;
    }

    err = esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_CONNECTED, wifi_default_action_sta_connected, NULL);
    if (err != ESP_OK) {
        goto fail;
    }

    err = esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, wifi_default_action_sta_disconnected, NULL);
    if (err != ESP_OK) {
        goto fail;
    }

    err = esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_AP_START, wifi_default_action_ap_start, NULL);
    if (err != ESP_OK) {
        goto fail;
    }

    err = esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_AP_STOP, wifi_default_action_ap_stop, NULL);
    if (err != ESP_OK) {
        goto fail;
    }

    err = esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, wifi_default_action_sta_got_ip, NULL);
    if (err != ESP_OK) {
        goto fail;
    }

    err = esp_register_shutdown_handler((shutdown_handler_t)esp_wifi_stop);
    if (err != ESP_OK && err != ESP_ERR_INVALID_STATE) {
        goto fail;
    }
    wifi_default_handlers_set = true;
    return ESP_OK;

fail:
    _esp_wifi_clear_default_wifi_handlers();
    return err;
}